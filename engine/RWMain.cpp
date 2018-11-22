#include <Windows.h>
#include <wchar.h>
#include "resource.h"
#include "RWGlobalDefinitions.h"
#include "RWGraphics.h"
#include "RWLevel.h"
#include "RWMainMenu.h"
#include "RWController.h"

int console = 1;
float mod = 0.0f;
float accel = 0.0f;

RWGraphics* graphics;
RWLevel* lev;
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
		MessageBox(NULL, "Error: 1E :: CreateWindowEx failed", "Excuse me what the fuck?", MB_OK);
		return -1;
	}
	graphics = new RWGraphics();
	if (!graphics->Init(windowHandle)) {
		MessageBox(NULL, "Error: 2E :: Initialization failed", "Excuse me what the fuck?", MB_OK);
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
	RWController::LoadInitialLevel(new RWMainMenu());
	
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		else {
			GetClientRect(windowHandle, &rc);
			RWController::CurrentRect(rc.right - rc.left, rc.bottom - rc.top);
			RWController::Update();
			graphics->BeginDraw();
			RWController::Render();
			graphics->EndDraw();
		}
	}

	delete graphics;
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		graphics->Resize(width, height);
	}
		break;
	case WM_LBUTTONDOWN:
		// sound
		RWController::SendAction(RW_ACTION_SHOOT);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP:
			RWController::SendCoordinates(XMFLOAT2(0, 1));
			break;
		case VK_LEFT:
			RWController::SendCoordinates(XMFLOAT2(-1, 0));
			break;
		case VK_RIGHT:
			RWController::SendCoordinates(XMFLOAT2(1, 0));
			break;
		case VK_DOWN:
			RWController::SendCoordinates(XMFLOAT2(0, -1));
			break;

		case 0x57:	// W
			RWController::SendCoordinates(XMFLOAT2(0, 1));
			break;
		case 0x41:	// A
			RWController::SendCoordinates(XMFLOAT2(-1, 0));
			break;
		case 0x44:	// D
			RWController::SendCoordinates(XMFLOAT2(1, 0));
			break;
		case 0x53:	// S
			RWController::SendCoordinates(XMFLOAT2(0, -1));
			break;

		case VK_SPACE:
			RWController::SendAction(RW_ACTION_JUMP);
			break;

		case VK_SHIFT:
			break;
		case VK_CONTROL:
			break;
		case VK_F1:
			MessageBox(NULL, "О проекте\nАвтор: Kalterseele", "About", MB_OK);
			break;
		case VK_F11:
			break;
		case VK_F12:
			break;
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		default:
			//RWController::TranslateSymbol((WCHAR)wParam, wParam);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
