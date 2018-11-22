#include "RWGraphics.h"
#include "RWController.h"
#include "RWMainMenu.h"
#include <iostream>
#include <string>
#include <fstream>

#define _RW_USE_GLOBAL_DEFINITIONS
#define _RW_USE_PHYSICS_CONSTANTS
#include "RWGlobalDefinitions.h"
#include "RWPhysicsConstants.h"

void RWMainMenu::Load() {
	tex = new RWSpriteSystem(L"glass_01.png", core);
	picture = new RWSpriteSystem(L"test.png", core, 128, 128);
	mapsize = XMFLOAT2(4096, 1024);
	encounter = 0;
	objectpos = XMFLOAT2(545, 15);
	startpos = XMFLOAT2(0, 0);
	dtime = 0;
	ttime = 0;
	buildname = L"Maverick [Pre-Alpha edition]";
	buildnum = L"0034";
	con_in = '\0';
	speed = 3;
	sound->initialize();
}

void RWMainMenu::Update(double timeTotal, double timeDelta) {
	dtime = timeDelta;
	ttime = timeTotal;
	int s = ttime;
	if (s % 3 == 0) anim = 0;
	//if (objectpos.x <= SW - 15) startpos.x--;
	//if (objectpos.y <= SH - 15) startpos.y--;
	//if (objectpos.x >= SW - 143) startpos.x++;
	//if (objectpos.y >= SH - 143) startpos.y++;
}

void RWMainMenu::Render() {
	core->clscr(XMFLOAT3(15, 15, 15));
	sound->open();
	core->rw_iface("open");
	picture->Draw(anim, objectpos, 255);
	tex->Texturize(startpos, mapsize, 25);
	//sprite->Draw(L"texture.png", core, startpos, 255);
		// Исполнение кода уровня
		// ScriptInit("MainMenuScript.xml");
	core->rw_iface("close");
	core->d_info(encounter, ttime);
	core->d_hware(ttime, buildname, buildnum);
	core->d_menu();
	core->number(sound->getrecsize(), XMFLOAT2(700, 300), 0, core->RW_Consolas, 25, core->GreenYellow);
	encounter++;
	sound->close();
}


double RWMainMenu::TranslateData(XMFLOAT2 vec) {
	objectpos.x += vec.x * speed;
	objectpos.y += vec.y * speed;
	if (vec.x != 0 || vec.y != 0) anim = 2;
	return 0;
}

void RWMainMenu::Action(UINT code) {
	switch (code) {
	case RW_ACTION_SHOOT:
		if (anim == 2) anim = 3;
		else anim = 1;
		break;
	case RW_ACTION_JUMP:
		break;
	}
}

void RWMainMenu::TranslateRect(UINT w, UINT h) {
	SW = w;
	SH = h;
}

void RWMainMenu::GetConsoleInput(WCHAR* input) {
	con_in = input;
}

void RWMainMenu::Unload() {
	delete picture;
	delete tex;
}