#include "RWController.h"
#include "RWGraphics.h"

RWLevel* RWController::currentLevel;
RWTimer* RWController::hpTimer;
bool RWController::IsLoading;

void RWController::SendCoordinates(XMFLOAT2 vec) {
	currentLevel->TranslateData(XMFLOAT2(vec.x, vec.y));
	IsLoading = false;
}
void RWController::SendAction(UINT code) {
	currentLevel->Action(code);
	IsLoading = false;
}
void RWController::CurrentRect(UINT width, UINT height) {
	currentLevel->TranslateRect(width, height);
	IsLoading = false;
}
void RWController::Initialize() {
	IsLoading = true;
	currentLevel = 0;
	hpTimer = new RWTimer();
}
void RWController::LoadInitialLevel(RWLevel* level) {
	IsLoading = true;
	currentLevel = level;
	currentLevel->Load();
	IsLoading = false;
}
void RWController::SwitchLevel(RWLevel* level) {
	IsLoading = true;
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;
	IsLoading = false;
}
void RWController::Render() {
	if (IsLoading) return;
	currentLevel->Render();
}
void RWController::Update() {
	if (IsLoading) return;
	hpTimer->Update();
	currentLevel->Update(hpTimer->GetTimeTotal(), hpTimer->GetTimeDelta());
}
LPCWSTR RWController::TranslateSymbol(WCHAR in, WPARAM com) {
	WCHAR* out = new WCHAR[16];
	out += in;
	if (com == VK_RETURN) {
		currentLevel->GetConsoleInput(out);
		delete[] out;
	}
	return 0;
}