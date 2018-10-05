#include "MurenaGraphics.h"
#include "MurenaController.h"
#include "MurenaTetranetLevel.h"
#include <sstream>

//--- --- --- --- --- --- --- --- --- --- --- --- ---
//	MurenaTetranetLevel - образцовый уровень MURENA2
//	версии 0.002
//	Использована релятивная система координат
//	Автор: Einhorn32
//--- --- --- --- --- --- --- --- --- --- --- --- ---

void MurenaTetranetLevel::Load() {
	point = 1;
	matrixA[61] = { -50 };
	matrixB[61] = { -50 };
	matrixC[60] = 0; matrixD[60] = 0;
	xCoord = -2;		yCoord = 200;
	xPos = 250;		yPos = 275;
	xAccel = 0;		yAccel = 5.0f;
	CWidth = 50;	CHeight = 20;
	TWidth = 0;		THeight = 0;
	WorkplaceWT = 0;
	WorkplaceHT = 0;
	num = 0; fps = 0;
	type = rand()%7;
	n = 0; m = 15;
	switcher = false;
	mem = 0;
	memp = 0;
}

/// EXTENDED FUNCTIONS LEVEL ::
	void MurenaTetranetLevel::TranslateRect(UINT x, UINT y){
		TWidth = x;
		THeight = y;
	}
	void MurenaTetranetLevel::DrawMatrixFigures() {
		for (int x = 0; x <= 61; x++) {
				gfx->DrawExtended(matrixA[x],matrixB[x],matrixC[x], matrixD[x], 173, 255, 47, 255);
		}
	}
	float MurenaTetranetLevel::TranslateData(float PositionX, float PositionY, float ACCELERATOR) {
		UNREFERENCED_PARAMETER(ACCELERATOR);
		if (PositionY == -1.0f) xCoord *= -1;
		xPos += PositionX * 50.0f;
		yPos += pow(PositionY, 2) * 50.0f;
		return 0;
	}
	bool MurenaTetranetLevel::CheckMatrix(int x, int y) {
		
		return false;
	}
	float MurenaTetranetLevel::Transform90(float CW, float CH) {
		#define W 0
		#define H 1
		#define N 2
		#define M 3
		// Реализация метода инверсии:
			float BUFFER_OF[4] = { 0, 0, 0, 0 };
			BUFFER_OF[W] = CW;
			BUFFER_OF[H] = CH;
			BUFFER_OF[N] = n;
			BUFFER_OF[M] = m;
			CWidth = BUFFER_OF[H];
			CHeight = BUFFER_OF[W];
			n = BUFFER_OF[M];
			m = BUFFER_OF[N];
		// Конец реализации
		#undef W
		#undef H
		#undef N
		#undef M
		return 0;
	}
/// EXTENDED LEVEL END

/// FIGURE DRAWING LEVEL:
	void MurenaTetranetLevel::DrawTestRect(float x, float y) {
		gfx->DrawRectangle(x + n, y + m, CWidth, CHeight, 173, 255, 47, 255);
	}
/// FIGURE DRAWING LEVEL END

void MurenaTetranetLevel::Update(double timeTotal, double timeDelta) {
	// Обязательный к помещению в апдейт блок!
	//->
	PROCESS_MEMORY_COUNTERS memCounter;
	GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(PROCESS_MEMORY_COUNTERS));
	mem = memCounter.WorkingSetSize / 1024 / 1024;
	memp = memCounter.PeakWorkingSetSize / 1024 / 1024;
	fps = 3600 * timeDelta;
	WorkplaceWT = TWidth - 10;
	WorkplaceHT = THeight - 140;
	//<-
	yPos += yAccel * (60 * timeDelta);
	// Пофиксить корявый респаун фигур
	if (yPos >= (115 + (WorkplaceHT / 2)) + yCoord) {
		yPos = (115 + (WorkplaceHT/2)) + yCoord;
		matrixA[point] = xPos;
		matrixB[point] = yPos;
		matrixC[point] = type;
		matrixD[point] = xCoord;
		num++;
		point++;
		type = 1 + rand() % 6;
		yPos = (115 + (WorkplaceHT / 2)) - 250;
	}
	switch (point) {
	case 6:
		yCoord = 150;
		break;
	case 12:
		yCoord = 100;
		break;
	case 18:
		yCoord = 50;
		break;
	case 24:
		yCoord = 0;
		break;
	case 30:
		yCoord = -50;
		break;
	case 36:
		yCoord = -100;
		break;
	case 42:
		yCoord = -150;
		break;
	case 48:
		yCoord = -200;
		break;
	case 54:
		yCoord = -250;
		break;
	case 61:
		point = 1;
		yCoord = 250;
		break;
	default:
		break;
	}
	if (xPos <= (5 + (WorkplaceWT / 2)) - 150) xPos = (5 + (WorkplaceWT / 2)) - 150;
	if (xPos >= (5 + (WorkplaceWT / 2)) + 100) xPos = (5 + (WorkplaceWT / 2)) + 100;
}

