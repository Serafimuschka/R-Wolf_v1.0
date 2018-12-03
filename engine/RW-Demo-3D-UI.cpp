//-----------------------------------------------------------------//
//	R-Wolf Demonstrations Pack: Dynamic 3D UI in 2D dimension      //
//	ƒемонстрационный пакет R-Wolf: ƒинамический 3D UI в плоскости  //
//																   //
//	#descr_english
//																   //
//	#descr_russian
//																   //
//																   //
//	Presented by kalterseele, 2018								   //
//-----------------------------------------------------------------//

#include "RWGraphics.h"
#include "RWController.h"
#include "RW-Demo-3D-UI.h"

#define _RW_USE_GLOBAL_DEFINITIONS
#define _RW_USE_PHYSICS_CONSTANTS
#include "RWGlobalDefinitions.h"
#include "RWPhysicsConstants.h"

void RWDemo_3DUI::Load() {
	// ”станавливаем позицию курсора в центр экрана:
	SetCursorPos(SW / 2, SH / 2);

	// «адаЄм первичные координаты плоскости:
	pointA = XMFLOAT2(SW * 0.1, SH * 0.1);
	pointB = XMFLOAT2(SW * 0.9, SH * 0.1);
	pointC = XMFLOAT2(SW * 0.9, SH * 0.9);
	pointD = XMFLOAT2(SW * 0.1, SH * 0.9);
}

void RWDemo_3DUI::Update(double total, double delta) {
	// ѕолучаем координаты курсора:
	GetCursorPos(&cursorPos);
	
	// »змен€ем значени€ сторон в зависимости от позиции курсора:
	// ”величиваетс€ на n% та сторона, в которую передвинут курсор на n%
	// и уменьшаетс€ на n% противоположна€ сторона
	// n = (lenght - cursorPos.x) / lenght;
	n = (SW * 0.5 - cursorPos.x) / (SW * 0.5) * 0.5;
	m = (SH * 0.5 - cursorPos.y) / (SH * 0.5) * 0.5;
	
	pointA.y = (SH * 0.1) - ((SH * 0.1) * n);
	pointD.y = (SH * 0.9) + ((SH * 0.1) * n);
	pointB.y = (SH * 0.1) + ((SH * 0.1) * n);
	pointC.y = (SH * 0.9) - ((SH * 0.1) * n);

	pointA.x = (SW * 0.1) - ((SW * 0.1) * m);
	pointB.x = (SW * 0.9) + ((SW * 0.1) * m);
	pointC.x = (SW * 0.9) - ((SW * 0.1) * m);
	pointD.x = (SW * 0.1) + ((SW * 0.1) * m);
	
}

void RWDemo_3DUI::Render() {
	core->clscr(core->Black);
	core->line(XMFLOAT4(0, 0, cursorPos.x, cursorPos.y), core->DarkGray, 2.0f);
	core->line(XMFLOAT4(0, SH, cursorPos.x, cursorPos.y), core->DarkGray, 2.0f);
	core->line(XMFLOAT4(SW, 0, cursorPos.x, cursorPos.y), core->DarkGray, 2.0f);
	core->line(XMFLOAT4(SW, SH, cursorPos.x, cursorPos.y), core->DarkGray, 2.0f);
	core->rect(XMFLOAT4(cursorPos.x - 8, cursorPos.y - 8, cursorPos.x + 8, cursorPos.y + 8), core->Red, 1.0f, true);

	core->line(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), core->YellowGreen, 3.0f);
	core->textman(L"A", XMFLOAT2(pointA.x, pointA.y), 20, core->RW_Consolas, core->YellowGreen);

	core->line(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), core->YellowGreen, 3.0f);
	core->textman(L"B", XMFLOAT2(pointB.x, pointB.y), 20, core->RW_Consolas, core->YellowGreen);

	core->line(XMFLOAT4(pointC.x, pointC.y, pointD.x, pointD.y), core->YellowGreen, 3.0f);
	core->textman(L"C", XMFLOAT2(pointC.x, pointC.y), 20, core->RW_Consolas, core->YellowGreen);

	core->line(XMFLOAT4(pointD.x, pointD.y, pointA.x, pointA.y), core->YellowGreen, 3.0f);
	core->textman(L"D", XMFLOAT2(pointD.x, pointD.y), 20, core->RW_Consolas, core->YellowGreen);
	core->textman(L"R-Wolf Engine: Scalable forms demonstration [1.01]", XMFLOAT2(60, 15), 15, core->RW_Consolas, core->YellowGreen);

	core->line(XMFLOAT4(pointA.x + 100, pointA.y + 25, pointD.x + 100, pointD.y - 200), core->OrangeRed, 3.0f);
	core->line(XMFLOAT4(pointB.x - 100, pointB.y + 25, pointC.x - 100, pointC.y - 200), core->OrangeRed, 3.0f);
	core->line(XMFLOAT4(pointA.x + 100, pointA.y + 25, pointB.x - 100, pointB.y + 25), core->OrangeRed, 3.0f);
	core->line(XMFLOAT4(pointD.x + 100, pointD.y - 200, pointC.x - 100, pointC.y - 200), core->OrangeRed, 3.0f);
	core->line(XMFLOAT4(pointA.x + 100, pointA.y + 25, pointC.x - 100, pointC.y - 200), core->OrangeRed, 3.0f);
	core->line(XMFLOAT4(pointD.x + 100, pointD.y - 200, pointB.x - 100, pointB.y + 25), core->OrangeRed, 3.0f);

	core->number(cursorPos.x, XMFLOAT2(15, 15), 0.0f, core->RW_Consolas, 15, core->YellowGreen);
	core->number(cursorPos.y, XMFLOAT2(15, 45), 0.0f, core->RW_Consolas, 15, core->YellowGreen);
	core->number(pointB.x, XMFLOAT2(15, 75), 0.0f, core->RW_Consolas, 15, core->YellowGreen);
	core->number(pointC.x, XMFLOAT2(15, 105), 0.0f, core->RW_Consolas, 15, core->YellowGreen);
	core->number(abs(100 * n), XMFLOAT2(15, 135), 0.0f, core->RW_Consolas, 15, core->YellowGreen);
}

void RWDemo_3DUI::Unload() {

}