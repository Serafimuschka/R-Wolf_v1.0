#pragma once
#include "MurenaLevel.h"
#include "MurenaGraphics.h"
#include "MurenaHPTimer.h"

//--------------------------------------------------
//	�����:			MurenaController
//	���������:		MurenaController
//	��������� ���� ����������� �������� ����� ��������
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaController {
	MurenaController();
	static MurenaLevel* currentLevel;
	static MurenaHPTimer* hpTimer;
public:
	static bool IsLoading;
	static void CurrentRect(UINT width, UINT height);
	static void SendCoordinates(float x, float y, float add);
	static void Initialize();
	static void LoadInitialLevel(MurenaLevel* level);
	static void SwitchLevel(MurenaLevel* level);
	static void Render();
	static void Update();
	static LPCWSTR TranslateSymbol(LPCWSTR symbol);
};