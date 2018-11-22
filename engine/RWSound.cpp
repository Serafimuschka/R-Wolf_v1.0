#include "RWSound.h"

HRESULT RWSound::initialize() {
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.wBitsPerSample = 24;
	format.nChannels = 1;
	format.nSamplesPerSec = 96000;
	return 1;
}

HRESULT RWSound::open() {
	waveInOpen(&hIn, WAVE_MAPPER, &format, NULL, 0L, CALLBACK_WINDOW);
	wave.lpData = buff;
	wave.dwBufferLength = strlen(buff);
	wave.dwBytesRecorded = NULL;
	wave.dwUser = NULL;
	wave.dwFlags = NULL;
	wave.dwLoops = NULL;
	wave.lpNext = NULL;
	wave.reserved = NULL;

	waveInPrepareHeader(hIn, &wave, sizeof(WAVEHDR));
	waveInAddBuffer(hIn, &wave, sizeof(WAVEHDR));
	waveInStart(hIn);
	return 1;
}

HRESULT RWSound::close() {
	waveInReset(hIn);
	waveInUnprepareHeader(hIn, &wave, sizeof(WAVEHDR));
	waveInClose(hIn);
	return 1;
}

DOUBLE RWSound::getrecsize() {
	return wave.dwBytesRecorded;
}
