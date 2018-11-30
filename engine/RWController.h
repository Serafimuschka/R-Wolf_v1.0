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
	static void Initialize();
	static void LoadInitialLevel(RWLevel* level);
	static void SwitchLevel(RWLevel* level);
	static void Render();
	static void Update();
};