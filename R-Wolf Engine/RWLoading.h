#pragma once
#include "RWLevel.h"
#include "RWController.h"
#include "RWGraphics.h"

class RWLoading : public RWLevel {
private:
	RWTimer* hpTimer;
	bool ready = false;
	// Строчный буфер загрузчика уровня
	wstring buff;
	// Переменные - флаги
	bool isPrevUnloaded = false;
	bool isNextReady = true;
	// Переменные с указателями на файлы:
	LPCWSTR logoName;
	// Дополнительные переменные
	int timeout;
public:
	void load() override;
	void unload() override;
	void update(double timeTotal, double timeDelta) override;
	void render() override;
};