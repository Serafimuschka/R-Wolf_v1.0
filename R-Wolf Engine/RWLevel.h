#pragma once

#include "RWGraphics.h"
#include "RWSpriteSystem.h"

class RWLevel {
protected:
	static RWGraphics*				core;
	// ÂÍÈÌÀÍÈÅ: ÓÑÒÀÐÅÂØÈÅ ÊËÀÑÑÛ
	// Áóäóò âñêîðå óäàëåíû èç óðîâíÿ è èñïîëüçîâàòüñÿ íà íàòèâíîì óðîâíå
	// -->
	static RWSpriteSystem*			picture;
	static RWSpriteSystem*			tex;
	// <--
	static RWSpriteSystemA*			sprite;
public:
	UINT							ScreenWidth = GetSystemMetrics(SM_CXSCREEN), 
									ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	short buffer;
	bool switcher;
	static void initialize(RWGraphics* graphics) {
		core = graphics;
	}

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void update(double timeTotal, double timeDelta) = 0;
	virtual void render() = 0;
};