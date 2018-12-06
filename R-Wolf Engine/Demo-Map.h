#pragma once
#include <atltime.h>

#include "RWLevel.h"
#include "RWGraphics.h"
#include "RWController.h"

class Map : public RWLevel {
	RWTimer* hpTimer;
	XMFLOAT2 mapPos;
	int _rDest, _bDest, _tDest;
	double bottomDelta, rightDelta, textDelta;
	bool _rWasClicked, _bWasClicked, _tWasClicked;
	bool _rBackward, _bBackward, _tBackward;
	bool markerP, markerT;
	bool aboutIn, textIn;
	XMFLOAT2 _beforeClickPos, _map, _from, _to;
	XMFLOAT2 _pointFrom, _pointTo;
	D2D1_COLOR_F bottomColor, rightColor,
		aboutColor, textColor, audioColor,
		backColor;
	wstring time;
	POINT cursorPos;
public:
	// ������� Load(): �������������� ������� � �������������, ��������� ������
	void load() override;
	// ������� Unload(): �������� ������, ������������� ������
	void unload() override;
	// ������� Update(): ���������� �������� ���������� � Load() ���������� ����� ������� Render()
	void update(double timeTotal, double timeDelta) override;
	// ������� Render(): ��������� ����� �� �������� ����������
	void render() override;
};