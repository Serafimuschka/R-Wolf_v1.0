#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"
#include <ddraw.h>

//--------------------------------------------------
//	�����:			MurenaMenuLevel
//	���������:		MurenaMenuLevel
//	��� ���������� ���������� ������ Guitar Storm, �� ��� ���� ���� ���-�� ������ � ��������
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaMenuLevel : public MurenaLevel {

	MurenaSpriteSheet* sprite;
	MurenaHPTimer* hpTimer;

	/// GUITAR STORM ADDON FUNCTIONS -->
	std::wstring songname, author, difficulty, info_string, multiplier;
	LPCSTR patternsoundname;
	bool lineTrigger, patternTrigger, verColTrigger, prevCollided;
	float dSpeed, size;
	float tcDistance;
	int bpm;
	float tact1, tact2, tact3, tact4, tact5;
	int score, mul, last;
	double song, currentPoint, currentBuffer[1024];
	void SetBPM(int bpms);
	void LCD(XMFLOAT2 coord, float size, int input, D2D1_COLOR_F color = gfx->GreenYellow);
	void CreateLCDCascade(XMFLOAT2 coord, float size, const wchar_t* input, D2D1_COLOR_F color = gfx->Red);
	void CreateLCDCascade(XMFLOAT2 coord, float size, float input, D2D1_COLOR_F color = gfx->Red);
	void CreateLCDCascade(XMFLOAT2 coord, float size, int input, D2D1_COLOR_F color = gfx->Red);
	void CreateProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double in, D2D1_COLOR_F color = gfx->Red);
	void CreateProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double in, XMFLOAT4 color);
	double NotBiggerThan(double size, double number);
	bool IsCollidingWithDimension(XMFLOAT2 diapason, double enter, bool key);
	void DrawPattern(UINT pattern);
	void DrawNote(int finger, int string, int fret, double pos, int currentnum);
	void Beep(DWORD dwFrequency, DWORD dwMilliseconds);
	/// <--

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

	/*void SST_OpenChannel_Mono() override;
	void SST_CloseChannel_Mono() override;
	void SST_InitializeDevices() override;
	float SST_ConvertToDecibels() override;
	float SST_ConvertToHertz() override;
	bool SST_PlaySound(LPSTR name) override;*/
};