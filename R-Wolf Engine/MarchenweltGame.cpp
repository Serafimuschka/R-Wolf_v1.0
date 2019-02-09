#include "MarchenweltGame.h"

void MarchenweltGame::load() {
	_chead = XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f);
	leftShutter = 8;
	saveFilePath = "marchenwelt.rwsave";
	if (isFirstLaunch) {
		level = 1;
		exper = 0;
		playerName = L"player";
		isFirstLaunch = false;
	}
	loadFile();
}

void MarchenweltGame::saveFile() {
	wofstream fout;
	fout.open(saveFilePath, ios_base::out);
	fout << isFirstLaunch << endl;
	fout << playerName << endl;
	fout << level << endl;
	fout << exper << endl;
	fout << money << endl;
	fout << buildmat << endl;
	fout << army << endl;
	fout << rating << endl;
	fout.close();
}

void MarchenweltGame::loadFile() {
	wifstream fin;
	fin.open(saveFilePath);
	fin >> isFirstLaunch >> playerName >> level >> exper;
	fin >> money >> buildmat >> army >> rating;
	fin.close();
}


void MarchenweltGame::update(double td, double tt) {
	GetCursorPos(&cPos);
	mouse = XMFLOAT2(cPos.x, cPos.y);
	saveFile();
	levExp = level * 2000;
	level = levExp / 2000;
	if (exper >= levExp) {
		level++;
		exper = 0;
	}
	if (leftBack && leftShutter >= SW - 530 ||
		leftBack && leftShutter <= SW - 530) leftShutter -= 50;
	if (leftShutter == 8) leftBack = false;
	if (leftClicked && leftShutter <= SW - 530) leftShutter += 50;
	else if (leftClicked && leftShutter >= SW - 530) leftClicked = false;

	if (exist(mouse, XMFLOAT4(leftShutter, 8.0f, leftShutter + 50, SH - 8.0f))) {
		_chead = XMFLOAT4(255.0f, 140.0f, 0.0f, 190.0f);
		if (GetAsyncKeyState(VK_LBUTTON) && leftShutter == 8) leftClicked = true;
		else if (GetAsyncKeyState(VK_LBUTTON) && leftShutter >= SW - 530) leftBack = true;
	}
	else {
		if (leftShutter == 8) _chead = XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f);
	}
	strMoney = to_wstring(money) + L" ₽";
	strMaterial = to_wstring(buildmat) + L" m³";
	strArmy = to_wstring(army) + L" units";
	strRating = L"Рейтинг поддержки: " + to_wstring(rating) + L"%";
}

void MarchenweltGame::render() {
	core->clscr(XMFLOAT3(15.0f, 15.0f, 15.0f));
	// Отрисовка игрового пространства
	// Линии за шторкой
	for (int i = 0; i <= SW; i += 60) {
		core->line(XMFLOAT4(leftShutter - 8, i, leftShutter + 58, i + 66), _chead, 20.0);
	}
	// Ограждение лишнего
	core->rect(XMFLOAT4(leftShutter - 28, 0, leftShutter, SH),
		XMFLOAT4(15.0f, 15.0f, 15.0f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(leftShutter - 28, 0, leftShutter + 92, 8),
		XMFLOAT4(15.0f, 15.0f, 15.0f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(leftShutter + 50, 0, leftShutter + 92, SH),
		XMFLOAT4(15.0f, 15.0f, 15.0f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(leftShutter - 28, SH - 8, leftShutter + 92, SH),
		XMFLOAT4(15.0f, 15.0f, 15.0f, 255.0f), 1.0, true);
	// Левая шторка
	core->rect(XMFLOAT4(5, 20, leftShutter, SH - 20), _chead, 1.0);
	core->rect(XMFLOAT4(0, 0, 5, SH), XMFLOAT4(15.0f, 15.0f, 15.0f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(leftShutter, 8.0f, leftShutter + 50, SH - 8.0f), _chead, 1.0);
	// Внутренности рамки
	core->rect(XMFLOAT4(368, 258, 632, 532), core->orange, 1.0);
	// sprite->draw(L"resources/img/elite.png", core, XMFLOAT2(374, 264), 255);
	core->rect(XMFLOAT4(582, 250, 634, 300), XMFLOAT4(15, 15, 15, 255), 1.0, true);
	core->line(XMFLOAT4(592, 258, 632, 298), core->orange);
	core->rect(XMFLOAT4(449, 499, 611, 565),
		XMFLOAT4(7.5f, 7.5f, 7.5f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(448, 498, 612, 566), core->orange, 1.0);
	core->rect(XMFLOAT4(389, 499, 427, 565),
		XMFLOAT4(7.5f, 7.5f, 7.5f, 255.0f), 1.0, true);
	core->rect(XMFLOAT4(388, 498, 428, 566), core->orange, 1.0);
	sprite->draw(L"resources/img/tec_sil.png", core, XMFLOAT2(450, 500), 255.0);
	// Рамка
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
	// Аватар игрока, уровень и имя
	sprite->draw(L"resources/img/avatar.png", core, XMFLOAT2(SW - 450.0f, 12.0f), 255.0);
	core->rect(XMFLOAT4(SW - 370.0f, 57.0f, SW - 370.0f +
		335.0f * (exper / (levExp * 0.01)) / 100, 73.0f),
		XMFLOAT4(0.0f, 128.0f, 0.0f, 128.0f), 1.0, true);
	core->rect(XMFLOAT4(SW - 370.0f, 56.0f, SW - 35.0f, 74.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 1.0);
	core->text(playerName.c_str(), XMFLOAT2(SW - 374.0f, 5.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 34.0, L"Roboto Thin");
	core->text(to_wstring(level + 1).c_str(), XMFLOAT2(SW - 30.0f, 53.0f),
		XMFLOAT4(200.0f, 200.0f, 200.0f, 128.0f), 18.0, L"Roboto Thin");
	core->text(to_wstring(exper).c_str(), 
		XMFLOAT2(SW - 370.0f + 335.0f * 0.5f - wcslen(to_wstring(exper).c_str()) * 7, 55.0f), 
		core->white, 14.0, L"Roboto Thin",
		DWRITE_TEXT_ALIGNMENT_CENTER);

	core->text(strMoney.c_str(), XMFLOAT2(SW - 450, 200), core->white, 15.0, L"Roboto Thin");
	core->text(strMaterial.c_str(), XMFLOAT2(SW - 450, 225), core->white, 15.0, L"Roboto Thin");
	core->text(strArmy.c_str(), XMFLOAT2(SW - 450, 250), core->white, 15.0, L"Roboto Thin");
	core->text(strRating.c_str(), XMFLOAT2(SW - 450, 275), core->white, 15.0, L"Roboto Thin");
}

void MarchenweltGame::unload() {

}