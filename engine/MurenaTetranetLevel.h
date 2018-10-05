#pragma once
#include "MurenaSpriteSheet.h"
#include "MurenaLevel.h"
#include "MurenaHPTimer.h"
#include "BasicTetranetFigures.h"

class MurenaTetranetLevel : public MurenaLevel {
	// Блок переменных и указателей класса:
	MurenaSpriteSheet* sprite;		// Объект класса SpriteSheet
	MurenaHPTimer* hpTimer;

	int matrixA[61], matrixB[61], matrixC[60], matrixD[60], point;
	bool switcher;
	float xPos, yPos, xAccel, yAccel, n, m; // CWidth, CHeight, TWidth, THeight, WorkplaceWT, WorkplaceHT;
	int num, type;
	int xCoord, yCoord;
public:
	bool CheckMatrix(int x, int y);
	bool CheckConnection();

	float Transform90(float CW, float CH);
	void DrawTestRect(float x, float y);
	void DrawMatrixFigures();

	/// VIRTUAL FUNCTIONS BLOCK ::
	float TranslateData(float PositionX, float PositionY, float add) override;
	void TranslateRect(UINT width, UINT height) override;
	void Load() override;
	void Unload() override;
	void Update(double timeTotal, double timeDelta) override;
	void Render() override;
	/// VIRTUAL FUNCTIONS END
};