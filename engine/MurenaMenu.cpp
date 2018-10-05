#include "MurenaGraphics.h"
#include "MurenaController.h"
#include "MurenaMenu.h"
#include "mmath.h"
#include <iostream>
#include <string>
#include <fstream>

void MurenaMenu::Load() {
	
}

void MurenaMenu::Update(double timeTotal, double timeDelta) {
	fps = timeDelta * 3600;
}

void MurenaMenu::Render() {
	gfx->ClearScreen(gfx->Black);
	ShowData(fps, mem, memp);
}

void MurenaMenu::Unload() {

}

float MurenaMenu::TranslateData(float PositionX, float PositionY, float add) {
	consoleSwitcher *= add;
	if (consoleSwitcher < 0) console = true;
	else console = false;
	return 0;
}
void MurenaMenu::TranslateRect(UINT w, UINT h) {
	ScreenWidth = w;
	ScreenHeight = h;
}
void MurenaMenu::GetConsoleInput(LPCWSTR input) {
	ConsoleInput += input;
}
void MurenaMenu::ShowData(float fpsVar, BOOL memUsedVar, BOOL memPeakVar) {

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
	std::wstring str = L"MURENA2 0.01 build ";
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
	std::wstring memAvail = wss.str().c_str();
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