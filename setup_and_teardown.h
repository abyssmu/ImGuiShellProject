// Most of this portion is copied from ImGui opengl3+win32 example
// It has been reorginized a bit for better reading

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "imgui_helper.h"

struct WGL_WindowData { HDC hDC; };

static HGLRC g_hRC;
static WGL_WindowData g_MainWindow;
static int g_Width;
static int g_Height;

bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);
void ResetDeviceWGL();

ImGuiIO& SetupImGui(HWND& hwnd, WNDCLASSEXW& wc);
void LoopImGuiDemo(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io);
void DestroyImGui(HWND& hwnd, WNDCLASSEXW& wc);
bool ProcessMessages();

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void Hook_Renderer_CreateWindow(ImGuiViewport* viewport)
{
	assert(viewport->RendererUserData == NULL);

	WGL_WindowData* data = IM_NEW(WGL_WindowData);
	CreateDeviceWGL((HWND)viewport->PlatformHandle, data);
	viewport->RendererUserData = data;
}

static void Hook_Renderer_DestroyWindow(ImGuiViewport* viewport)
{
	if (viewport->RendererUserData != NULL)
	{
		WGL_WindowData* data = (WGL_WindowData*)viewport->RendererUserData;
		CleanupDeviceWGL((HWND)viewport->PlatformHandle, data);
		IM_DELETE(data);
		viewport->RendererUserData = NULL;
	}
}

static void Hook_Platform_RenderWindow(ImGuiViewport* viewport, void*)
{
	if (WGL_WindowData* data = (WGL_WindowData*)viewport->RendererUserData)
		wglMakeCurrent(data->hDC, g_hRC);
}

static void Hook_Renderer_SwapBuffers(ImGuiViewport* viewport, void*)
{
	if (WGL_WindowData* data = (WGL_WindowData*)viewport->RendererUserData)
		::SwapBuffers(data->hDC);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);