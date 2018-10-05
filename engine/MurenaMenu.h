#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"

class MurenaMenu : public MurenaLevel {

	MurenaSpriteSheet* sprite;
	MurenaHPTimer* hpTimer;

public:

	float TranslateData(float PositionX, float PositionY, float add) override;
	void TranslateRect(UINT width, UINT height) override;
	void ShowData(float fpsVar, BOOL memUsedVar, BOOL memPeakVar) override;
	void GetConsoleInput(LPCWSTR input) override;

	// Функция Load(): подгатавливает уровень к инициализации, загружает данные
	void Load() override;
	// Функция Unload(): выгрузка данных, деконструкция уровня
	void Unload() override;
	// Функция Update(): обновление значений хранящихся в Load() переменных перед вызовом Render()
	void Update(double timeTotal, double timeDelta) override;
	// Функция Render(): отрисовка сцены по заданным параметрам
	void Render() override;
};