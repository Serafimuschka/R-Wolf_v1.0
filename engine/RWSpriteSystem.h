#pragma once
#include "wincodec.h"
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
	void Draw(float x, float y);
	void Draw(int index, XMFLOAT2 coord, double opacity);
	void Texturize(XMFLOAT2 coord, XMFLOAT2 mapsize, double opacity);
};

class RWSpriteAlternative {
	RWSpriteSystem*		syst;
public:
	void Draw(LPCWSTR filename, RWGraphics* gfx, XMFLOAT2 coord, double opacity);
	void Draw(LPCWSTR filename, RWGraphics* gfx, uint32_t index, XMFLOAT2 size, XMFLOAT2 coord, double opacity);
	void Texturize(LPCWSTR filename, RWGraphics* gfx, XMFLOAT4 rect, double opacity);
};