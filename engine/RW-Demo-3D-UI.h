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
	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void Load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void Unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void Update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void Render() override;
};