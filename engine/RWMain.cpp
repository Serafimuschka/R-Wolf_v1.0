#include <Windows.h>
#include <wchar.h>
#include "resource.h"
#include "RWGlobalDefinitions.h"
#include "RWGraphics.h"
#include "RWLevel.h"
#include "RW-Demo-3D-UI.h"
#include "RWController.h"

RWGraphics* graphics;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
								ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize					= sizeof(WNDCLASSEX);
	wcex.hIcon					= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hbrBackground			= (HBRUSH)COLOR_WINDOW;
	wcex.hInstance				= hInst;
	wcex.lpfnWndProc			= WindowProc;
	wcex.lpszClassName			= "RWolf";
	wcex.style					= CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	HWND windowHandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"RWolf",
		"R-Wolf 2DGE ",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		NULL,
		NULL,
		hInst,
		0);
	if (!windowHandle) {
		MessageBox(NULL, "CreateWindowEx failed", "Critical error", MB_ICONWARNING);
		return -1;
	}
	graphics = new RWGraphics();
	if (!graphics->Init(windowHandle)) {
		MessageBox(NULL, "Window handle initialization failed", "Critical error", MB_ICONWARNING);
		delete graphics;
		return -1;
	}
	graphics->GetCurrentMainHWND(windowHandle);
	SetWindowLong(windowHandle, GWL_STYLE, WS_POPUP);
	SetWindowLong(windowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);
	ShowWindow(windowHandle, SW_SHOWMAXIMIZED);
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	RWLevel::Initialize(graphics);
	RWController::Initialize();
	RWController::LoadInitialLevel(new RWDemo_3DUI());
	
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		GetClientRect(windowHandle, &rc);
		RWController::Update();
		graphics->BeginDraw();
		RWController::Render();
		graphics->EndDraw();
	}

	delete graphics;
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	bool keys[256];
	UINT width, height;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		graphics->Resize(width, height);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYUP:
		keys[(BYTE)wParam] = false;
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
