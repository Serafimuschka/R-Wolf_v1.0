#pragma once
#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWController.h"

class MarchenweltMenu : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT4 _cgame, _csett, _cexit;
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