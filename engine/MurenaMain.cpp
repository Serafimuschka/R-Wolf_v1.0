#include <Windows.h>
#include <wchar.h>
#include "resource.h"
#include "MurenaGraphics.h"
#include "MurenaDefaultLevel.h"
#include "MurenaMenu.h"
#include "MurenaTetranetLevel.h"
#include "MurenaController.h"

//--------------------------------------------------
//	Исходник:		MurenaMain
//	Является точкой входа в процедуру приложения
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
int console = 1;
float mod = 0.0f;
float accel = 0.0f;
Graphics* graphics;
MurenaLevel* lev;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
								ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize					= sizeof(WNDCLASSEX);
	wcex.hIcon					= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hbrBackground			= (HBRUSH)COLOR_WINDOW;
	wcex.hInstance				= hInst;
	wcex.lpfnWndProc			= WindowProc;
	wcex.lpszClassName			= "Murena";
	wcex.style					= CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	HWND windowHandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"Murena",
		"MURENA2 GRAPHICS ENGINE",
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
	graphics = new Graphics();
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

	MurenaLevel::Initialize(graphics);
	MurenaController::Initialize();
	MurenaController::LoadInitialLevel(new MurenaMenu());
	
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		else {
			GetClientRect(windowHandle, &rc);
			MurenaController::CurrentRect(rc.right - rc.left, rc.bottom - rc.top);
			MurenaController::Update();
			graphics->BeginDraw();
			MurenaController::Render();
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
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_OEM_3:
			MurenaController::SendCoordinates(NULL, NULL, -1);
			break;
		case VK_LEFT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_RIGHT:
			break;
		case VK_SHIFT:
			break;
		case VK_CONTROL:
			break;
		case VK_F1:
			MessageBox(NULL, "О проекте\nАвтор: Einhorn32\nКоманда отладки:\nEinhorn32\nТестеры:\nNesty\n(c)2018", "About", MB_OK);
			break;
		case VK_F11:
			// MurenaController::SwitchLevel(new MurenaTetranetLevel());
			break;
		case VK_F12:
			// MurenaController::SwitchLevel(new MurenaDefaultLevel());
			break;
		case VK_RETURN:
			//lev->ConsoleInput = L"";
			break;
		case VK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
