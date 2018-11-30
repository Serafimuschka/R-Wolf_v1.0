#include "RWController.h"
#include "RWGraphics.h"

RWLevel* RWController::currentLevel;
RWTimer* RWController::hpTimer;
bool RWController::IsLoading;

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