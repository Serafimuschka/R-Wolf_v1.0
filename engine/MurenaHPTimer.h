#pragma once
#include <Windows.h>

//--------------------------------------------------
//	Класс:			MurenaHPTimer
//	Заголовок:		MurenaHPTimer
//	Описывает возможности таймера повышенной точности
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
class MurenaHPTimer {
	LONGLONG startTime;
	LONGLONG lastCallToUpdate;
	LONGLONG currentCallToUpdate;
	LONGLONG frequency;
public:
	MurenaHPTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;
		Reset();
	}
	void Reset() {
		LARGE_INTEGER t;
		if (!QueryPerformanceCounter(&t)) {
			MessageBox(NULL, "Ошибка вычисления FPS", "MURENA2: ERROR", MB_OK);
			// Если будет постоянно выдавать ошибку - удалить это условие
		}
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}
	void Update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}
	double GetTimeTotal() {
		double d = currentCallToUpdate - startTime;
		return d / frequency;
	}
	double GetTimeDelta() {
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / frequency;
	}
};