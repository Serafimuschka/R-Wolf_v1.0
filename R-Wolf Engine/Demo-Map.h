#pragma once
#include <atltime.h>

#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWController.h"

class Map : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT2 mapPos;
	int _rDest, _bDest, _tDest;
	double bottomDelta, rightDelta, textDelta;
	bool _rWasClicked, _bWasClicked, _tWasClicked;
	bool _rBackward, _bBackward, _tBackward;
	bool markerP, markerT;
	bool aboutIn, textIn;
	XMFLOAT2 _beforeClickPos, _map, _from, _to;
	XMFLOAT2 _pointFrom, _pointTo;
	D2D1_COLOR_F bottomColor, rightColor,
		aboutColor, textColor, audioColor,
		backColor;
	wstring time;
	POINT cursorPos;
public:
	// Функция Load(): подгатавливает уровень к инициализации, загружает данные
	void load() override;
	// Функция Unload(): выгрузка данных, деконструкция уровня
	void unload() override;
	// Функция Update(): обновление значений хранящихся в Load() переменных перед вызовом Render()
	void update(double timeTotal, double timeDelta) override;
	// Функция Render(): отрисовка сцены по заданным параметрам
	void render() override;
};