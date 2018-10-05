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

	// ������������ � ��������� � ������ ����!
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
		ConsoleInput = L"MURENA2 Developer console: >> ���� ������ � �������� �������� ����������� ������ � �����";
	}
	hr = min / 60;
	min = sec / 60;
	sec = timeTotal1; // ������� �������
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
	str += L". ����� ������ ����������\n";
	str += L"����������� ~ ��� ������ ������� ��� ESC ��� ������ �� MURENA2\n";
	str += L"������� �������: ";
	str += CurrentLevelName;
	str += L" | ������������: "; str += AdapterName;
	str += L" (������� ���������� ������: ";
	wss << ScreenWidth;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" � ";
	wss << ScreenHeight;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" px)\n";
	str += L"����� ������ ����������: ";
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
	str += L" sec(s) | ����� ������� ����������: ";
	wss << mcsec;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" �sec, ��� ";
	wss << mcsec2;
	str += wss.str().c_str();
	wss.str(L"");
	str += L" sec\n";
	str += L"����� ��������� ����������� ������: ";
	wss << memoryAll;
	std::wstring memAvail = wss.str().c_str();
	str += memAvail;
	wss.str(L""); // ������� ������ ������
	wss << memUsedVar;
	str += L" Mb; ���������� ������������ ������: ";
	str += wss.str().c_str();
	wss.str(L"");
	wss << memPeakVar;
	str += L" Mb, ���������� ������� ������: ";
	str += wss.str().c_str();
	wss.str(L"");
	str += L" Mb\n";
	wss << fpsVar;
	str += L"������� ���������� ������ (FPS): ";
	str += wss.str().c_str();
	str += L" ������ � �������\n";
	wss.str(L"");
	gfx->PrintTextManual(str.c_str(), XMFLOAT2(5, 5), 12, L"Consolas", gfx->White);
	wss.str(L"");
}