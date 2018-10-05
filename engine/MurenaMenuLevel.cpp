#include "MurenaGraphics.h"
#include "MurenaController.h"
#include "MurenaMenuLevel.h"
#include <DXGI.h>
#include <iomanip>
#include <iostream>

// [GUITAR STORM PATTERN DRAWING SYSTEM] NOTES DEFINITIONS -->

///////////////////////////////////////////////////////////////
//		There is several same NOTE_ flags:
//	NOTE_FULL == NOTE_1 | NOTE_FULL_DOT == NOTE_1_DOT
//	NOTE_HALF == NOTE_2 | NOTE_HALF_DOT == NOTE_2_DOT
//	NOTE_QUART == NOTE_4 | NOTE_QUART_DOT == NOTE_4_DOT
//	NOTE_EIGHT == NOTE_8
//		It will be deprecated coming soon cause we should to
//	rewrite pattern 0 if we don't want to use that old flags now
///////////////////////////////////////////////////////////////

#define NOTE_64					7.8125
#define NOTE_64_DOT				11.71875
#define NOTE_64_2DOT			13.671875
#define NOTE_32					15.625
#define NOTE_32_DOT				23.4375
#define NOTE_32_2DOT			27,34375
#define NOTE_16					31.25
#define NOTE_16_DOT				46.875
#define NOTE_16_2DOT			54.6875
#define NOTE_EIGHT				62.5
#define NOTE_8					62.5
#define NOTE_8_DOT				93.75
#define NOTE_8_2DOT				109.375
#define NOTE_QUART				125
#define NOTE_4					125
#define NOTE_QUART_DOT			187.5
#define NOTE_4_DOT				187.5
#define NOTE_4_2DOT				218.75
#define NOTE_HALF				250
#define NOTE_2					250
#define NOTE_HALF_DOT			375
#define NOTE_2_DOT				375
#define NOTE_2_2DOT				437.5
#define NOTE_FULL				500
#define NOTE_1					500
#define NOTE_FULL_DOT			750
#define NOTE_1_DOT				750
#define NOTE_1_2DOT				875
#define TACT					500
// <--

using namespace std;
wstringstream wss;
#include "MurenaMenuLevel_UnoverridedFunctions.h"

//--------------------------------------------------
//	Исходник:		MurenaMenuLevel.h
//	Автор модуля:	Einhorn32
//					2018, Einhorn32(c)
//--------------------------------------------------
void MurenaMenuLevel::Load() {
	//sprite = new MurenaSpriteSheet((LPCWSTR)L"resources/img/<name>.png", gfx, <height>, <width>);

	//////////////////////////////////////////////////////
	//		This is initialization of default debug
	//	variables. It's no need to change anything there
	//////////////////////////////////////////////////////
	CurrentLevelName = L"Guitar Storm";	buildnum = L"1";
	vmemavail = 0; vmemtotal = 0; fps = 0;
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	memoryAll = 0; sec = 0;
	AdapterName = L"Adapter name undefined or system cannot get it";
	ConsoleInput = L"MURENA2 Developer console: >> Ввод знаков в терминал вызывает критическую ошибку и вылет";
	consoleSwitcher = 1;	console = false;

	//////////////////////////////////////////////////////
	//		Guitar Storm game variable initialization
	//	Please conside that some variables equals a divide
	//	from any another variables. Avoid a dividing by
	//	zero in <Update> function
	//////////////////////////////////////////////////////
	bpm = 1;	tcDistance = 0;		dSpeed = 1;		size = 0;
	score = 0;
	tact1 = 0;							// Starting point in a tact loop: 1
	tact2 = -500;						// Starting point in a tact loop: 2
	tact3 = -1000;						// Starting point in a tact loop: 3
	tact4 = -1500;						// Starting point in a tact loop: 4
	tact5 = -2000;						// Starting point in a tact loop: 5
	song = 0;						// Starting point of a song
	multiplier = L"x1";		mul = 1;
	currentPoint = -1000; last = -1;	// GAME LOGIC ELEMENT: Contains an Y-axis coordinate of current <Note>
										// mul: multiplier of score; last: marker of a last <Note> currentPoint
	patternsoundname = "null";			// GAME LOGIC ELEMENT: Contains a PATH to .wav-soundfile of current <Pattern>
	patternTrigger = true;
}

void MurenaMenuLevel::Unload() {
	/*delete sprite;
	delete sst;*/
}

float MurenaMenuLevel::TranslateData(float PositionX, float PositionY, float add) {
	consoleSwitcher *= add;
	if (consoleSwitcher < 0) console = true;
	else console = false;
	return 0;
}
void MurenaMenuLevel::TranslateRect(UINT w, UINT h) {
	ScreenWidth = w;
	ScreenHeight = h;
}
void MurenaMenuLevel::GetConsoleInput(LPCWSTR input) {
	ConsoleInput += input;
}

