#pragma once
#include <Windows.h>
#include <mmsystem.h>

#define Cascade CreateLCDCascade
#define ShowDebugInfo ShowData
#define Note DrawNote
#define ProgressBar CreateProgressBar
#define IsCollide IsCollidingWithDimension

void MurenaMenuLevel::SetBPM(int bpms) {
	bpm = bpms;
}

// Инфоблок, который наверное стоит вынести в Graphics.cpp
void MurenaMenuLevel::ShowData(float fpsVar, BOOL memUsedVar, BOOL memPeakVar) {

	// Обязательный к помещению в апдейт блок!
	//->
	MEMORYSTATUSEX msex;
	msex.dwLength = sizeof(msex);
	GlobalMemoryStatusEx(&msex);
	memoryAll = msex.ullAvailPhys / 1024 / 1024;
	PROCESS_MEMORY_COUNTERS memCounter;
	GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(PROCESS_MEMORY_COUNTERS));
	mem = memCounter.WorkingSetSize / 1024 / 1024;
	memp = memCounter.PeakWorkingSetSize / 1024 / 1024;
	fps = 60 / timeDelta1;
	if (console == true) {
		///
	}
	else {
		ConsoleInput = L"MURENA2 Developer console: >> Ввод знаков в терминал вызывает критическую ошибку и вылет";
	}
	hr = min / 60;
	min = sec / 60;
	sec = timeTotal1; // считает секунды
	mcsec = timeDelta1 * 10000000;
	mcsec2 = timeDelta1;
	//<-

	IDXGIFactory1* pFactory;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
	IDXGIAdapter1* Adapter;
	pFactory->EnumAdapters1(0, &Adapter);
	DXGI_ADAPTER_DESC1 Desc;
	Adapter->GetDesc1(&Desc);
	std::wstringstream wss;
	wss << Desc.Description;
	AdapterName = wss.str().c_str();
	wss.str(L"");
	Adapter->Release();
	pFactory->Release();
	wstring str = L"MURENA2 0.01 build ";
	str += buildnum;
	str += L". Режим показа информации\n";
	str += L"Используйте ~ для вызова консоли или ESC для выхода из MURENA2\n";
	str += L"Текущий уровень: ";
	str += CurrentLevelName;
	str += L" | Видеоадаптер: "; str += AdapterName;
	str += L" (Текущее разрешение экрана: ";
	wss << ScreenWidth;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" х ";
	wss << ScreenHeight;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" px)\n";
	str += L"Время работы приложения: ";
	wss << hr;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" hr(s):";
	wss << min;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" min(s) | ";
	wss << sec;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" sec(s) | Время отклика процессора: ";
	wss << mcsec;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" µsec, или ";
	wss << mcsec2;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" sec\n";
	str += L"Объём свободной оперативной памяти: ";
	wss << memoryAll;
	wstring memAvail = wss.str().c_str();
	str += memAvail;
	wss.str(L""); // Очистка вывода строки
	wss << memUsedVar;
	str += L" Mb; Количество используемой памяти: ";
	str += wss.str().c_str();
	wss.str(L"");
	wss << memPeakVar;
	str += L" Mb, количество пиковой памяти: ";
	str += wss.str().c_str();
	wss.str(L"");
	str += L" Mb\n";
	wss << fpsVar;
	str += L"Частота обновления кадров (FPS): ";
	str += wss.str().c_str();
	str += L" кадров в секунду\n";
	wss.str(L"");
	gfx->PrintTextManual(str.c_str(), XMFLOAT2(5, 5), 12, L"Consolas", gfx->White);
	wss.str(L"");

}
void MurenaMenuLevel::LCD(XMFLOAT2 coord, float size, int input, D2D1_COLOR_F color) {
	gfx->PrintTextManual(L"8", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintTextManual(L"X", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintNum(input, XMFLOAT2(coord.x, coord.y), 0, L"Digital-7 Mono", size, color);
}
void MurenaMenuLevel::CreateLCDCascade(XMFLOAT2 coord, float size, const wchar_t* input = L"ERROR", D2D1_COLOR_F color) {
	gfx->PrintTextManual(L"88888", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintTextManual(L"XXXXX", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintTextManual(input, 5, XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", color);
}
void MurenaMenuLevel::CreateLCDCascade(XMFLOAT2 coord, float size, float input, D2D1_COLOR_F color) {
	gfx->PrintTextManual(L"88888", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintTextManual(L"XXXXX", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintNum(input, XMFLOAT2(coord.x, coord.y), 0, L"Digital-7 Mono", size, color);
}
void MurenaMenuLevel::CreateLCDCascade(XMFLOAT2 coord, float size, int input, D2D1_COLOR_F color) {
	gfx->PrintTextManual(L"88888", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintTextManual(L"XXXXX", XMFLOAT2(coord.x, coord.y), size, L"Digital-7 Mono", gfx->DimGray);
	gfx->PrintNum(input, XMFLOAT2(coord.x, coord.y), 0, L"Digital-7 Mono", size, color);
}
void MurenaMenuLevel::DrawNote(int finger, int string, int fret, double pos, int currentnum) {
	currentBuffer[currentnum - 1] = pos;
	std::wstringstream wss;
	wss << fret;
	LPCWSTR inputbuffer = wss.str().c_str();
	D2D1_COLOR_F padcolor = gfx->Gray;
	switch (finger) {
	case 1:
		padcolor = gfx->Red;
		break;
	case 2:
		padcolor = gfx->LimeGreen;
		break;
	case 3:
		padcolor = gfx->DarkOrange;
		break;
	case 4:
		padcolor = gfx->DarkCyan;
		break;
	default:
		padcolor = gfx->Silver;
		break;
	}
	switch (string) {
	case 1:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 1.5 - (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)) / 2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case 2:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.2 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.2 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.2 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)) / 2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case 3:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.4 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.4 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 1.5 - ScreenWidth / 3 * 0.4 - (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)) / 2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case 4:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.4 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.4 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.4 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.4) / (ScreenHeight)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)) / 2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case 5:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.2 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.2 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 3 + ScreenWidth / 3 * 0.2 + (ScreenHeight - pos) * ((ScreenWidth / 2 - ScreenWidth / 3 - ScreenWidth / 3 * 0.2) / (ScreenHeight)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)) / 2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	case 6:
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), gfx->Black, 1.0f, true);
		gfx->DrawCircle(XMFLOAT2(ScreenWidth / 3 + (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), XMFLOAT2(NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8)), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))), padcolor, 2.5f);
		gfx->PrintNum(fret, XMFLOAT2(ScreenWidth / 3 + (ScreenHeight*0.95 - pos) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), pos), NotBiggerThan(20, pos * (20 / ScreenHeight * 0.8))/2, L"Larabiefont Free", (abs(pos) * (40 / ScreenHeight * 0.8)), padcolor, DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	}
	wss.str(L"");
}

