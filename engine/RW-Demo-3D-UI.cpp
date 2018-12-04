//-----------------------------------------------------------------//
//	R-Wolf Demonstrations Pack: Scalable forms					   //
//																   //
//	#descr_english
//																   //
//	#descr_russian
//																   //
//																   //
//	Presented by kalterseele, 2018								   //
//-----------------------------------------------------------------//

#include "RW-Demo-3D-UI.h"

#define _RW_USE_GLOBAL_DEFINITIONS
#define _RW_USE_PHYSICS_CONSTANTS
#include "RWGlobalDefinitions.h"
#include "RWPhysicsConstants.h"

// Описываем структуру слоя:
struct layoutRect {
	double Ax, Bx, Cx, Dx;
	double Ay, By, Cy, Dy;
	double layoutHeightLeft, layoutHeightRight;
	double layoutWidthTop, layoutWidthBottom;
	double constLayoutWidth, constLayoutHeight;
};
layoutRect layout;
RWGraphics::ScalableMatrix5x4F matrix;

void RWDemo_3DUI::load() {
	// Устанавливаем позицию курсора в центр экрана:
	SetCursorPos(SW / 2, SH / 2);

	// Задаём первичные координаты плоскости:
	pointA = XMFLOAT2(SW * 0.1, SH * 0.1);
	pointB = XMFLOAT2(SW * 0.9, SH * 0.1);
	pointC = XMFLOAT2(SW * 0.9, SH * 0.9);
	pointD = XMFLOAT2(SW * 0.1, SH * 0.9);
}

void RWDemo_3DUI::update(double total, double delta) {
	// Получаем координаты курсора:
	GetCursorPos(&cursorPos);
	
	// Изменяем значения сторон в зависимости от позиции курсора:
	// Увеличивается на n% та сторона, в которую передвинут курсор на n%
	// и уменьшается на n% противоположная сторона
	// n = (lenght - cursorPos.x) / lenght;
	n = (SW * 0.5 - cursorPos.x) / (SW * 0.5) * 0.5;
	m = (SH * 0.5 - cursorPos.y) / (SH * 0.5) * 0.5;
	
	// Определяем параметры опорных точек:
	pointA.y = (SH * 0.1) - ((SH * 0.1) * n);
	pointD.y = (SH * 0.9) + ((SH * 0.1) * n);
	pointB.y = (SH * 0.1) + ((SH * 0.1) * n);
	pointC.y = (SH * 0.9) - ((SH * 0.1) * n);

	pointA.x = (SW * 0.1) - ((SW * 0.1) * m);
	pointB.x = (SW * 0.9) + ((SW * 0.1) * m);
	pointC.x = (SW * 0.9) - ((SW * 0.1) * m);
	pointD.x = (SW * 0.1) + ((SW * 0.1) * m);
	
}

void RWDemo_3DUI::render() {
	core->clscr(core->black);

	// Отладчик положения курсора:
	core->rect(XMFLOAT4(cursorPos.x - 4, cursorPos.y - 4, cursorPos.x + 4, cursorPos.y + 4),
		core->red, 1.0f, true);

	// Рисуем сам слой:
	core->line(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), core->yellowGreen, 3.0f);
	core->textman(L"A", XMFLOAT2(pointA.x, pointA.y), 20.0f,
		core->RW_Consolas, core->yellowGreen);
	core->line(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), core->yellowGreen, 3.0f);
	core->textman(L"B", XMFLOAT2(pointB.x, pointB.y), 20.0f,
		core->RW_Consolas, core->yellowGreen);
	core->line(XMFLOAT4(pointC.x, pointC.y, pointD.x, pointD.y), core->yellowGreen, 3.0f);
	core->textman(L"C", XMFLOAT2(pointC.x, pointC.y), 20.0f,
		core->RW_Consolas, core->yellowGreen);
	core->line(XMFLOAT4(pointD.x, pointD.y, pointA.x, pointA.y), core->yellowGreen, 3.0f);
	core->textman(L"D", XMFLOAT2(pointD.x, pointD.y), 20.0f,
		core->RW_Consolas, core->yellowGreen);

	// Объект внутри слоя:


	// Информация для отладки:
	core->textnum(cursorPos.x, XMFLOAT2(15, 15), 0.0f, core->RW_Consolas, 15.0f,
		core->yellowGreen);
	core->textnum(cursorPos.y, XMFLOAT2(15, 45), 0.0f, core->RW_Consolas, 15.0f,
		core->yellowGreen);
	core->textnum(100 * layout.layoutWidthTop, XMFLOAT2(15, 75), 0.0f,
		core->RW_Consolas, 15.0f, core->yellowGreen);
	core->textnum(100 * layout.layoutWidthBottom, XMFLOAT2(15, 105), 0.0f,
		core->RW_Consolas, 15.0f, core->yellowGreen);
	core->textnum(100 * layout.layoutHeightLeft, XMFLOAT2(105, 75), 0.0f,
		core->RW_Consolas, 15.0f, core->yellowGreen);
	core->textnum(100 * layout.layoutHeightRight, XMFLOAT2(105, 105), 0.0f,
		core->RW_Consolas, 15.0f, core->yellowGreen);
	core->textnum(abs(100 * n), XMFLOAT2(15, 135), 0.0f,
		core->RW_Consolas, 15.0f, core->yellowGreen);

	core->textman(L"R-Wolf Engine: Scalable forms demonstration [1.01]", XMFLOAT2(60, 15), 15.0f,
		core->RW_Consolas, core->yellowGreen);
}

void RWDemo_3DUI::unload() {

}