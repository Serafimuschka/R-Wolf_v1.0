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

	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void Load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void Unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void Update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void Render() override;
};