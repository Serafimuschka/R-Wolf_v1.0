#include "MurenaGraphics.h"
#include "MurenaController.h"
#include "MurenaDefaultLevel.h"

//--------------------------------------------------
//	�����:			MurenaDefaultLevel
//	��������:		MurenaDefaultLevel
//	������������� ��������� ������� ������ (��������� ���)
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
void MurenaDefaultLevel::Load() {
	fps = 0.0f;
	checker = 0;
	counter = 0;
	x = 70;
	y = 220;
	xSpeed = 0;		xAccel = 0;		xTracker = 228;
	ySpeed = 0;		yAccel = 0;		yTracker = 72;
	deg = 0;
	x0Screen = 0;		y0Screen = 0;
	x1Screen = 800;		y1Screen = 600;
	sprite = new MurenaSpriteSheet((LPCWSTR)L"test.png", gfx, 50, 50);
	// PlaySound("test.wav", NULL, SND_FILENAME);	// ������ winmm.lib - �������� �������
}
/*
	���������� ������ ���������� ������:
		1. ����� ������� ���������� �������������� ������������:
		(x0Screen, y0Screen) && (x1Screen, y1Screen)
		/ - - - /
		2. ������ ��� ����� ����� ������������� ���������:
		x1Screen - 10; � ���� ��������
		/ - - - /
		3. ������, ��� ��������� ��������� ������, � ������ ��� ��� ����������:
		xAccel; yAccel
		/ - - - /
		4. ������, ��� ��� ������ ��������:
			���� ����������� ������ (�����) ��������� ����������� ��� �� ����� ����, �� ����������� ������������ ���� ����,
			� �������� ��������� ����� �� �����. ���� ����� ��������� ���� x[x1Screen-50; x1Screen], �� xAccel �������� ���������.
			��� ����������� �������� � ��������, ����� ������������ ������� �����, ��������� �� ������������.
		/ - - - /
*/
void MurenaDefaultLevel::Unload() {
	delete sprite;
}
void MurenaDefaultLevel::TranslateRect(UINT w, UINT h) {
	UNREFERENCED_PARAMETER(w);
	UNREFERENCED_PARAMETER(h);
}
void MurenaDefaultLevel::Update(double timeTotal, double timeDelta) {
	x += xSpeed;
	y += ySpeed;
	if (x <= (x0Screen + 50)) {
		x = (x0Screen + 50);
		xAccel++;
	}
	if (x >= (x0Screen + 90)) {
		x = (x0Screen + 90);
		xAccel--;
	}
	if (y <= (y0Screen + 200)) {
		y = (y0Screen + 200);
		yAccel++;
	}
	if (y >= (y0Screen + 240)) {
		y = (y0Screen + 240);
		yAccel--;
	}
	if ((xTracker == 650) && (yTracker == 500)) {
		xAccel = 0;			yAccel = 0;
		xTracker = 650;		yTracker = 500;
		deg = 58;
	}
}
float MurenaDefaultLevel::TranslateData(float PositionX, float PositionY, float add) {
	xSpeed = (PositionX * add);
	ySpeed = (PositionY * add);
	return xSpeed, ySpeed;
}
// ��������� �������, ������� �� ����� �������� ������ �� SYSTEMTIME, � ����� ������� ��������� �� float
float MurenaDefaultLevel::FPS() {
	counter++; // ����� ���������� �����������
	checker++;
	if (checker == 61) {
		checker = 1;
		counter = 1;
	}
	fps = counter;
	return fps;
}
void MurenaDefaultLevel::Render() {
	gfx->ClearScreen(30, 30, 30);

	gfx->DrawLine(x0Screen, y1Screen - 25, x1Screen, y1Screen - 25, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen, y0Screen + 45, x1Screen, y0Screen + 45, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen, y0Screen, y1Screen, y0Screen, 173, 255, 47, 255);
	gfx->DrawLine(x1Screen, y0Screen, x1Screen, y1Screen, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen, y1Screen, x1Screen, y1Screen, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen, y0Screen, x0Screen, y1Screen, 173, 255, 47, 255);

	gfx->DrawLine(x0Screen + 50, y0Screen + 200, x0Screen + 100, y0Screen + 200, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen + 50, y0Screen + 250, x0Screen + 100, y0Screen + 250, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen + 50, y0Screen + 200, x0Screen + 50, y0Screen + 250, 173, 255, 47, 255);
	gfx->DrawLine(x0Screen + 100, y0Screen + 200, x0Screen + 100, y0Screen + 250, 173, 255, 47, 255);

	gfx->DrawLine(x0Screen + 650, y0Screen + 500, x0Screen + 700, y0Screen + 500, 255, 69, 0, 255);
	gfx->DrawLine(x0Screen + 650, y0Screen + 550, x0Screen + 700, y0Screen + 550, 255, 69, 0, 255);
	gfx->DrawLine(x0Screen + 650, y0Screen + 500, x0Screen + 650, y0Screen + 550, 255, 69, 0, 255);
	gfx->DrawLine(x0Screen + 700, y0Screen + 500, x0Screen + 700, y0Screen + 550, 255, 69, 0, 255);

	gfx->DrawRectangle(x, y, 10, 10, 173, 255, 47, 255);
	gfx->DrawRectangle(xTracker - xAccel, yTracker - yAccel, 50, 50, 173, 255, 47, 255);
	gfx->PrintText((LPWSTR)L"�������� �������: �������� ������������ ������������� ����", 58, 5, 580, 171, 255, 47, 255);
	gfx->PrintText((LPWSTR)L"����������, �� ������ �����������! Press F to pay recpects", deg, 5, 565, 255, 69, 0, 255);
	gfx->PrintText((LPWSTR)L"��� ���� ����������\n��������� SHIFT ��� ��������� ������������ � CTRL ��� ��� ����������\n�� ������� ��������� �����������\n����� ������ ����� � ���� � ������ �����������", 168, 110, 197, 171, 255, 47, 255);

	FPS();
	sprite->Draw(0, 100, 100, 0);
	gfx->PrintInfo(fps, 2, 10, 10, 173, 255, 47, 255);

	gfx->PrintText((LPWSTR)L"xSpeed =", 8, 10, 50, 171, 255, 47, 255);
	gfx->PrintText((LPWSTR)L"ySpeed =", 8, 10, 60, 171, 255, 47, 255);
	gfx->PrintInt(xSpeed, 2, 70, 50, 255, 69, 0, 255);
	gfx->PrintInt(-1 * ySpeed, 2, 70, 60, 255, 69, 0, 255);
}