void MurenaMenuLevel::Update(double timeTotal, double timeDelta) {
	timeDelta1 = timeDelta;
	timeTotal1 = timeTotal;

	tcDistance = 4 * (240 / bpm);
	dSpeed = (500 / (ScreenHeight * 0.8 * timeDelta) / tcDistance);
	song += dSpeed;
	tact1 += dSpeed;
	tact2 += dSpeed;
	tact3 += dSpeed;
	tact4 += dSpeed;
	tact5 += dSpeed; 

	size += timeDelta;
		
	if (tact1 >= ScreenHeight * 0.9) tact1 = tact5 - 500;
	if (tact2 >= ScreenHeight * 0.9) tact2 = tact1 - 500;
	if (tact3 >= ScreenHeight * 0.9) tact3 = tact2 - 500;
	if (tact4 >= ScreenHeight * 0.9) tact4 = tact3 - 500;
	if (tact5 >= ScreenHeight * 0.9) tact5 = tact4 - 500;

	if (score == 10) mul = 2;
	if (score == 30) mul = 3;
	if (score == 60) mul = 4;
		switch (mul) {
		case 1:
			multiplier = L"x1";
			break;
		case 2:
			multiplier = L"x2";
			break;
		case 3:
			multiplier = L"x3";
			break;
		case 4:
			multiplier = L"x4";
			break;
		}
}

void MurenaMenuLevel::Render() {
	gfx->ClearScreen(gfx->Black);

	// STRINGS AND FRETS -->
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3, ScreenHeight * 0.95, ScreenWidth / 2, 0), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3 + ScreenWidth / 3 * 0.2, ScreenHeight, ScreenWidth / 2, 0), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3 + ScreenWidth / 3 * 0.4, ScreenHeight, ScreenWidth / 2, 0), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3 + ScreenWidth / 3 * 0.6, ScreenHeight, ScreenWidth / 2, 0), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3 + ScreenWidth / 3 * 0.8, ScreenHeight, ScreenWidth / 2, 0), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(2 * ScreenWidth / 3, ScreenHeight * 0.95, ScreenWidth / 2, 0), gfx->Ivory);

	gfx->DrawLine(XMFLOAT4(ScreenWidth / 1.5 - (ScreenHeight*0.95 - tact1) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact1, ScreenWidth / 3 + (ScreenHeight*0.95 - tact1) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact1), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 1.5 - (ScreenHeight*0.95 - tact2) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact2, ScreenWidth / 3 + (ScreenHeight*0.95 - tact2) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact2), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 1.5 - (ScreenHeight*0.95 - tact3) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact3, ScreenWidth / 3 + (ScreenHeight*0.95 - tact3) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact3), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 1.5 - (ScreenHeight*0.95 - tact4) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact4, ScreenWidth / 3 + (ScreenHeight*0.95 - tact4) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact4), gfx->Ivory);
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 1.5 - (ScreenHeight*0.95 - tact5) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact5, ScreenWidth / 3 + (ScreenHeight*0.95 - tact5) * ((ScreenWidth / 2 - ScreenWidth / 3) / (ScreenHeight*0.95)), tact5), gfx->Ivory);
	// <--

	// PATTERN DRAWING BLOCK -->
	DrawPattern(Demo_PreRelease_Song_Hard);
	if (patternTrigger == true) {
		PlaySound(patternsoundname, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		patternTrigger = false;
	}
	// <--

	// COMMON GAME INTERFACE -->
	gfx->DrawLine(XMFLOAT4(ScreenWidth / 3, ScreenHeight - ScreenHeight * 0.2, ScreenWidth / 1.5, ScreenHeight - ScreenHeight * 0.2), gfx->GreenYellow);
	gfx->DrawRectangle(XMFLOAT4(ScreenWidth / 3, ScreenHeight - ScreenHeight * 0.1, ScreenWidth / 1.5, ScreenHeight), gfx->Black, 1.0f, true);
	gfx->DrawRectangle(XMFLOAT4(ScreenWidth / 3, 0, ScreenWidth / 1.5, ScreenHeight*0.1), gfx->Black, 1.0f, true);

	gfx->PrintTextManual(info_string.c_str(), XMFLOAT2(ScreenWidth / 1.5, ScreenHeight*0.5 - ScreenHeight * 0.2), 25, L"Larabiefont Free", gfx->Ivory);

	if (score == 0) {
		Cascade(XMFLOAT2(ScreenWidth / 1.5, ScreenHeight*0.5 - ScreenHeight * 0.05), ScreenHeight * 0.1, L"-----", gfx->Gold);
	}
	else {
		Cascade(XMFLOAT2(ScreenWidth / 1.5, ScreenHeight*0.5 - ScreenHeight * 0.05), ScreenHeight * 0.1, score, gfx->Gold);
	}
	Cascade(XMFLOAT2(ScreenWidth / 1.5 + ScreenHeight*0.25, ScreenHeight*0.5 - ScreenHeight * 0.05), ScreenHeight * 0.1, multiplier.c_str(), gfx->GreenYellow);
	ProgressBar(XMFLOAT2(ScreenWidth / 1.5, ScreenHeight*0.5 + ScreenHeight * 0.05), XMFLOAT2(ScreenWidth / 4, 5), score/1.8, gfx->GreenYellow);

	lineTrigger = IsCollide(XMFLOAT2(ScreenHeight*0.8 - 20, ScreenHeight*0.8 + 20), currentPoint, verColTrigger);
	if (lineTrigger == true) {
		score += 1 * mul;
		last++;
	}
	gfx->PrintNum(size, XMFLOAT2(500, 500), 0, L"Consolas", 34, gfx->Yellow);
	// <--

	// ENGINE DEBUG INSTRUMENTS -->
	ShowDebugInfo(fps, mem, memp);
	if (console == true) {
		gfx->CreateConsole(ConsoleInput);
	}
	// <--
}