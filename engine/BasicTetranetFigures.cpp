#include "BasicTetranetFigures.h"

Figure::Figure(float x, float y, int type) {
	switch (type) {
	case FIGURE_DEFAULT:
		gfx->DrawRectangle(x, y, 50, 20, 173, 255, 47, 255);
		break;
	}
}