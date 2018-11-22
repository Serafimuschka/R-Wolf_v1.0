#pragma once
#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWTimer.h"

class RWController {
	RWController();
	static RWLevel* currentLevel;
	static RWTimer* hpTimer;
public:
	static bool IsLoading;
	static void CurrentRect(UINT width, UINT height);
	static void SendCoordinates(XMFLOAT2 vec);
	static void SendAction(UINT code);
	static void Initialize();
	static void LoadInitialLevel(RWLevel* level);
	static void SwitchLevel(RWLevel* level);
	static void Render();
	static void Update();
	static LPCWSTR TranslateSymbol(WCHAR in, WPARAM com);
};