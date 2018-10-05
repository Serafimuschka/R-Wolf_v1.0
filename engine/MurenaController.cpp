#include "MurenaController.h"
#include "MurenaGraphics.h"

//--------------------------------------------------
//	Класс:			MurenaController
//	Исходник:		MurenaController
//	Выполняет роль контроллера перехода между уровнями
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
MurenaLevel* MurenaController::currentLevel;
MurenaHPTimer* MurenaController::hpTimer;
bool MurenaController::IsLoading;

void MurenaController::SendCoordinates(float x, float y, float add) {
	currentLevel->TranslateData(x, y, add);
	IsLoading = false;
}
void MurenaController::CurrentRect(UINT width, UINT height) {
	currentLevel->TranslateRect(width, height);
	IsLoading = false;
}
void MurenaController::Initialize() {
	IsLoading = true;
	currentLevel = 0;
	hpTimer = new MurenaHPTimer();
}
void MurenaController::LoadInitialLevel(MurenaLevel* level) {
	IsLoading = true;
	currentLevel = level;
	currentLevel->Load();
	IsLoading = false;
}
void MurenaController::SwitchLevel(MurenaLevel* level) {
	IsLoading = true;
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;
	IsLoading = false;
}
void MurenaController::Render() {
	if (IsLoading) return;
	currentLevel->Render();
}
void MurenaController::Update() {
	if (IsLoading) return;
	hpTimer->Update();
	currentLevel->Update(hpTimer->GetTimeTotal(), hpTimer->GetTimeDelta());
}
LPCWSTR MurenaController::TranslateSymbol(LPCWSTR symbol) {
	LPCWSTR output = symbol;
	currentLevel->GetConsoleInput(output);
	return 0;
}