enum Songs {
	Demo_PreRelease_Song_Easy = -16384,
	Demo_PreRelease_Song_Medium = -16383,
	Demo_PreRelease_Song_Hard = -16382,
	Demo_PreRelease_Song_Expert = -16381,
	Demo_PreRelease_Song_Insane = - 16380
};

void MurenaMenuLevel::DrawPattern(UINT pattern) {
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	switch (pattern) {
	case Demo_PreRelease_Song_Easy:
		SetBPM(90);
		patternTrigger = true;
		patternsoundname = "resources/audio/pattern0.wav";

		/// SONG INFO -->
		author = L"Vladimir Shainskij (words by Nikolay Nosov)";
		songname = L"Grasshopper";
		difficulty = L"Very easy";
		/// <--

		/// PATTERN DRAWING -->
		Note(3, 3, 2, song - NOTE_QUART_DOT, 1);
		Note(2, 4, 2, song - NOTE_QUART_DOT - NOTE_EIGHT, 2);
		Note(3, 3, 2, song - NOTE_QUART_DOT - NOTE_QUART, 3);
		Note(2, 4, 2, song - NOTE_QUART_DOT - NOTE_QUART_DOT, 4);
		Note(3, 3, 2, song - NOTE_QUART_DOT - NOTE_HALF, 5);

		Note(1, 3, 1, song - TACT - NOTE_EIGHT, 6);
		Note(1, 3, 1, song - TACT - NOTE_QUART, 7);
		Note(1, 3, 1, song - TACT - NOTE_HALF, 8);

		Note(1, 4, 2, song - TACT - NOTE_HALF - NOTE_EIGHT, 9);
		Note(2, 3, 1, song - TACT - NOTE_HALF - NOTE_QUART, 10);
		Note(1, 4, 2, song - TACT - NOTE_HALF - NOTE_QUART_DOT, 11);
		Note(2, 3, 1, song - TACT - TACT, 12);

		Note(3, 3, 2, song - 2 * TACT - NOTE_EIGHT, 13);
		Note(3, 3, 2, song - 2 * TACT - NOTE_QUART, 14);
		Note(3, 3, 2, song - 2 * TACT - NOTE_HALF, 15);

		Note(3, 4, 2, song - 2 * TACT - NOTE_HALF - NOTE_EIGHT, 16);
		Note(2, 3, 1, song - 2 * TACT - NOTE_HALF - NOTE_QUART, 17);
		Note(3, 4, 2, song - 2 * TACT - NOTE_HALF - NOTE_QUART_DOT, 18);
		Note(2, 3, 1, song - 2 * TACT - TACT, 19);

		Note(1, 3, 2, song - 3 * TACT - NOTE_EIGHT, 20);
		Note(1, 3, 2, song - 3 * TACT - NOTE_QUART, 21);
		Note(1, 3, 2, song - 3 * TACT - NOTE_HALF, 22);

		Note(1, 4, 2, song - 3 * TACT - NOTE_HALF - NOTE_EIGHT, 23);
		Note(2, 3, 1, song - 3 * TACT - NOTE_HALF - NOTE_QUART, 24);
		Note(1, 4, 2, song - 3 * TACT - NOTE_HALF - NOTE_QUART_DOT, 25);
		Note(2, 3, 1, song - 3 * TACT - TACT, 26);

		Note(3, 3, 2, song - 4 * TACT - NOTE_QUART, 27);
		Note(3, 3, 2, song - 4 * TACT - NOTE_HALF, 28);

		Note(0, 2, 0, song - 4 * TACT - NOTE_HALF - NOTE_EIGHT, 29);
		Note(0, 2, 0, song - 4 * TACT - NOTE_HALF - NOTE_EIGHT - NOTE_16, 30);
		Note(0, 2, 0, song - 4 * TACT - NOTE_HALF - NOTE_QUART, 31);
		Note(0, 2, 0, song - 4 * TACT - NOTE_HALF - NOTE_QUART - NOTE_EIGHT, 32);
		Note(0, 2, 0, song - 5 * TACT, 33);

		Note(1, 2, 1, song - 5 * TACT - NOTE_EIGHT, 34);
		Note(1, 2, 1, song - 5 * TACT - NOTE_EIGHT - NOTE_16, 35);
		Note(1, 2, 1, song - 5 * TACT - NOTE_QUART, 36);
		Note(1, 2, 1, song - 5 * TACT - NOTE_QUART - NOTE_EIGHT, 37);
		Note(1, 2, 1, song - 5 * TACT - NOTE_HALF, 38);

		Note(1, 2, 1, song - 5 * TACT - NOTE_HALF - NOTE_EIGHT, 39);
		Note(0, 2, 0, song - 5 * TACT - NOTE_HALF - NOTE_QUART, 40);
		Note(2, 3, 2, song - 5 * TACT - NOTE_HALF - NOTE_QUART_DOT, 41);
		Note(1, 3, 1, song - 6 * TACT, 42);

		Note(2, 3, 2, song - 6 * TACT - NOTE_EIGHT, 43);
		Note(2, 3, 2, song - 6 * TACT - NOTE_QUART, 44);
		Note(2, 3, 2, song - 6 * TACT - NOTE_HALF, 45);

		Note(0, 2, 0, song - 6 * TACT - NOTE_HALF - NOTE_EIGHT, 46);
		Note(0, 2, 0, song - 6 * TACT - NOTE_HALF - NOTE_EIGHT - NOTE_16, 47);
		Note(0, 2, 0, song - 6 * TACT - NOTE_HALF - NOTE_QUART, 48);
		Note(0, 2, 0, song - 6 * TACT - NOTE_HALF - NOTE_QUART - NOTE_EIGHT, 49);
		Note(0, 2, 0, song - 7 * TACT, 50);

		Note(1, 2, 1, song - 7 * TACT - NOTE_EIGHT, 51);
		Note(1, 2, 1, song - 7 * TACT - NOTE_EIGHT - NOTE_16, 52);
		Note(1, 2, 1, song - 7 * TACT - NOTE_QUART, 53);
		Note(1, 2, 1, song - 7 * TACT - NOTE_QUART - NOTE_EIGHT, 54);
		Note(1, 2, 1, song - 7 * TACT - NOTE_HALF, 55);

		Note(1, 2, 1, song - 7 * TACT - NOTE_HALF - NOTE_EIGHT, 56);
		Note(0, 2, 0, song - 7 * TACT - NOTE_HALF - NOTE_QUART, 57);
		Note(2, 3, 2, song - 7 * TACT - NOTE_HALF - NOTE_QUART_DOT, 58);
		Note(1, 3, 1, song - 8 * TACT, 59);
		Note(1, 3, 2, song - 8 * TACT - NOTE_EIGHT, 60);
		/// <--

		break;
	case Demo_PreRelease_Song_Medium:
		break;
	case Demo_PreRelease_Song_Hard:
		SetBPM(140);
		patternsoundname = "resources/audio/demo_hard_symphonyx_fallen.wav";

		/// SONG INFO -->
		author = L"Symphony X";
		songname = L"Fallen";
		difficulty = L"Hard";
		/// <--

		Note(2, 5, 4, song - 15 * TACT - NOTE_2_DOT - NOTE_8, 1);
		Note(1, 6, 2, song - 15 * TACT - NOTE_2_DOT - NOTE_8, 2);

		Note(2, 5, 4, song - 16 * TACT, 3);
		Note(1, 6, 2, song - 16 * TACT, 4);

		Note(2, 5, 4, song - 16 * TACT - NOTE_4, 5);
		Note(1, 6, 2, song - 16 * TACT - NOTE_4, 6);

		Note(2, 5, 4, song - 16 * TACT - NOTE_4 - NOTE_8, 7);
		Note(1, 6, 2, song - 16 * TACT - NOTE_4 - NOTE_8, 8);

		Note(2, 5, 4, song - 16 * TACT - 2 * NOTE_4, 9);
		Note(1, 6, 2, song - 16 * TACT - 2 * NOTE_4, 10);

		Note(2, 5, 4, song - 16 * TACT - 2 * NOTE_4 - NOTE_8, 11);
		Note(1, 6, 2, song - 16 * TACT - 2 * NOTE_4 - NOTE_8, 12);

		Note(2, 5, 4, song - 17 * TACT, 13);
		Note(1, 6, 2, song - 17 * TACT, 14);

		break;
	}
	/// MAKING AN INFO STRING -->
	info_string = L"";
	info_string += songname;
	info_string += L"\n[Song by ";
	info_string += author;
	info_string += L"]\nDifficulty: ";
	info_string += difficulty;
	info_string += L"\nScore:";
	/// <--

	currentPoint = currentBuffer[last + 1];
}
double MurenaMenuLevel::NotBiggerThan(double size, double number) {
	if (number > size) {
		number = size;
	}
	return number;
}
bool MurenaMenuLevel::IsCollidingWithDimension(XMFLOAT2 diapason, double enter, bool key) {
	if ((enter >= diapason.x) && (enter <= diapason.y)) {
		key = true;
		return true;
	}
	else key = false;
	return false;
}
void MurenaMenuLevel::CreateProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double in, D2D1_COLOR_F color) {
	double progress = size.x / 100 * in;
	gfx->DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + size.x, coord.y + size.y), gfx->DimGray, 1.0f, true);
	gfx->DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + NotBiggerThan(size.x, progress), coord.y + size.y), color, 1.0f, true);
}
void MurenaMenuLevel::CreateProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double in, XMFLOAT4 color) {
	double progress = size.x / 100 * in;
	gfx->DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + size.x, coord.y + size.y), gfx->DimGray, 1.0f, true);
	gfx->DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + NotBiggerThan(size.x, progress), coord.y + size.y), color, 1.0f, true);
}

