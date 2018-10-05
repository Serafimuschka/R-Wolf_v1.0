#pragma once
#include "MurenaGraphics.h"
#include <sstream>
#include <string>
#include <Psapi.h>
#define SSTOpen SST_OpenChannelMono
#define SSTClose SST_CloseChannelMono
#define SSTInit SST_InitializeDevices
#define SSTConvertDB SST_ConvertToDecibels
#define SSTConvertHZ SST_ConvertToHertz
#define SSTPlaySound SST_PlaySound

//--------------------------------------------------
//	Класс:			MurenaLevel
//	Заголовок:		MurenaLevel
//	Описывает свойства уровня для наследования
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaLevel {
protected:
	static Graphics* gfx;
public:
	float ScreenWidth, ScreenHeight;
	BOOL mem, memp;
	DWORD vmemavail, vmemtotal;
	UINT hr, min, sec, msec;
	float mcsec, mcsec2;
	unsigned long long int memoryAll;
	float fps;
	bool console;
	int consoleSwitcher;
	double timeDelta1, timeTotal1;
	std::wstring AdapterName, buildnum;
	std::wstring CurrentLevelName, ConsoleInput;

	static void Initialize(Graphics* graphics) {
		gfx = graphics;
	}

	virtual float TranslateData(float PositionX, float PositionY, float add) = 0;
	virtual void TranslateRect(UINT width, UINT height) = 0;
	virtual void ShowData(float fpsVar, BOOL memUsedVar, BOOL memPeakVar) = 0;
	virtual void GetConsoleInput(LPCWSTR input) = 0;

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Render() = 0;

	/*virtual void SST_OpenChannel_Mono() = 0;
	//virtual void SST_CloseChannel_Mono() = 0;
	//virtual void SST_InitializeDevices() = 0;
	//virtual float SST_ConvertToDecibels() = 0;
	//virtual float SST_ConvertToHertz() = 0;
	//virtual bool SST_PlaySound(LPSTR name) = 0;*/
};