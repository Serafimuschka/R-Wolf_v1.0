#pragma once
#include "MurenaGraphics.h"

class Figure {
	Graphics* gfx;
public:
	Figure(float x, float y, int type);
	~Figure();
	void Draw(float x, float y, int type);
};
enum FigureTypes {
	FIGURE_DEFAULT = 1,
	FIGURE_PIPE = 2,
	FIGURE_TRI = 3,
	FIGURE_QUAD = 4,
	FIGURE_PC = 5,
	FIGURE_SERVER = 6
};