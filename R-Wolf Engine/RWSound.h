#pragma once
#include <Windows.h>
#include <mmsystem.h>

class RWSound {
private:
	double					recBytes;
	char					buff[8192] = "";
	HWAVEIN					hIn = NULL;
	WAVEHDR					wave;
	WAVEFORMATEX			format;
public:
	HRESULT					initialize();
	HRESULT					open();
	HRESULT					close();
	double					getrecsize();
};