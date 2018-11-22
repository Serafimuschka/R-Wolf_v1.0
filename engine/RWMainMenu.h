#pragma once
#include "RWSpriteSystem.h"
#include "RWLevel.h"
#include "RWTimer.h"
#include "RWSound.h"

class RWMainMenu : public RWLevel {

	RWTimer* hpTimer;

public:

	double TranslateData(XMFLOAT2 vec) override;
	void Action(UINT code) override;
	void TranslateRect(UINT width, UINT height) override;
	void GetConsoleInput(WCHAR* input) override;

	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void Load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void Unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void Update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void Render() override;
};