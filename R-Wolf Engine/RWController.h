#pragma once

#include "RWLevel.h"
#include "RWTimer.h"

class RWController {
	RWController();
	~RWController();
	static RWLevel* currentLevel;
	static RWTimer* hpTimer;
public:
	static bool isLoading;
	static void initialize();
	static void loadInitialLevel(RWLevel* level);
	static void switchLevel(RWLevel* level);
	static void throwIntoLevel(short);
	static void throwSwitching();
	static void render();
	static void update();
};