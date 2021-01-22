//
//
//
//
//
//	kalterseele, 2018
//

#include "RWHeaders.h"
#include "mainscreen.h"

#include <CommCtrl.h>

RWGraphics* gfx;

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// СДЕЛАТЬ FIXED-SIZE

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize	=				sizeof(WNDCLASSEX);
	wcex.hIcon =				LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor =				LoadCursor(hInst, IDC_ARROW);
	wcex.hbrBackground =		(HBRUSH)COLOR_WINDOW;
	wcex.hInstance =			hInst;
	wcex.lpfnWndProc =			windowProc;
	wcex.lpszClassName =		"VLabs";
	wcex.style =				CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);
	
	RECT rc = { 0, 0,
		1024, 788 };

	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"VLabs",
		"Visual Labs | r0001",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME,
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
	InitCommonControls();
	HMENU hMenu = CreateMenu();
	HMENU hLaser = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 1000, "&Включить лазер");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hLaser, "Установить длину волны");
	AppendMenu(hLaser, MF_STRING, 1001, "650 nm\tКрасный");
	AppendMenu(hLaser, MF_STRING, 1002, "610 nm\tОранжевый");
	AppendMenu(hLaser, MF_STRING, 1003, "580 nm\tЖёлтый");
	AppendMenu(hLaser, MF_STRING, 1004, "520 nm\tЗелёный");
	AppendMenu(hLaser, MF_STRING, 1005, "490 nm\tГолубой");
	AppendMenu(hLaser, MF_STRING, 1006, "460 nm\tСиний");
	AppendMenu(hLaser, MF_STRING, 1007, "420 nm\tФиолетовый");
	AppendMenu(hMenu, MF_STRING, 2000, "Участие в проекте");
	AppendMenu(hMenu, MF_STRING, 3000, "Обновления");

	SetMenu(windowHandle, hMenu);
	SetMenu(windowHandle, hLaser);


	//SetWindowLong(windowHandle, GWL_STYLE, WS_POPUP);
	//SetWindowLong(windowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);
	ShowWindow(windowHandle, SW_SHOWDEFAULT);
	UpdateWindow(windowHandle);

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	RWLevel::initialize(gfx);
	RWController::initialize();
	RWController::loadInitialLevel(new mainscreen());
	
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
	case WM_CLOSE:
		exit(EXIT_SUCCESS);
		break;
	case WM_DESTROY:
		exit(EXIT_SUCCESS);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1000:
			RWController::throwSwitching();
			break;
		case 1001:
			RWController::throwIntoLevel(650);
			break;
		case 1002:
			RWController::throwIntoLevel(630);
			break;
		case 1003:
			RWController::throwIntoLevel(600);
			break;
		case 1004:
			RWController::throwIntoLevel(540);
			break;
		case 1005:
			RWController::throwIntoLevel(490);
			break;
		case 1006:
			RWController::throwIntoLevel(460);
			break;
		case 1007:
			RWController::throwIntoLevel(420);
			break;
		case 2000:
			system("start http://www.vk.com");
			break;
		case 3000:
			system("start http://www.vk.com");
			break;
		}
		break;
	case WM_SIZE:
		gfx->resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		default:
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
