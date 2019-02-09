#pragma once
#include "RWLevel.h"
#include "RWController.h"
#include "RWGraphics.h"

class RWLoading : public RWLevel {
private:
	RWTimer* hpTimer;
	bool ready = false;
	// �������� ����� ���������� ������
	wstring buff;
	// ���������� - �����
	bool isPrevUnloaded = false;
	bool isNextReady = true;
	// ���������� � ����������� �� �����:
	LPCWSTR logoName;
	// �������������� ����������
	int timeout;
public:
	void load() override;
	void unload() override;
	void update(double timeTotal, double timeDelta) override;
	void render() override;
};