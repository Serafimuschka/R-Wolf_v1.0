#pragma once

#include "RWGraphics.h"
#include "RWSpriteSystem.h"

class RWLevel {
protected:
	HRESULT					hres;
	FLOAT					dtime, ttime;
	WCHAR*					con_in;

	static RWGraphics*				core;
	static RWSpriteSystem*			picture;
	static RWSpriteSystem*			tex;
	static RWSpriteAlternative*		sprite;
public:
	XMFLOAT2				mapsize;
	XMFLOAT2				startpos;
	XMFLOAT2				objectpos;
	UINT					encounter;
	DOUBLE					speed;
	INT						anim, action;
	UINT					ScreenWidth = GetSystemMetrics(SM_CXSCREEN), 
							ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	wstring					AdapterName, buildnum, buildname;
	wstring					CurrentLevelName;

	static void initialize(RWGraphics* graphics) {
		core = graphics;
	}

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void update(double timeTotal, double timeDelta) = 0;
	virtual void render() = 0;
};