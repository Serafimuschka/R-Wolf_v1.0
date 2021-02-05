#pragma once
#include "RWLevel.h"
#include "RWController.h"

enum ThemeComponents
{
	background,
	primaryColor,
	secondaryColor,
	secondaryDarkColor,
	laserBodyColor,
	rulerColor,
	rulerBackground,
	scalerAccent,
	scalerAccentActive,
	scalerBackground,
	scalerSecondary,
	textHeaders,
	textAccent
};

class mainscreen : public RWLevel {
private:
	RWTimer* hpTimer;
	POINT cPos;
	XMFLOAT2 mouse;

	XMFLOAT3 slit;
	XMFLOAT3 screen;
	XMFLOAT3 wave;

	wstring slitWidthStr;
	wstring screenDistanceStr;
	wstring wavelenStr;

	XMFLOAT2 lasPosBegin;
	XMFLOAT2 slitPosCenter;
	float screenDistance;
	float slitWidth;
	float wavelength;

	bool onSlit;
	bool onScreen;
	bool onWave;

	D2D1_COLOR_F slitClr;
	D2D1_COLOR_F lenClr;
	D2D1_COLOR_F screenClr;
	D2D1_COLOR_F laserEn;

	wstring manualHeader;
	wstring manualContent;

	inline double scale();

	vector<D2D1_COLOR_F>* theme;
public:
	void load() override;
	void unload() override;
	void update(double timeTotal, double timeDelta) override;
	void render() override;
};