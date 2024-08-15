#pragma once

#include "setup_and_teardown.h"

bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
	HDC hDc = ::GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	const int pf = ::ChoosePixelFormat(hDc, &pfd);
	if (pf == 0) return false;
	if (::SetPixelFormat(hDc, pf, &pfd) == FALSE) return false;
	::ReleaseDC(hWnd, hDc);

	data->hDC = ::GetDC(hWnd);
	if (!g_hRC) g_hRC = wglCreateContext(data->hDC);

	return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
	wglMakeCurrent(nullptr, nullptr);
	::ReleaseDC(hWnd, data->hDC);
}

void ResetDeviceWGL()
{

}

ImGuiIO& SetupImGui(HWND& hwnd, WNDCLASSEXW& wc)
{
	if (!CreateDeviceWGL(hwnd, &g_MainWindow))
	{
		CleanupDeviceWGL(hwnd, &g_MainWindow);
		::DestroyWindow(hwnd);
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
		return ImGuiIO();
	}
	wglMakeCurrent(g_MainWindow.hDC, g_hRC);

	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_InitForOpenGL(hwnd);
	ImGui_ImplOpenGL3_Init();

	// Win32+GL needs specific hooks for viewport, as there are specific things needed to tie Win32 and GL api.
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
		IM_ASSERT(platform_io.Renderer_CreateWindow == NULL);
		IM_ASSERT(platform_io.Renderer_DestroyWindow == NULL);
		IM_ASSERT(platform_io.Renderer_SwapBuffers == NULL);
		IM_ASSERT(platform_io.Platform_RenderWindow == NULL);
		platform_io.Renderer_CreateWindow = Hook_Renderer_CreateWindow;
		platform_io.Renderer_DestroyWindow = Hook_Renderer_DestroyWindow;
		platform_io.Renderer_SwapBuffers = Hook_Renderer_SwapBuffers;
		platform_io.Platform_RenderWindow = Hook_Platform_RenderWindow;
	}

	return io;
}

void LoopImGuiDemo(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io)
{
	while (true)
	{
		if (ProcessMessages()) break;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		SetupBasicWindow(show_demo_window, show_another_window, clear_color, io);
		RenderImGui(g_Width, g_Height, clear_color, io);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			// Restore the OpenGL rendering context to the main window DC, since platform windows might have changed it.
			wglMakeCurrent(g_MainWindow.hDC, g_hRC);
		}

		::SwapBuffers(g_MainWindow.hDC);
	}
}

void DestroyImGui(HWND& hwnd, WNDCLASSEXW& wc)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceWGL(hwnd, &g_MainWindow);
	wglDeleteContext(g_hRC);
	::DestroyWindow(hwnd);
	::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

bool ProcessMessages()
{
	// Poll and handle messages (inputs, window resize, etc.)
	// See the WndProc() function below for our dispatch events to the Win32 backend.
	MSG msg;
	while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT) return true;
	}

	return false;
}

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			g_Width = LOWORD(lParam);
			g_Height = HIWORD(lParam);
		}
		return false;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) return false; // Disable ALT application menu
	case WM_DESTROY:
		::PostQuitMessage(0);
		return false;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}