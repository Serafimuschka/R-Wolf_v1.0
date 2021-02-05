#include "mainscreen.h"

#define J0 2
#define A 0.001
#define N 4.0
#define K 3.0

inline XMFLOAT4 colorlength(float lambda, float lum, float sat = 1.0F)
{
	float h = 280.0F + (280.0F / 230.0F) * (420.0F - lambda);
	float c = (1.0F - abs(2.0F * lum - 1.0F)) * sat;
	float x = c * (1.0F - abs(fmod((h / 60.0F), 2.0F) - 1.0F));
	float m = lum - c / 2.0F;

	if (h >= 0.0F && h <= 60.0F) return		
		XMFLOAT4(255.0F * (c + m), 255.0F * (x + m), 255.0F * (0 + m), 255.0F);

	else if (h >= 60.0F && h <= 120.0F) return		
		XMFLOAT4(255.0F * (x + m), 255.0F * (c + m), 255.0F * (0 + m), 255.0F);

	else if (h >= 120.0F && h <= 180.0F) return		
		XMFLOAT4(255.0F * (0.0F + m), 255.0F * (c + m), 255.0F * (x + m), 255.0F);

	else if (h >= 180.0F && h <= 240.0F) return		
		XMFLOAT4(255.0F * (0.0F + m), 255.0F * (x + m), 255.0F * (c + m), 255.0F);

	else if (h >= 240.0F && h <= 300.0F) return		
		XMFLOAT4(255.0F * (x + m), 255.0F * (0.0F + m), 255.0F * (c + m), 255.0F);

	else if (h >= 300.0F && h <= 360.0F) return		
		XMFLOAT4(255.0F * (c + m), 255.0F * (0.0F + m), 255.0F * (x + m), 255.0F);

	else return		
		XMFLOAT4(0.0F, 0.0F, 0.0F, 0.0F);
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

inline double mainscreen::scale()
{
	if (this->screenDistance < 0.090F) this->screenDistance = 0.090F;
	return (20.0 * this->screenDistance * this->wavelength) / (100.0 * this->slitWidth);
}


void mainscreen::load()
{
	switcher = false;

	slitPosCenter = XMFLOAT2(512.0F, 250.0F);
	lasPosBegin = XMFLOAT2(512.0F, 212.5F);

	slitWidth = 4.5F;
	buffer = 0;
	wavelength = 650.0F;
	screenDistance = 0.2F;

	wave.x = 825.0F;
	wave.y = 250.0F;
	wave.z = wavelength;

	slit.x = 875.0F;
	slit.y = 325.0F;
	slit.z = slitWidth;

	screen.x = 925.0F;
	screen.y = 300.0F;
	screen.z = screenDistance;

	manualHeader = L"Порядок выполнения работы:\n";
	manualContent = L"1. Включить лазер, используя соответствующую кнопку меню;\n";
	manualContent += L"2. Установить значения длины волны и расстояние до экрана;\n";
	manualContent += L"3. Установить такую ширину щели, чтобы ширина полос была удобной для наблюдения;\n";
	manualContent += L"4. Снять измерения и обработать результаты.\n";

	theme = new vector<D2D1_COLOR_F>;
		theme->push_back(core->darkGray);			// Background color
		theme->push_back(core->black);				// Primary (Accent) color
		theme->push_back(core->blue);				// Secondary color
		theme->push_back(core->darkBlue);			// Secondary (Dark) color
		theme->push_back(core->black);				// Laser body color
		theme->push_back(core->white);				// Ruler color
		theme->push_back(core->black);				// Ruler background
		theme->push_back(core->darkSlateBlue);		// Scaler accent color (idle)
		theme->push_back(core->darkRed);			// Scaler accent color (selected)
		theme->push_back(core->black);				// Scaler background (line)
		theme->push_back(core->black);				// Scaler secondary color
		theme->push_back(core->darkGreen);			// Text headers color
		theme->push_back(core->black);				// Text accent color
}

void mainscreen::update(double td, double tt)
{
	//SetCursor(LoadCursor((HINSTANCE)GetWindowLong(core->getHwnd(), GWL_HINSTANCE), IDC_ARROW));
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

	if (
		GetAsyncKeyState(VK_LBUTTON) && 
		mouse.x >= wave.x - 15.0F && mouse.x <= wave.x + 15.0F && 
		mouse.y > wave.y - 10.0F && mouse.y < wave.y + 10.0F
		)
	{
		onWave = true;

		wave.y = mouse.y;
		wave.z = 650.0F - (230.0F / 250.0F) * (wave.y - 250.0F);
		wavelength = wave.z;

		if (mouse.x != wave.x)
		{
			cPos.x = wave.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 250.0F)
		{
			cPos.x = wave.x;
			cPos.y = 250;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500.0F)
		{
			cPos.x = wave.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onWave = false;

	if (
		GetAsyncKeyState(VK_LBUTTON) && 
		mouse.x >= slit.x - 15.0F && mouse.x <= slit.x + 15.0F && 
		mouse.y > slit.y - 10.0F && mouse.y < slit.y + 10.0F
		)
	{
		onSlit = true;

		slit.y = mouse.y;
		slit.z = (15.0F / 250.0F) * (slit.y - 250.0F);
		slitWidth = slit.z;

		if (mouse.x != slit.x)
		{
			cPos.x = slit.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 260.0F)
		{
			cPos.x = slit.x;
			cPos.y = 260;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500.0F)
		{
			cPos.x = slit.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onSlit = false;

	if (
		GetAsyncKeyState(VK_LBUTTON) && 
		mouse.x >= screen.x - 15.0F && mouse.x <= screen.x + 15.0F && 
		mouse.y > screen.y - 10.0F && mouse.y < screen.y + 10.0F
		)
	{
		onScreen = true;

		screen.y = mouse.y;
		screen.z = (1.0F / 250.0F) * (screen.y - 250.0F);
		screenDistance = screen.z;

		if (mouse.x != screen.x)
		{
			cPos.x = screen.x;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y < 280.0F)
		{
			cPos.x = screen.x;
			cPos.y = 280;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
		if (mouse.y > 500.0F)
		{
			cPos.x = screen.x;
			cPos.y = 500;
			ClientToScreen(core->getHwnd(), &cPos);
			SetCursorPos(cPos.x, cPos.y);
		}
	}
	else onScreen = false;

	if (onWave) lenClr = theme->at(scalerAccentActive);
	else lenClr = theme->at(scalerAccent);

	if (onSlit) slitClr = theme->at(scalerAccentActive);
	else slitClr = theme->at(scalerAccent);

	if (onScreen) screenClr = theme->at(scalerAccentActive);
	else screenClr = theme->at(scalerAccent);

	if (switcher) laserEn = core->greenYellow;
	else laserEn = core->red;
}

void mainscreen::render()
{
	// Фоновый цвет
	core->clearScreen(theme->at(background));

	// Отрисовка экрана
	core->drawRectangle
	(
		XMFLOAT4
		(
			0.0F, 0.0F, 
			1024.0F, 150.0F
		), 
		theme->at(rulerBackground), 
		1.0, 
		true
	);

	// Отрисовка размеров
	core->drawLine
	(
		XMFLOAT4
		(
			slitPosCenter.x, slitPosCenter.y, 
			slitPosCenter.x, slitPosCenter.y + 20.0F
		), 
		theme->at(primaryColor),
		1.0
	);

	core->drawLine
	(
		XMFLOAT4
		(
			slitPosCenter.x, slitPosCenter.y, 
			slitPosCenter.x + 100.0F, slitPosCenter.y - 100.0F
		), 
		theme->at(primaryColor),
		1.0
	);

	core->drawLine
	(
		XMFLOAT4
		(
			slitPosCenter.x, slitPosCenter.y, 
			slitPosCenter.x + 200.0F, slitPosCenter.y
		),
		theme->at(primaryColor),
		1.0
	);

	core->printText
	(
		slitWidthStr.c_str(), 
		XMFLOAT2(640.0F, slitPosCenter.y), 
		theme->at(textAccent),
		15.0, 
		L"Consolas"
	);

	core->printText
	(
		screenDistanceStr.c_str(), 
		XMFLOAT2(640.0F, slitPosCenter.y - 20.0F), 
		theme->at(textAccent),
		15.0, 
		L"Consolas"
	);

	core->printText
	(
		wavelenStr.c_str(), 
		XMFLOAT2(640.0F, slitPosCenter.y + 80.0F), 
		theme->at(textAccent),
		15.0, 
		L"Consolas"
	);

	core->printText
	(
		L"Линейка, \u00b5m\n",
		XMFLOAT2(5.0F, 170.0F),
		theme->at(textAccent),
		15.0,
		L"Consolas"
	);

	// Отрисовка шторки с щелью
	auto shutterLeftX = slitPosCenter.x - slitWidth / 8.0 - 50.0;
	auto shutterRightX = slitPosCenter.x + slitWidth / 8.0 + 50.0;

	core->drawRectangle
	(
		XMFLOAT4
		(
			shutterLeftX, slitPosCenter.y, 
			shutterLeftX + 50.0F, slitPosCenter.y - 75.0F
		),
		theme->at(secondaryDarkColor),
		1.0, 
		true
	);
	
	core->drawRectangle
	(
		XMFLOAT4
		(
			shutterRightX, slitPosCenter.y, 
			shutterRightX - 50.0F, slitPosCenter.y - 75.0F
		), 
		theme->at(secondaryDarkColor),
		1.0,
		true
	);
	
	core->drawRectangle
	(
		XMFLOAT4
		(
			shutterLeftX, slitPosCenter.y, 
			shutterRightX, slitPosCenter.y - 75.0F
		), 
		theme->at(secondaryDarkColor),
		1.0
	);

	// Отрисовка лазерного луча и диф картины
	auto prevX = 512.0;

	if (switcher && (int)slitWidth) 
	{ 
		core->drawLine
		(
			XMFLOAT4
			(
				150.0F, 618.0F, 
				lasPosBegin.x, lasPosBegin.y
			), 
			colorlength(wavelength, 0.5F),
			3.5
		);
		for (double i = 0, s = 0; i < 512; i += 1.0 - (1.0 / scale()), s += 0.77)
		{
			auto d = fx(difr(slitWidth, wavelength, s), s);

			if (!i) 
				core->drawLine
				(
					XMFLOAT4
					(
						512.0F, 0.0F, 
						512.0F, 150.0F
					), 
					colorlength(wavelength, 0.85F)
				);
			else
			{
				core->drawLine
				(
					XMFLOAT4
					(
						512.0F - i, 0.0F, 
						512.0F - i, 150.0F
					), 
					colorlength(wavelength, d)
				);

				core->drawLine
				(
					XMFLOAT4
					(
						512.0F + i, 0.0F, 
						512.0F + i, 150.0F
					), 
					colorlength(wavelength, d)
				);
			}
			prevX += i;
		}
	}

	// Отрисовка сетки
	for (short x = 0; x < 512; x += 64)
	{
		core->drawLine
		(
			XMFLOAT4
			(
				512.0F - x, 125.0F, 
				512.0F - x, 150.0F
			), 
			theme->at(rulerColor),
			1.0
		);

		core->drawLine
		(
			XMFLOAT4
			(
				512.0F + x, 125.0F, 
				512.0F + x, 150.0F
			), 
			theme->at(rulerColor),
			1.0
		);

		core->printText
		(
			to_wstring(100 + 100 * (x / 64)).c_str(),
			XMFLOAT2(440.0F - x, 150.0F),
			theme->at(rulerColor),
			15.0,
			L"Consolas"
		);
		
		core->printText
		(
			to_wstring(100 + 100 * (x / 64)).c_str(), 
			XMFLOAT2(568.0F + x, 150.0F),
			theme->at(rulerColor),
			15.0, 
			L"Consolas"
		);
	}

	core->printText
	(
		to_wstring(0).c_str(), 
		XMFLOAT2(508.0F, 150.0F),
		theme->at(rulerColor),
		15.0,
		L"Consolas"
	);

	for (float x = 64.0F/5.0F; x < 512; x += 64.0F/5.0F)
	{
		core->drawLine
		(
			XMFLOAT4
			(
				512.0F - x, 135.0F,
				512.0F - x, 150.0F
			), 
			theme->at(rulerColor),
			1.0
		);

		core->drawLine
		(
			XMFLOAT4
			(
				512.0F + x, 135.0F, 
				512.0F + x, 150.0F
			), 
			theme->at(rulerColor),
			1.0
		);
	}

	// Отрисовка компонентов управления
	core->printText
	(
		L"\u03bb     b     l\n",
		XMFLOAT2(wave.x - 5.0F, 215.0F), 
		theme->at(textAccent),
		15.0, 
		L"Consolas"
	);

	core->printText
	(
		L"Элементы управления\n", 
		XMFLOAT2(wave.x - 30.0F, 195.0F), 
		theme->at(textAccent), 
		15.0, 
		L"Consolas"
	);

	core->drawLine(XMFLOAT4(wave.x, 250.0F, wave.x, 500.0F), theme->at(scalerBackground));
	core->drawLine(XMFLOAT4(slit.x, 250.0F, slit.x, 500.0F), theme->at(scalerBackground));
	core->drawLine(XMFLOAT4(screen.x, 250.0F, screen.x, 500.0F), theme->at(scalerBackground));

	core->drawRectangle
	(
		XMFLOAT4
		(
			wave.x - 15.0F, wave.y - 10.0F, 
			wave.x + 15.0F, wave.y + 10.0F
		),
		lenClr,
		1.0,
		true
	);

	core->drawLine
	(
		XMFLOAT4
		(
			wave.x - 10.0F, wave.y, 
			wave.x + 10.0F, wave.y
		),
		theme->at(scalerBackground)
	);

	core->drawRectangle
	(
		XMFLOAT4
		(
			slit.x - 15.0F, slit.y - 10.0F,
			slit.x + 15.0F, slit.y + 10.0F), 
		slitClr, 
		1.0, 
		true
	);

	core->drawLine
	(
		XMFLOAT4
		(
			slit.x - 10.0F, slit.y, 
			slit.x + 10.0F, slit.y
		),
		theme->at(scalerBackground)
	);

	core->drawRectangle
	(
		XMFLOAT4
		(
			screen.x - 15.0F, screen.y - 10.0F, 
			screen.x + 15.0F, screen.y + 10.0F
		), 
		screenClr, 
		1.0,
		true
	);

	core->drawLine
	(
		XMFLOAT4
		(
			screen.x - 10.0F, screen.y, 
			screen.x + 10.0F, screen.y
		),
		theme->at(scalerBackground)
	);

	// Отрисовка тела лазера
	core->drawCircle
	(
		XMFLOAT2(150.0F, 618.0F), 
		XMFLOAT2(25.0F, 25.0F),
		theme->at(laserBodyColor),
		1.0, 
		true
	);

	for (short i = 0; i < 360; i++)
	{
		auto bx = 150 + 25 * cos(i);
		auto by = 617 + 25 * sin(i);

		core->drawLine(XMFLOAT4(bx, by, bx - 100.0F, by + 100.0F), theme->at(laserBodyColor));
	}

	core->drawCircle
	(
		XMFLOAT2(50.0F, 718.0F), 
		XMFLOAT2(25.0F, 25.0F), 
		theme->at(laserBodyColor),
		1.0, 
		true
	);

	core->drawCircle
	(
		XMFLOAT2(150.0F, 618.0F),
		XMFLOAT2(5.0F, 5.0F),
		laserEn, 
		1.0, 
		true
	);

	// Отрисовка руководства
	core->printText
	(
		manualHeader.c_str(),
		XMFLOAT2(300.0F, 500.0F),
		theme->at(textHeaders),
		20.0,
		L"Consolas"
	);

	core->printText
	(
		manualContent.c_str(),
		XMFLOAT2(300.0F, 550.0F),
		theme->at(textAccent),
		15.0,
		L"Consolas"
	);
}

void mainscreen::unload()
{
	delete[] theme;
}