#define _CRT_SECURE_NO_WARNINGS
struct WAVHEADER
{
	char    sigRIFF[4];     // должно быть равно "RIFF"
	DWORD   sizeRIFFch;     // размер чанка RIFF
	char    sigWAVE[4];     // должно быть равно "WAVE"
	char    sigFMT[4];      // должно быть равно "fmt "
	DWORD   sizeFMTch;      // размер чанка FMT
	WORD    wFormatTag;     // категория формата, для PCM = 1
	WORD    wChannels;      // кол-во каналов: 1-моно 2-стерео
	DWORD   dwSamplesPerSec;// кол-во сэмплов в сек.
	DWORD   dwAvgBytesPerSec;// среднее число байт в сек
	WORD    wBlockAlign;    // выравнивание данных в дата-чанке
	WORD    wBitPerSample;  // бит в сэмпле
	char    sigDATA[4];     // должно быть равно "data"
	DWORD   sizeDATAch;     // размер data-чанка
};
void MurenaMenuLevel::Beep(DWORD dwFrequency, DWORD dwMseconds) {
	// частота дискретизации = 44100 Гц
	// кол-во бит на сэмпл = 8
	// если требуемая частота > 44100 или равна нулю, то выходим
	if (!dwFrequency || dwFrequency > 44100)
		return;

	// длина дорожки в байтах
	DWORD numSamples = 44100 / dwFrequency;

	// выделяем память под дорожку
	DWORD size = sizeof(WAVHEADER) + numSamples;
	void *buff = new char[size];

	// заполняем WAV-header
	WAVHEADER *head = (WAVHEADER*)buff;
	strcpy_s(head->sigRIFF, "RIFF");
	strcpy_s(head->sigWAVE, "WAVE");
	head->sizeRIFFch = size - 8;
	strcpy_s(head->sigFMT, "fmt ");
	head->sizeFMTch = 16;
	head->wFormatTag = 1;
	head->wChannels = 1; // моно
	head->dwSamplesPerSec = 44100;
	head->dwAvgBytesPerSec = 44100;
	head->wBlockAlign = 1;
	head->wBitPerSample = 8;
	strcpy_s(head->sigDATA, "data");
	head->sizeDATAch = size;

	// заполняем дорожку периодом синуса
	BYTE *samples = (BYTE*)(head + 1);
	for (DWORD i = 0; i < numSamples; i++)
		samples[i] = BYTE(255 * sin(6.28*double(i) / double(size)));

	// проигрываем звук
	PlaySound((const char*)buff, 0, SND_ASYNC | SND_LOOP | SND_MEMORY);

	// ждём заданное количество миллисекунд
	Sleep(dwMseconds);

	// останавливаем звук
	PlaySound(0, 0, SND_ASYNC);
}