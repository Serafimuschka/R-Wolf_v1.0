//
//
//
//
//
//	kalterseele, 2018
//

#include "RWHeaders.h"
#include "RW-Demo-3D-UI.h"
#include "Demo-Map.h"

RWGraphics* gfx;

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize	=				sizeof(WNDCLASSEX);
	wcex.hIcon =				LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor =				LoadCursor(hInst, IDC_HAND);
	wcex.hbrBackground =		(HBRUSH)COLOR_WINDOW;
	wcex.hInstance =			hInst;
	wcex.lpfnWndProc =			windowProc;
	wcex.lpszClassName =		"RWolf";
	wcex.style =				CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);
	
	RECT rc = { 0, 0,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"RWolf",
		"R-Wolf 2D Graphics Engine",
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
		return EXIT_FAILURE;
	}

	gfx = new RWGraphics();

	if (!gfx->init(windowHandle)) {
		MessageBox(NULL, "Window handle initialization failed", "Critical error", MB_ICONWARNING);
		delete gfx;
		return EXIT_FAILURE;
	}

	SetWindowLong(windowHandle, GWL_STYLE, WS_POPUP);
	SetWindowLong(windowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);
	ShowWindow(windowHandle, SW_SHOWMAXIMIZED);
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	RWLevel::initialize(gfx);
	RWController::initialize();
	RWController::loadInitialLevel(new RWDemo_3DUI());
	
	MSG msg;
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		GetClientRect(windowHandle, &rc);
		RWController::update();
		gfx->beginDraw();
		RWController::render();
		gfx->endDraw();
	}

	delete gfx;
	return EXIT_SUCCESS;
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_SIZE:
		gfx->resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
