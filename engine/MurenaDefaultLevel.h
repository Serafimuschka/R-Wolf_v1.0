#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"
//--------------------------------------------------
//	�����:			MurenaDefaultLevel
//	���������:		MurenaDefaultLevel
//	��������� ��������� ������� ������ (��������� ���)
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaDefaultLevel: public MurenaLevel {
	// ���� ���������� � ���������� ������:
	MurenaSpriteSheet* sprite;		// ������ ������ SpriteSheet
	MurenaHPTimer* hpTimer;
	float x, y, xSpeed, ySpeed, xTracker, yTracker;
	float x0Screen, y0Screen, x1Screen, y1Screen, xAccel, yAccel;
	int deg;
public:
	float fps;
	int counter;
	int checker;
	float FPS();

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