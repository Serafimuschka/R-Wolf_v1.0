#pragma once

#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWController.h"

class RWDemo_3DUI : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT2 pointA, pointB, pointC, pointD;
	double n, m;
	POINT cursorPos;
public:
	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void render() override;
};