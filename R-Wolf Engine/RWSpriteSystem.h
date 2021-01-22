#pragma once


#include "RWGraphics.h"

class RWSpriteSystem {
	RWGraphics*			gfx;
	ID2D1Bitmap*		bmp;
	int spriteWidth, spriteHeight;
	int spritesAcross;

public:
	RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx);
	RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx, int spriteWidth, int spriteHeight);
	~RWSpriteSystem();
	void draw(XMFLOAT2 coord);
	void draw(int index, XMFLOAT2 coord, double opacity);
	void texturize(XMFLOAT2 coord, XMFLOAT2 mapsize, double opacity);
};

class RWSpriteSystemA {
	static RWSpriteSystem*		rwss;
public:
	void draw(LPCWSTR filename, RWGraphics* gfx, XMFLOAT2 coord, double opacity);
	void draw(LPCWSTR filename, RWGraphics* gfx, unsigned int index,
		XMFLOAT2 size, XMFLOAT2 coord, double opacity);
	void texturize(LPCWSTR filename, RWGraphics* gfx, XMFLOAT4 rectangle, double opacity);
};