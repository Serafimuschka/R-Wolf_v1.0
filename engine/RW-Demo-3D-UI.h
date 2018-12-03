#pragma once
#include "RWSpriteSystem.h"
#include "RWLevel.h"
#include "RWTimer.h"
#include "RWSound.h"

class RWDemo_3DUI : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT2 pointA, pointB, pointC, pointD;
	double n, m;
	POINT cursorPos;
public:
	// Функция Load(): подгатавливает уровень к инициализации, загружает данные
	void Load() override;
	// Функция Unload(): выгрузка данных, деконструкция уровня
	void Unload() override;
	// Функция Update(): обновление значений хранящихся в Load() переменных перед вызовом Render()
	void Update(double timeTotal, double timeDelta) override;
	// Функция Render(): отрисовка сцены по заданным параметрам
	void Render() override;
};