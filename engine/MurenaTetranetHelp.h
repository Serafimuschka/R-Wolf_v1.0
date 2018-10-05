#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"

class MurenaTetranetHelpLevel : public MurenaLevel {
	// ���� ���������� � ���������� ������:
	MurenaSpriteSheet* sprite;		// ������ ������ SpriteSheet
	MurenaHPTimer* hpTimer;
public:
	float TranslateData(float PositionX, float PositionY, float add) override;
	void TranslateRect(UINT width, UINT height) override;
	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void Load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void Unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void Update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void Render() override;
};