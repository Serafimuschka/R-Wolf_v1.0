#include "mainscreen.h"

#define J0 1
#define A 0.001
#define N 4.0
#define K 3.0

inline XMFLOAT4 colorlength(float lambda, float lum, float sat = 1.0)
{
	float h = 280.0F + (280.0F / 230.0F) * (420.0F - lambda);
	//float h = 280;
	float c = (1.0F - abs(2.0F * lum - 1.0F)) * sat;
	float x = c * (1.0F - abs(fmod((h / 60.0F), 2.0F) - 1.0F));
	float m = lum - c / 2.0F;

	if (h >= 0 && h <= 60)				return		XMFLOAT4(255.0F * (c + m), 255.0F * (x + m), 255.0F * (0 + m), 255);
	else if (h >= 60 && h <= 120)		return		XMFLOAT4(255.0F * (x + m), 255.0F * (c + m), 255.0F * (0 + m), 255);
	else if (h >= 120 && h <= 180)		return		XMFLOAT4(255.0F * (0 + m), 255.0F * (c + m), 255.0F * (x + m), 255);
	else if (h >= 180 && h <= 240)		return		XMFLOAT4(255.0F * (0 + m), 255.0F * (x + m), 255.0F * (c + m), 255);
	else if (h >= 240 && h <= 300)		return		XMFLOAT4(255.0F * (x + m), 255.0F * (0 + m), 255.0F * (c + m), 255);
	else if (h >= 300 && h <= 360)		return		XMFLOAT4(255.0F * (c + m), 255.0F * (0 + m), 255.0F * (x + m), 255);
	else								return		XMFLOAT4(0, 0, 0, 0);
}

inline double difr(double slitWidth, double waveLength, double iterator)
{
	auto arg = (PI * slitWidth * iterator) / waveLength;
	return J0 * pow(sin(arg), 2) * pow(1.0 / arg, 2);
}

inline double fx(double in, double iterator)
{
	auto pta = log10(1 + sqrt(in + A)) - log10(1 + sqrt(A));
	auto ptb = log10(1 + sqrt(1 + A)) - log10(1 + sqrt(A));
	auto ptc = 0.7 / (1.0 + 1.0 / pow(K, 1.0 / N));
	auto ptd = 1.0 + 1.0 / pow(in * K, 1.0 / N);

	return (pta / ptb) * ptc * ptd;
}

void mainscreen::load()
{
	switcher = false;
	slitPosCenter = XMFLOAT2(512, 250);
	lasPosBegin = XMFLOAT2(512, 212.5);
	slitWidth = 4.5;
	buffer = 0;
	wavelength = 650;
	screenDistance = 0.2;
	wave.x = 825;
	wave.y = 250;
	slit.y = 250;
	screen.y = 250;
	slit.x = 875;
	screen.x = 925;
	wave.z = wavelength;
	slit.z = slitWidth;
	screen.z = screenDistance;
	manualHeader = L"Порядок выполнения работы:\n";
	manualContent = L"1. Включить лазер, используя соответствующую кнопку меню;\n";
	manualContent += L"2. Установить значения длины волны и расстояние до экрана;\n";
	manualContent += L"3. Установить такую ширину щели, чтобы ширина полос была удобной для наблюдения;\n";
	manualContent += L"4. Снять измерения и обработать результаты.\n";
}


