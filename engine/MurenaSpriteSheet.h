#pragma once
#include "wincodec.h"
#include "MurenaGraphics.h"

//--------------------------------------------------
//	Класс:			MurenaSpriteSheet
//	Заголовок:		MurenaSpriteSheet
//	Описывает модуль преобразования изображений и
//	покадровой анимации
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaSpriteSheet {
	Graphics*			gfx;
	ID2D1Bitmap*		bmp;
	int spriteWidth, spriteHeight;
	int spritesAcross;

public:
	MurenaSpriteSheet(LPCWSTR filename, Graphics* gfx);
	MurenaSpriteSheet(LPCWSTR filename, Graphics* gfx, int spriteWidth, int spriteHeight);
	~MurenaSpriteSheet();
	void Draw(float x, float y);
	void Draw(int index, int x, int y, int deg);
};