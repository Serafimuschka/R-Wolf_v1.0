#include "MarchenweltMenu.h"
#include "MarchenweltGame.h"

void MarchenweltMenu::load() {
	core->resize(core->endWidth, core->endHeight);
}

void MarchenweltMenu::update(double tt, double td) {
	POINT cursor;
	XMFLOAT2 curBuff;
	GetCursorPos(&cursor);
	curBuff = XMFLOAT2(cursor.x, cursor.y);
	if (exist(curBuff,
		XMFLOAT4(SW * 0.5f - 175, SH * 0.5f + 10, SW * 0.5f + 175, SH * 0.5f + 45))) {
		_cgame = XMFLOAT4(255.0f, 69.0f, 0.0f, 128.0f);
		if (GetAsyncKeyState(VK_LBUTTON)) RWController::loadInitialLevel(new MarchenweltGame);
	}
	else {
		_cgame = XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f);
	}
	if (exist(curBuff,
		XMFLOAT4(SW * 0.5f - 157.5f, SH * 0.5f + 50, SW * 0.5f + 157.5f, SH * 0.5f + 85))) {
		_csett = XMFLOAT4(255.0f, 69.0f, 0.0f, 128.0f);
		// if (GetAsyncKeyState(VK_LBUTTON));
	}
	else {
		_csett = XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f);
	}
	if (exist(curBuff,
		XMFLOAT4(SW * 0.5f - 87.5f, SH * 0.5f + 90, SW * 0.5f + 87.5f, SH * 0.5f + 125))) {
		_cexit = XMFLOAT4(255.0f, 69.0f, 0.0f, 128.0f);
		if (GetAsyncKeyState(VK_LBUTTON)) exit(0);
	}
	else {
		_cexit = XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f);
	}
}

void MarchenweltMenu::render() {
	core->clscr(XMFLOAT3(15.0f, 15.0f, 15.0f));
	// Interface element: frame
	core->line(XMFLOAT4(5.0f, 5.0f, 30.0f, 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(5.0f, 5.0f, 5.0f, 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(30.0f, 5.0f, SW - 30.0f, 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f));
	core->line(XMFLOAT4(SW - 5.0f, 5.0f, SW - 30.0f, 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(SW - 5.0f, 5.0f, SW - 5.0f, 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(5.0f, SH - 5.0f, 30.0f, SH - 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(5.0f, SH - 5.0f, 5.0f, SH - 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(30.0f, SH - 5.0f, SW - 30.0f, SH - 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f));
	core->line(XMFLOAT4(SW - 5.0f, SH - 5.0f, SW - 30.0f, SH - 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(SW - 5.0f, SH - 5.0f, SW - 5.0f, SH - 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 3.0);
	core->line(XMFLOAT4(5.0f, 30.0f, 5.0f, SH - 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f));
	core->line(XMFLOAT4(SW - 5.0f, 30.0f, SW - 5.0f, SH - 30.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f));
	
	core->line(XMFLOAT4(SW*0.5, 0, SW*0.5, SH), core->green);
	core->line(XMFLOAT4(0, SH*0.5, SW, SH*0.5), core->green);

	// Текст в центре
	core->text(L"MΛRCHENWELT", XMFLOAT2(SW * 0.5f - 275, SH * 0.5f - 50),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f),
		50.0, L"Roboto Thin", DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_EXTRA_LIGHT);
	core->text(L"Новая игра", XMFLOAT2(SW * 0.5f - 175, SH * 0.5f + 10),
		_cgame,
		35.0, L"Roboto Thin", DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_EXTRA_LIGHT);
	core->text(L"Настройки", XMFLOAT2(SW * 0.5f - 157.5f, SH * 0.5f + 50),
		_csett,
		35.0, L"Roboto Thin", DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_EXTRA_LIGHT);
	core->text(L"Выход", XMFLOAT2(SW * 0.5f - 87.5f, SH * 0.5f + 90),
		_cexit,
		35.0, L"Roboto Thin", DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_EXTRA_LIGHT);
}

void MarchenweltMenu::unload() {

}