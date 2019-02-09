#pragma once
#include "RWLevel.h"
#include "RWController.h"

class MarchenweltGame : public RWLevel {
private:
	RWTimer* hpTimer;
	POINT cPos;
	XMFLOAT2 mouse;

	float leftShutter;
	XMFLOAT4 _chead;
	bool leftClicked, leftBack;

	LPCWSTR avatarPath;
	wstring strMoney, strMaterial, strArmy, strRating;
	wstring playerName;
	LPCSTR saveFilePath;
	bool isFirstLaunch = true;
	int exper, level, levExp;
	int money, buildmat, army;
	double rating;
public:
	void load() override;
	void unload() override;
	void update(double timeTotal, double timeDelta) override;
	void render() override;
	void saveFile();
	void loadFile();
};