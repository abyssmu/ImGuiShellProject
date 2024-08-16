#include "setup_and_teardown.h"

int main(int, char**)
{
	int width = 1280;
	int height = 800;
	int x = 100;
	int y = 100;

	WNDCLASSEXW wc = {
		sizeof(wc),
		CS_OWNDC,
		WndProc,
		0L,
		0L,
		GetModuleHandle(nullptr),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		L"Physics Sim",
		nullptr
	};

	::RegisterClassExW(&wc);

	HWND hwnd = ::CreateWindowW(
		wc.lpszClassName,
		L"Physics Sim",
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		width,
		height,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGuiIO& io = SetupImGui(hwnd, wc);
	//bool demo = true;
	bool demo = true;

	if (demo)
	{
		bool show_demo_window = false;
		bool show_another_window = false;
		LoopImGuiDemo(show_demo_window, show_another_window, clear_color, io);
	}

	DestroyImGui(hwnd, wc);

	return 0;
}