#pragma once
#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWController.h"

class MarchenweltMenu : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT4 _cgame, _csett, _cexit;
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