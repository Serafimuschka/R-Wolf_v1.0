#include "RWLoading.h"
#include "MarchenweltMenu.h"

void RWLoading::load() {
	timeout = 1;
	logoName = L"resources/img/engine_logo.png";
	buff = L"# R-Wolf Engine 1.2 Alpha version, debug mode... \n# kalterseele, 2018-2019 \n";
	isPrevUnloaded = true;
	//sprite = new RWSpriteSystemA();
}

void RWLoading::update(double, double) {
	if (isPrevUnloaded) {
		timeout++;
	}
	if (timeout == 250) buff += L"# Initialising game 'Marchenwelt' \n";
	if (timeout == 260) buff += L"# Checking your system... ";
	if (timeout == 295) buff += L"OK \n";
	if (timeout == 350) buff += L"# Level loaded, waiting... \n";
	if (isNextReady) {
		isPrevUnloaded = false;
		timeout++;
	}
	if (timeout == 500) {
		buff += L"# Level is ready to start... \n";
		ready = true;
	}
	if (timeout == 525) buff += L"# Launching \n";
	if (ready && timeout == 550) {
		isNextReady = false;
		RWController::loadInitialLevel(new MarchenweltMenu);
	}
}

void RWLoading::render() {
	core->clscr(XMFLOAT3(15.0f, 15.0f, 15.0f));
	sprite->draw(logoName, core,
		XMFLOAT2(SW * 0.5f - 256, SH * 0.5f - 256), 255.0);
	core->text(buff.c_str(), XMFLOAT2(10.0f, 10.0f), core->white, 12.0, L"Consolas");
	core->loadBar(SW, SH, timeout, 550);
}

void RWLoading::unload() {
	//delete sprite;
}