void mainscreen::update(double td, double tt)
{
	GetCursorPos(&cPos);
	ScreenToClient(core->getHwnd(), &cPos);
	mouse = XMFLOAT2(cPos.x, cPos.y);
	if (buffer) wavelength = buffer;
	buffer = 0;
	slitWidthStr = L"";
	screenDistanceStr = L"";
	wavelenStr = L"";
	slitWidthStr += L"b = " + to_wstring(100 * slitWidth) + L" \u00b5m\n";
	wavelenStr += L"\u03bb = " + to_wstring(wavelength) + L" nm\n";
	screenDistanceStr += L"l = " + to_wstring(screenDistance) + L" m\n";

	if (GetAsyncKeyState(VK_LBUTTON) && mouse.x >= wave.x - 15 && mouse.x <= wave.x + 15 && mouse.y > wave.y - 10 && mouse.y < wave.y + 10)
	{
		onWave = true;
		wave.y = mouse.y;
		wave.z = 650 - (230.0 / 250.0) * (wave.y - 250.0);
		wavelength = wave.z;
		if (mouse.x != wave.x)
		{
			cPos.x = wave.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 250)
		{
			cPos.x = wave.x;
			cPos.y = 250;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500)
		{
			cPos.x = wave.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onWave = false;

	if (GetAsyncKeyState(VK_LBUTTON) && mouse.x >= slit.x - 15 && mouse.x <= slit.x + 15 && mouse.y > slit.y - 10 && mouse.y < slit.y + 10)
	{
		onSlit = true;
		slit.y = mouse.y;
		slit.z = (15.0 / 250.0) * (slit.y - 250.0);
		slitWidth = slit.z;
		if (mouse.x != slit.x)
		{
			cPos.x = slit.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 250)
		{
			cPos.x = slit.x;
			cPos.y = 250;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500)
		{
			cPos.x = slit.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onSlit = false;

	if (GetAsyncKeyState(VK_LBUTTON) && mouse.x >= screen.x - 15 && mouse.x <= screen.x + 15 && mouse.y > screen.y - 10 && mouse.y < screen.y + 10)
	{
		onScreen = true;
		screen.y = mouse.y;
		screen.z = (1.0 / 250.0) * (screen.y - 250.0);
		screenDistance = screen.z;
		if (mouse.x != screen.x)
		{
			cPos.x = screen.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 250)
		{
			cPos.x = screen.x;
			cPos.y = 250;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500)
		{
			cPos.x = screen.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onScreen = false;

	if (onWave) lenClr = core->darkRed;
	else lenClr = core->darkSlateBlue;

	if (onSlit) slitClr = core->darkRed;
	else slitClr = core->darkSlateBlue;

	if (onScreen) screenClr = core->darkRed;
	else screenClr = core->darkSlateBlue;

	if (switcher) laserEn = core->greenYellow;
	else laserEn = core->red;
}

void mainscreen::render()
{
	// Фоновый цвет
	core->clearScreen(core->darkGray);

	// Отрисовка экрана
	core->drawRectangle(XMFLOAT4(0, 0, 1024, 150), core->black, 1.0, true);

	// Отрисовка размеров
	core->drawLine(XMFLOAT4(slitPosCenter.x, slitPosCenter.y, slitPosCenter.x, slitPosCenter.y + 20.0), core->black, 1.0);
	core->drawLine(XMFLOAT4(slitPosCenter.x, slitPosCenter.y, slitPosCenter.x + 100.0, slitPosCenter.y - 100.0), core->black, 1.0);
	core->drawLine(XMFLOAT4(slitPosCenter.x, slitPosCenter.y, slitPosCenter.x + 200.0, slitPosCenter.y), core->black, 1.0);
	core->printText(slitWidthStr.c_str(), XMFLOAT2(640, slitPosCenter.y), core->black, 15.0, L"Consolas");
	core->printText(screenDistanceStr.c_str(), XMFLOAT2(640, slitPosCenter.y - 20), core->black, 15.0, L"Consolas");
	core->printText(wavelenStr.c_str(), XMFLOAT2(640, slitPosCenter.y + 80), core->black, 15.0, L"Consolas");
	core->printText(L"Линейка, \u00b5m\n", XMFLOAT2(5, 170), core->black, 15.0, L"Consolas");


	// Отрисовка шторки с щелью
	auto shutterLeftX = slitPosCenter.x - slitWidth / 8.0 - 50.0;
	auto shutterRightX = slitPosCenter.x + slitWidth / 8.0 + 50.0;
	core->drawRectangle(XMFLOAT4(shutterLeftX, slitPosCenter.y, shutterLeftX + 50.0, slitPosCenter.y - 75.0), core->slateBlue, 1.0, true);
	core->drawRectangle(XMFLOAT4(shutterRightX, slitPosCenter.y, shutterRightX - 50.0, slitPosCenter.y - 75.0), core->slateBlue, 1.0, true);
	core->drawRectangle(XMFLOAT4(shutterLeftX, slitPosCenter.y, shutterRightX, slitPosCenter.y - 75.0), core->blue, 1.0);

	// Отрисовка лазерного луча и диф картины
	if (switcher) 
	{ 
		core->drawLine(XMFLOAT4(150, 618, lasPosBegin.x, lasPosBegin.y), colorlength(wavelength, 0.5), 3.5);
		//core->drawLine(XMFLOAT4(512, 0, 512, 150), colorlength(wavelength, 1));
		for (short i = 0; i < 512; i++)
		{
			auto d = fx(difr(slitWidth, wavelength, i), i);
			if (!i) core->drawLine(XMFLOAT4(512, 0, 512, 150), colorlength(wavelength, d));
			else
			{
				core->drawLine(XMFLOAT4(512 - i, 0, 512 - i, 150), colorlength(wavelength, d));
				core->drawLine(XMFLOAT4(512 + i, 0, 512 + i, 150), colorlength(wavelength, d));
			}
		}
	}

	// Отрисовка сетки
	for (short x = 0; x < 512; x += 64)
	{
		core->drawLine(XMFLOAT4(512 - x, 125, 512 - x, 150), core->white, 1.0);
		core->drawLine(XMFLOAT4(512 + x, 125, 512 + x, 150), core->white, 1.0);
		core->printText(to_wstring(100 + 100 * x / 64).c_str(), XMFLOAT2(440 - x, 150), core->white, 15.0, L"Consolas");
		core->printText(to_wstring(100 + 100 * x / 64).c_str(), XMFLOAT2(568 + x, 150), core->white, 15.0, L"Consolas");
	}
	core->printText(to_wstring(0).c_str(), XMFLOAT2(508, 150), core->white, 15.0, L"Consolas");
	for (float x = 64.0F/5.0F; x < 512; x += 64.0F/5.0F)
	{
		core->drawLine(XMFLOAT4(512 - x, 135, 512 - x, 150), core->white, 1.0);
		core->drawLine(XMFLOAT4(512 + x, 135, 512 + x, 150), core->white, 1.0);
	}

	// Отрисовка компонентов управления
	core->printText(L"\u03bb     b     l\n", XMFLOAT2(wave.x - 5, 215), core->black, 15.0, L"Consolas");
	core->printText(L"Элементы управления\n", XMFLOAT2(wave.x - 30, 195), core->black, 15.0, L"Consolas");

	core->drawLine(XMFLOAT4(wave.x, 250, wave.x, 500), core->black);
	core->drawLine(XMFLOAT4(slit.x, 250, slit.x, 500), core->black);
	core->drawLine(XMFLOAT4(screen.x, 250, screen.x, 500), core->black);

	core->drawRectangle(XMFLOAT4(wave.x - 15, wave.y - 10, wave.x + 15, wave.y + 10), lenClr, 1, true);
	core->drawLine(XMFLOAT4(wave.x - 10, wave.y, wave.x + 10, wave.y), core->black);

	core->drawRectangle(XMFLOAT4(slit.x - 15, slit.y - 10, slit.x + 15, slit.y + 10), slitClr, 1, true);
	core->drawLine(XMFLOAT4(slit.x - 10, slit.y, slit.x + 10, slit.y), core->black);

	core->drawRectangle(XMFLOAT4(screen.x - 15, screen.y - 10, screen.x + 15, screen.y + 10), screenClr, 1, true);
	core->drawLine(XMFLOAT4(screen.x - 10, screen.y, screen.x + 10, screen.y), core->black);

	// Отрисовка тела лазера
	core->drawCircle(XMFLOAT2(150, 618), XMFLOAT2(25, 25), core->black, 1.0, true);
	for (short i = 0; i < 360; i++)
	{
		auto bx = 150 + 25 * cos(i);
		auto by = 617 + 25 * sin(i);
		core->drawLine(XMFLOAT4(bx, by, bx - 100, by + 100), core->black);
	}
	core->drawCircle(XMFLOAT2(50, 718), XMFLOAT2(25, 25), core->black, 1.0, true);
	core->drawCircle(XMFLOAT2(150, 618), XMFLOAT2(5, 5), laserEn, 1.0, true);

	// Отрисовка руководства
	core->printText(manualHeader.c_str(), XMFLOAT2(300, 500), core->darkGreen, 20, L"Consolas");
	core->printText(manualContent.c_str(), XMFLOAT2(300, 550), core->black, 15, L"Consolas");
}

void mainscreen::unload()
{

}