void MurenaTetranetLevel::Render() {
	gfx->ClearScreen(30, 30, 30);
	std::wstringstream wss;

	// Обязательный к помещению в рендер блок!
	//->
	/// INFO BLOCK:
		gfx->DrawLine(5, 5, TWidth - 5, 5, 255, 69, 0, 255);
		gfx->DrawLine(5, THeight - 5, TWidth - 5, THeight - 5, 255, 69, 0, 255);
		gfx->DrawLine(5, 95, TWidth - 5, 95, 255, 69, 0, 255);
		gfx->DrawLine(540, 5, 540, 95, 255, 69, 0, 255);
		gfx->DrawLine(540, 25, TWidth - 5, 25, 255, 69, 0, 255);
		//-------//
		gfx->PrintText((LPWSTR)L":: ENGINE TESTING / DEBUG INFORMATION ::", 40, 540 + ((TWidth - 540) / 2 - 125), 8, 173, 255, 47, 255);
		gfx->PrintText((LPWSTR)L"Version:", 8, 545, 26, 173, 255, 47, 255);
		gfx->PrintText((LPWSTR)L"Murena2 Engine pre-alpha | 0.004", 32, 695, 26, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"Date of compilation:", 20, 545, 40, 173, 255, 47, 255);
		gfx->PrintText((LPWSTR)L"14 Jul 2018", 11, 695, 40, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"Graphics driver:", 16, 545, 60, 173, 255, 47, 255);
		gfx->PrintText((LPWSTR)L"DirectX Direct2D in DirectX12 (or older versions)", 49, 695, 60, 138, 43, 226, 255);
		gfx->DrawLine(540, 56, TWidth - 5, 56, 255, 69, 0, 255);
		gfx->DrawLine(950, 25, 950, 56, 255, 69, 0, 255);
		gfx->DrawLine(540, 78, TWidth - 5, 78, 255, 69, 0, 255);
		gfx->DrawLine(1000, 78, 1000, 95, 255, 69, 0, 255);
		gfx->PrintText((LPWSTR)L"Frame rate target:", 18, 845, 80, 173, 255, 47, 255);
		gfx->PrintInt(fps, 1 + (ceil(log10(fps + 1))), 970, 80, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"Used memory (MB):", 17, 545, 80, 173, 255, 47, 255);
		gfx->PrintInt(mem, 1 + (ceil(log10(mem + 1))), 660, 80, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"Peak memory (MB):", 17, 695, 80, 173, 255, 47, 255);
		gfx->PrintInt(memp, 1 + (ceil(log10(memp + 1))), 810, 80, 138, 43, 226, 255);
		//-------//
		gfx->PrintText((LPWSTR)L":: LEVEL WORKSPACE ::", 21, TWidth/2 - 75, 98, 138, 43, 226, 255);
		gfx->PrintInt(WorkplaceWT, 4, 165, 71, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"x", 1, 195, 71, 173, 255, 47, 255);
		gfx->PrintInt(WorkplaceHT, 4, 205, 71, 138, 43, 226, 255);
		gfx->DrawLine(5, 115, TWidth - 5, 115, 255, 69, 0, 255);
		gfx->DrawLine(5, 5, 5, THeight - 5, 255, 69, 0, 255);
		gfx->DrawLine(TWidth - 5, 5, TWidth - 5, THeight - 5, 255, 69, 0, 255);
		gfx->PrintText((LPWSTR)L"Внимание: движок использует релятивную систему координат при рисовании. Картинка только векторно масштабируется. || Есть риск переполнения ОЗУ при долгой работе приложения. Ведётся работа над этой ошибкой.", 205, 10, THeight - 22, 205, 255, 0, 255);
		gfx->DrawLine(5, THeight - 25, TWidth - 5, THeight - 25, 255, 69, 0, 255);
		gfx->PrintText((LPWSTR)L"MURENA2 ENGINE-> Test launch. Version: PA.\nMurenaContoller::CurrentLevel -> Initialized\nTaken resolution info:\n[MAX RAM USAGE: 256MB! IF ENGINE USES MORE THAN 256MB - SHUTDOWN THIS PROCESS!]\nWorkspace resolution:", 212, 15, 15, 173, 255, 47, 255);
		gfx->PrintInt(TWidth, 4, 165, 43, 138, 43, 226, 255);
		gfx->PrintText((LPWSTR)L"x", 1, 195, 43, 173, 255, 47, 255);
		gfx->PrintInt(THeight, 4, 205, 43, 138, 43, 226, 255);
	/// INFO BLOCK END
	//<-
	
	/// GRID FORMING BLOCK:
		/*
		Workplace grid:
		X1 = 5				Y1 = 115
		X2 = TWidth - 5		Y2 = THeight - 25
		WorkplaceWT = TWidth - 10;
		WorkplaceHT = THeight - 140;
		-> X1 = 5
		-> Y1 = 115
		-> X2 = WorkplaceWT + 5
		-> Y2 = WorkplaceHT + 115
		*/
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 100, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) - 100, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 100, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) + 100, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 50, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) - 50, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)), (115 + (WorkplaceHT/2)) - 250, (5 + (WorkplaceWT/2)), (115 + (WorkplaceHT/2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 50, (115 + (WorkplaceHT/2)) - 250, (5 + (WorkplaceWT/2)) + 50, (115 + (WorkplaceHT/2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 250, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 250, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 200, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 200, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 150, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 150, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 100, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 100, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 50, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 50, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) - 0, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) - 0, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 200, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 200, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 150, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 150, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 100, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 100, 173, 255, 47, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 150, (115 + (WorkplaceHT / 2)) + 50, (5 + (WorkplaceWT / 2)) + 150, (115 + (WorkplaceHT / 2)) + 50, 173, 255, 47, 125);
	/// GRID FORMING BLOCK END

	/// GRID INFO BLOCK:
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 350, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) - 350, (115 + (WorkplaceHT / 2)) + 250, 255, 255, 0, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 350, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) - 200, (115 + (WorkplaceHT / 2)) - 250, 255, 255, 0, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) - 350, (115 + (WorkplaceHT / 2)) + 250, (5 + (WorkplaceWT / 2)) - 200, (115 + (WorkplaceHT / 2)) + 250, 255, 255, 0, 125);
		gfx->PrintTextManual((LPWSTR)L"T E T R A N E T", 15, (5 + (WorkplaceWT / 2) - 250), (115 + (WorkplaceHT / 2) - 400), 72, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 173, 255, 47, 255);
		gfx->PrintTextManual((LPWSTR)L"Info:", 5, (5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) - 245), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 173, 255, 47, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) - 205), 1, 2, 138, 43, 226, 255);
		gfx->PrintTextManual((LPWSTR)L"x2 Tube", 7, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) - 195), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 138, 43, 226, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) - 135), 2, 2, 138, 43, 226, 255);
		gfx->PrintTextManual((LPWSTR)L"x3 Tube", 7, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) - 125), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 138, 43, 226, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) - 65), 3, -2, 138, 43, 226, 255);
		gfx->PrintTextManual((LPWSTR)L"x4 Tube", 7, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) - 55), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 138, 43, 226, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) + 5), 4, -2, 138, 43, 226, 255);
		gfx->PrintTextManual((LPWSTR)L"Corner", 6, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) + 15), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 138, 43, 226, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) + 75), 5, -2, 255, 0, 255, 255);
		gfx->PrintTextManual((LPWSTR)L"Server", 6, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) + 85), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 255, 0, 255, 255);

		gfx->DrawExtended((5 + (WorkplaceWT / 2) - 345), (115 + (WorkplaceHT / 2) + 145), 6, -2, 255, 255, 0, 255);
		gfx->PrintTextManual((LPWSTR)L"PC", 2, (5 + (WorkplaceWT / 2) - 285), (115 + (WorkplaceHT / 2) + 155), 25, (LPWSTR)L"Alien Encounters(RUS BY LYAJKA)", 255, 255, 0, 255);

		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 350, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) + 350, (115 + (WorkplaceHT / 2)) + 250, 255, 255, 0, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 350, (115 + (WorkplaceHT / 2)) - 250, (5 + (WorkplaceWT / 2)) + 200, (115 + (WorkplaceHT / 2)) - 250, 255, 255, 0, 125);
		gfx->DrawLine((5 + (WorkplaceWT / 2)) + 350, (115 + (WorkplaceHT / 2)) + 250, (5 + (WorkplaceWT / 2)) + 200, (115 + (WorkplaceHT / 2)) + 250, 255, 255, 0, 125);
	/// GRID INFO END

	/// OTHER GRAPHICS BLOCK:
		gfx->PrintTextManual((LPWSTR)L"Score:", 6, (5 + (WorkplaceWT / 2) + 175), (115 + (WorkplaceHT / 2) - 225), 25, (LPWSTR)L"Larabiefont Free", 173, 255, 47, 255);
		wss << num;
		gfx->PrintTextManual((LPWSTR)wss.str().c_str(), 1 + (ceil(log10(num + 1))), (5 + (WorkplaceWT / 2) + 275), (115 + (WorkplaceHT / 2) - 225), 25, (LPWSTR)L"Larabiefont Free", 173, 255, 47, 255);
	/// OTHER GRAPHICS BLOCK END

	/// FIGURE DRAWING BLOCK:
		gfx->DrawExtended(xPos, yPos, type, xCoord, 173, 255, 47, 255);
		DrawMatrixFigures();
	/// FIGURE DRAWING BLOCK END
}

void MurenaTetranetLevel::Unload() {
	delete sprite;
}