#pragma once
#include <Windows.h>

class RWTimer {
	LONGLONG startTime;
	LONGLONG lastCallToUpdate;
	LONGLONG currentCallToUpdate;
	LONGLONG frequency;
public:
	RWTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;
		reset();
	}
	void reset() {
		LARGE_INTEGER t;
		if (!QueryPerformanceCounter(&t)) {
			MessageBox(NULL, "Ошибка вычисления FPS", "RW: ERROR", MB_OK);
			// Если будет постоянно выдавать ошибку - удалить это условие
		}
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}
	void update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}
	double getTimeTotal() {
		double d = currentCallToUpdate - startTime;
		return d / frequency;
	}
	double getTimeDelta() {
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / frequency;
	}
};