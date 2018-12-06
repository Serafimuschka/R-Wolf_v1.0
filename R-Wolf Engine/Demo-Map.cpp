#include "Demo-Map.h"
#include <mmsystem.h>

#define IW0 (SW - 360) * 0.5
#define IW (SW + 360) * 0.5
#define IH0 64
#define IH SH - 64

bool isExistIn(XMFLOAT2 coord, D2D1_SIZE_F size, XMFLOAT2 in) {
	if ((in.x >= coord.x && in.x <= (size.width + coord.x) &&
		(in.y >= coord.y && in.y <= (size.height + coord.y)))) {
		return true;
	}
	else {
		return false;
	}
}

void Map::load() {
	tex = new RWSpriteSystem(L"map.png", core);
	mapPos = XMFLOAT2(-1766 / 2, 0);
	_pointFrom = XMFLOAT2(0, 0);
	_pointTo = XMFLOAT2(0, 0);
	_rWasClicked = false;
	_rBackward = false;
	_tWasClicked = false;
	_tBackward = false;
	_bWasClicked = false;
	_bBackward = false;
	markerP = false;
	markerT = false;
	rightDelta = 0;
	bottomDelta = 0;
	textDelta = IH;
}

void Map::update(double total, double delta) {
	bool isClick = false;
	bool isBottomShutter = false;
	bool isRightShutter = false;

	bool existRight = isExistIn(XMFLOAT2(IW - 36 - rightDelta, IH0 + 18), SizeF(36, 36),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existBottom = isExistIn(XMFLOAT2(SW * 0.5 - 16, IH - 56 - bottomDelta), SizeF(32, 20),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existMap = isExistIn(XMFLOAT2(IW0, IH0 + 54), SizeF(320, 530),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existAbout = isExistIn(XMFLOAT2(IW - rightDelta + 15, IH0 + 60), SizeF(250, 22),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existAboutBack = isExistIn(XMFLOAT2(IW0 + 35, IH0 + 270), SizeF(250, 100),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existOpenText = isExistIn(XMFLOAT2(IW0 + 15, IH - 36 - bottomDelta), SizeF(305, 20),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existOpenAudio = isExistIn(XMFLOAT2(IW0 + 15, IH - 8 - bottomDelta), SizeF(305, 20),
		XMFLOAT2(cursorPos.x, cursorPos.y));
	bool existBack = isExistIn(XMFLOAT2(IW0 + 15, IH - textDelta + 4), SizeF(305, 20),
		XMFLOAT2(cursorPos.x, cursorPos.y));

	CTime t = CTime::GetCurrentTime();
	int hr = t.GetHour();
	int min = t.GetMinute();

	wstring str_hr = to_wstring(hr);
	wstring str_min = to_wstring(min);

	time += str_hr;
	time += L":";
	time += str_min;

	// Запрашиваем позицию курсора
	GetCursorPos(&cursorPos);

	// Не даём ему покинуть окно
	if (cursorPos.x < IW0) {
		SetCursorPos(IW0, cursorPos.y);
	}
	else if (cursorPos.x > IW) {
		SetCursorPos(IW, cursorPos.y);
	}
	if (cursorPos.y < IH0 + 18) {
		SetCursorPos(cursorPos.x, IH0 + 18);
	}
	else if (cursorPos.y > IH - 36) {
		SetCursorPos(cursorPos.x, IH - 36);
	}

	if (existRight) {
		rightColor = core->white;
	}
	else {
		rightColor = core->black;
	}

	if (existBottom) {
		bottomColor = core->white;
	}
	else {
		bottomColor = core->black;
	}

	if (existAbout) {
		aboutColor = core->orange;
	}
	else {
		aboutColor = core->darkGray;
	}

	if (existOpenText) {
		textColor = core->orange;
	}
	else {
		textColor = core->darkGray;
	}

	if (existOpenAudio) {
		audioColor = core->orange;
	}
	else {
		audioColor = core->darkGray;
	}

	if (existBack) {
		backColor = core->white;
	}
	else {
		backColor = core->black;
	}

	// Обработка нажатия:
	if (GetAsyncKeyState(VK_CONTROL)) {
		_pointFrom = XMFLOAT2(cursorPos.x, cursorPos.y);
		markerP = true;
	}
	if (GetAsyncKeyState(VK_SHIFT)) {
		_pointTo = XMFLOAT2(cursorPos.x, cursorPos.y);
		markerT = true;
	}
	if (GetAsyncKeyState(VK_TAB)) {
		_pointFrom = XMFLOAT2(0, 0);
		_pointTo = XMFLOAT2(0, 0);
		markerP = false;
		markerT = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON)) {
		isClick = true;
	}
	if (isClick) {
		// В случае клика по карте
		if (existMap) {
			mapPos.x = _map.x + (cursorPos.x - _beforeClickPos.x);
			mapPos.y = _map.y + (cursorPos.y - _beforeClickPos.y);
			if (markerP) {
				_pointFrom.x = _from.x + (cursorPos.x - _beforeClickPos.x);
				_pointFrom.y = _from.y + (cursorPos.y - _beforeClickPos.y);
			}
			if (markerT) {
				_pointTo.x = _to.x + (cursorPos.x - _beforeClickPos.x);
				_pointTo.y = _to.y + (cursorPos.y - _beforeClickPos.y);
			}
		}

		// В случае клика по правой шторке
		if (existRight) {
			_rWasClicked = true;
			_rDest = 256;
		}
		if (existRight && _rBackward) {
			_rDest = 0;
		}

		// В случае клика по нижней шторке
		if (existBottom) {
			_bWasClicked = true;
			_bDest = 100;
		}
		if (existBottom && _bBackward) {
			_bDest = 0;
		}

		// О программе:
		if (existAbout) {
			aboutIn = true;
		}

		if (existAboutBack) {
			aboutIn = false;
		}

		// Прочитать текст:
		if (existOpenText) {
			textIn = true;
			_tWasClicked = true;
			_tDest = IH0;
		}

		// Вернуться:
		if (existBack && _tBackward) {
			_tWasClicked = true;
			textIn = false;
			_tDest = IH;
		}

		// Прослушать аудио:
		if (existOpenAudio) {
			PlaySound("sound.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
	}
	else {
		_beforeClickPos = XMFLOAT2(cursorPos.x, cursorPos.y);
		_map = mapPos;
		if (markerP) _from = _pointFrom;
		if (markerT) _to = _pointTo;
	}

	// Выполнение анимаций открытия шторок:
	if (_rWasClicked && !isClick) {
		if (rightDelta < _rDest) {
			if (rightDelta == _rDest - 16) _rWasClicked = false;
			rightDelta += 16;
			_rBackward = true;
		}
		else if (rightDelta > _rDest) {
			if (rightDelta == _rDest + 16) _rWasClicked = false;
			rightDelta -= 16;
			_rBackward = false;
		}
	}
	if (_bWasClicked && !isClick) {
		if (bottomDelta < _bDest) {
			if (bottomDelta == _bDest - 10) _bWasClicked = false;
			bottomDelta += 10;
			_bBackward = true;
		}
		else if (bottomDelta > _bDest) {
			if (bottomDelta == _bDest + 10) _bWasClicked = false;
			bottomDelta -= 10;
			_bBackward = false;
		}
	}
	if (_tWasClicked && !isClick) {
		if (textDelta < _tDest) {
			if (textDelta == _tDest - 32) _tWasClicked = false;
			textDelta += 32;
			_tBackward = false;
		}
		else if (textDelta > _tDest) {
			if (textDelta == _tDest + 32) _tWasClicked = false;
			textDelta -= 32;
			_tBackward = true;
		}
	}
}

void Map::render() {
	core->clscr(core->black);

	// Карта
	tex->texturize(mapPos, XMFLOAT2(1766, 875), 255.0f);

	// Маркеры
	core->tri(_pointFrom, XMFLOAT2(_pointFrom.x - 15, _pointFrom.y - 60),
		XMFLOAT2(_pointFrom.x + 15, _pointFrom.y - 45), core->blue, 3.0f);
	core->tri(_pointTo, XMFLOAT2(_pointTo.x - 15, _pointTo.y - 60),
		XMFLOAT2(_pointTo.x + 15, _pointTo.y - 45), core->red, 3.0f);
	if (markerP && markerT) {
		core->line(XMFLOAT4(_pointFrom.x, _pointFrom.y, _pointTo.x, _pointTo.y),
			core->darkBlue, 3.0f);
	}

	// Шторка снизу
	core->rect(XMFLOAT4(IW0, IH - 36 - bottomDelta, IW, IH - 36),
		core->white, 1.0f, true);

	// Холст шторы
	core->rect(XMFLOAT4(IW0, IH - 36 - bottomDelta, IW, IH - 56 - bottomDelta),
		core->orange, 1.0f, true);

	// Контент
	core->textman(L"Прочитать текст", XMFLOAT2(IW0, IH - 36 - bottomDelta), 18.0f,
		core->RW_Consolas, textColor);
	core->textman(L"Прослушать аудиозапись", XMFLOAT2(IW0, IH - 8 - bottomDelta), 18.0f,
		core->RW_Consolas, audioColor);

	// Кнопка
	core->line(XMFLOAT4(SW * 0.5 - 8, IH - 44 - bottomDelta, SW * 0.5, IH - 48 - bottomDelta),
		bottomColor, 2.0f);
	core->line(XMFLOAT4(SW * 0.5 + 8, IH - 44 - bottomDelta, SW * 0.5, IH - 48 - bottomDelta),
		bottomColor, 2.0f);

	// Шторка справа
	core->rect(XMFLOAT4(IW0, IH0 + 18, IW, IH0 + 54), core->orange, 1.0f, true);
	core->textman(L"Функциональный макет 1.0", XMFLOAT2(IW0 + 15, IH0 + 22), 18.0f, core->RW_Roboto,
		core->black);

	// Холст шторы
	core->rect(XMFLOAT4(IW - rightDelta, IH0 + 18, IW, IH - 36), core->white, 1.0f, true);
	core->rect(XMFLOAT4(IW - 32 - rightDelta, IH0 + 18, IW, IH0 + 54),
		core->orange, 1.0f, true);

	// Заголовок
	core->textman(L"Название программы", XMFLOAT2(IW - rightDelta + 15, IH0 + 18), 16.0f, L"Roboto Thin",
		core->white);
	core->textman(L"Версия: 0.0.0.0", XMFLOAT2(IW - rightDelta + 15, IH0 + 36), 12.0f, L"Roboto Thin",
		core->white);

	// Контент
	core->textman(L"О программе", XMFLOAT2(IW - rightDelta + 15, IH0 + 60), 22.0f, L"Roboto Thin",
		aboutColor);

	// Кнопка
	core->line(XMFLOAT4(IW - 20 - rightDelta, IH0 + 24, IW - 26 - rightDelta, IH0 + 36),
		rightColor, 2.0f);
	core->line(XMFLOAT4(IW - 20 - rightDelta, IH0 + 46, IW - 26 - rightDelta, IH0 + 36),
		rightColor, 2.0f);

	// Холст
	core->rect(XMFLOAT4(IW0, IH - textDelta, IW, IH0), core->white, 1.0f, true);
	if (textIn) {
		core->textman(L"Текст и фото в подарок", XMFLOAT2(IW0 + 15, IH0 + 25),
			16.0f, core->RW_Consolas, core->black);
		picture = new RWSpriteSystem(L"texture.png", core);
		picture->draw(XMFLOAT2(IW0 + 15, IH0 + 50));
		delete picture;
	}
	core->rect(XMFLOAT4(IW0, IH - textDelta, IW, IH - textDelta + 54), core->orange, 1.0f, true);
	core->textman(L"Вернуться назад", XMFLOAT2(IW0 + 15, IH - textDelta + 2), 18.0f,
		core->RW_Roboto, backColor);

	if (aboutIn) {
		core->rect(XMFLOAT4(IW0 + 35, IH0 + 270, IW - 35, IH - 270), core->orange, 1.0f, true);
		core->textman(L"Автор: kalterseele\nСделано с помощью kalterseele's\nR-Wolf 2D Engine\n\n06.12.18\nНажмите на окно для выхода",
			XMFLOAT2(IW0 + 50, IH0 + 285), 10.0f, core->RW_Consolas, core->white);
	}

	// Элементы UI Android:
	core->rect(XMFLOAT4(IW0, IH0, IW, IH0 + 18), core->black, 1.0f, true);
	core->textman(time.c_str(), XMFLOAT2(IW - 40, IH0), 14.0f, core->RW_Roboto,
		core->white);
	time = L"";
	core->rect(XMFLOAT4(IW0, IH, IW, IH - 36), core->black, 1.0f, true);
	core->ellipse(XMFLOAT2(SW * 0.5, IH - 18), XMFLOAT2(8, 8),
		core->white, 2.0f);
	core->tri(XMFLOAT2(IW0 + (IW - IW0) * 0.25, IH - 26),
		XMFLOAT2(IW0 + (IW - IW0) * 0.25, IH - 10),
		XMFLOAT2(IW0 + (IW - IW0) * 0.25 - 16 * sinf(PI / 3), IH - 18),
		core->white, 2.0f);
	core->rect(XMFLOAT4(IW0 + (IW - IW0) * 0.75, IH - 26, IW0 + (IW - IW0) * 0.75 + 16, IH - 10),
		core->white, 2.0f);

	// Границы экрана:
	core->rect(XMFLOAT4(0, 0, SW, IH0), core->lightSlateGray, 1.0f, true);
	core->rect(XMFLOAT4(0, IH, SW, SH), core->lightSlateGray, 1.0f, true);
	core->rect(XMFLOAT4(0, 0, IW0, SH), core->lightSlateGray, 1.0f, true);
	core->rect(XMFLOAT4(IW, 0, SW, SH), core->lightSlateGray, 1.0f, true);
	core->textman(L"Экспериментируйте!", XMFLOAT2(25, 25), 30.0f, core->RW_Consolas, core->white);
	core->textman(L"Графический визуализатор и движок R-Wolf 2D позволяет\nделать это с удовольствием",
		XMFLOAT2(25, 75), 15.0f, core->RW_Consolas, core->white);
	core->textman(L"Пробуйте, нажимайте, перемещайте...\nФункциональный макет демонстирирует приложения для\nдругих платформ, при должном желании можно даже собрать\nготовое решение внутри визуализатора.",
		XMFLOAT2(25, 125), 15.0f, core->RW_Consolas, core->white);
	core->textman(L"Клавишные команды макета:\nESC - завершить работу макета\nCTRL[удерж.] - поставить маркер А\nSHIFT[удерж.] - поставить маркер В\nTAB - сбросить маркеры\nЛКМ[удерж.] - скролл карты",
		XMFLOAT2(25, 250), 15.0f, core->RW_Consolas, core->white);
	core->textman(L"Created by kalterseele (c) 2018\nVK: vk.com/kalterseele\nInstagram: @kalterseele\nTelegram: @kalterseele\nRequest an engine's demos: einhorn.sv@gmail.com\nGitHub repository:\nhttps://github.com/Serafimuschka/R-Wolf_v1.0",
		XMFLOAT2(25, SH - 125), 12.0f, core->RW_Consolas, core->white);
}

void Map::unload() {
	delete tex;
}