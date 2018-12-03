
#include "RWHeaders.h"

RWLevel* RWController::currentLevel;
RWTimer* RWController::hpTimer;
bool RWController::isLoading;

void RWController::initialize() {
	isLoading = true;
	currentLevel = 0;
	hpTimer = new RWTimer();
}
void RWController::loadInitialLevel(RWLevel* level) {
	isLoading = true;
	currentLevel = level;
	currentLevel->load();
	isLoading = false;
}
void RWController::switchLevel(RWLevel* level) {
	isLoading = true;
	currentLevel->unload();
	level->load();
	delete currentLevel;
	currentLevel = level;
	isLoading = false;
}
void RWController::render() {
	if (isLoading) return;
	currentLevel->render();
}
void RWController::update() {
	if (isLoading) return;
	hpTimer->update();
	currentLevel->update(hpTimer->getTimeTotal(), hpTimer->getTimeDelta());
}