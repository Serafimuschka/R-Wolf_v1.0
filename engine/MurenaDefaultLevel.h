#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"
//--------------------------------------------------
//	Класс:			MurenaDefaultLevel
//	Заголовок:		MurenaDefaultLevel
//	Описывает дефолтный уровень движка (прыгающий мяч)
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaDefaultLevel: public MurenaLevel {
	// Блок переменных и указателей класса:
	MurenaSpriteSheet* sprite;		// Объект класса SpriteSheet
	MurenaHPTimer* hpTimer;
	float x, y, xSpeed, ySpeed, xTracker, yTracker;
	float x0Screen, y0Screen, x1Screen, y1Screen, xAccel, yAccel;
	int deg;
public:
	float fps;
	int counter;
	int checker;
	float FPS();

	float TranslateData(float PositionX, float PositionY, float add) override;
	void TranslateRect(UINT width, UINT height) override;

	// Функция Load(): подгатавливает уровень к инициализации, загружает данные
	void Load() override;

	// Функция Unload(): выгрузка данных, деконструкция уровня
	void Unload() override;

	// Функция Update(): обновление значений хранящихся в Load() переменных перед вызовом Render()
	void Update(double timeTotal, double timeDelta) override;

	// Функция Render(): отрисовка сцены по заданным параметрам
	void Render() override;
};