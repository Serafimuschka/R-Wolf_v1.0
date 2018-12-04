//
//
//
//
//
//	kalterseele, 2018
//

#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <wchar.h>
#include <D2D1.h>
#include <DXGI.h>
#include <DWrite.h>
#include <xnamath.h>
#include <iostream>
#include <string>
#include <sstream>

#define _RW_USE_PHYSICS_CONSTANTS
#include "RWPhysicsConstants.h"

#define _RW_USE_GLOBAL_DEFINITIONS
#include "RWGlobalDefinitions.h"

using namespace D2D1;
using namespace std;

#define rwfont					wstring
#define RT						renderTarget

class RWGraphics {
	ID2D1Factory*				factory;
	IDWriteFactory*				wFactory;
	IDWriteTextFormat*			textFormat;
	ID2D1HwndRenderTarget*		renderTarget;
	ID2D1SolidColorBrush*		brush;
	ID2D1PathGeometry*			path;
public:
	struct ScalableMatrix5x4F {
		double _11, _12, _13, _14;
		double _21, _22, _23, _24;
		double _31, _32, _33, _34;
		double _41, _42, _43, _44;
		double _51, _52, _53, _54;
	};
	struct ScalableObjectProperties {
		double _11, _12, _13, _14;
		double _21, _22, _23, _24;
		D2D1_FIGURE_BEGIN figureBegin;
		D2D1_FIGURE_END figureEnd;
	};
	D2D1_COLOR_F	white = ColorF(ColorF::White);
	D2D1_COLOR_F	snow = ColorF(ColorF::Snow);
	D2D1_COLOR_F	honeydew = ColorF(ColorF::Honeydew);
	D2D1_COLOR_F	mintCream = ColorF(ColorF::MintCream);
	D2D1_COLOR_F	azure = ColorF(ColorF::Azure);
	D2D1_COLOR_F	aliceBlue = ColorF(ColorF::AliceBlue);
	D2D1_COLOR_F	ghostWhite = ColorF(ColorF::GhostWhite);
	D2D1_COLOR_F	whiteSmoke = ColorF(ColorF::WhiteSmoke);
	D2D1_COLOR_F	seaShell = ColorF(ColorF::SeaShell);
	D2D1_COLOR_F	beige = ColorF(ColorF::Beige);
	D2D1_COLOR_F	oldLace = ColorF(ColorF::OldLace);
	D2D1_COLOR_F	floralWhite = ColorF(ColorF::FloralWhite);
	D2D1_COLOR_F	ivory = ColorF(ColorF::Ivory);
	D2D1_COLOR_F	antiqueWhite = ColorF(ColorF::AntiqueWhite);
	D2D1_COLOR_F	linen = ColorF(ColorF::Linen);
	D2D1_COLOR_F	mistyRose = ColorF(ColorF::MistyRose);
	D2D1_COLOR_F	lavenderBlush = ColorF(ColorF::LavenderBlush);
	D2D1_COLOR_F	gainsboro = ColorF(ColorF::Gainsboro);
	D2D1_COLOR_F	lightGray = ColorF(ColorF::LightGray);
	D2D1_COLOR_F	silver = ColorF(ColorF::Silver);
	D2D1_COLOR_F	darkGray = ColorF(ColorF::DarkGray);
	D2D1_COLOR_F	gray = ColorF(ColorF::Gray);
	D2D1_COLOR_F	dimGray = ColorF(ColorF::DimGray);
	D2D1_COLOR_F	lightSlateGray = ColorF(ColorF::LightSlateGray);
	D2D1_COLOR_F	slateGray = ColorF(ColorF::SlateGray);
	D2D1_COLOR_F	darkSlateGray = ColorF(ColorF::DarkSlateGray);
	D2D1_COLOR_F	black = ColorF(ColorF::Black);
	D2D1_COLOR_F	indianRed = ColorF(ColorF::IndianRed);
	D2D1_COLOR_F	lightCoral = ColorF(ColorF::LightCoral);
	D2D1_COLOR_F	salmon = ColorF(ColorF::Salmon);
	D2D1_COLOR_F	darkSalmon = ColorF(ColorF::DarkSalmon);
	D2D1_COLOR_F	lightSalmon = ColorF(ColorF::LightSalmon);
	D2D1_COLOR_F	crimson = ColorF(ColorF::Crimson);
	D2D1_COLOR_F	red = ColorF(ColorF::Red);
	D2D1_COLOR_F	firebrick = ColorF(ColorF::Firebrick);
	D2D1_COLOR_F	darkRed = ColorF(ColorF::DarkRed);
	D2D1_COLOR_F	pink = ColorF(ColorF::Pink);
	D2D1_COLOR_F	lightPink = ColorF(ColorF::LightPink);
	D2D1_COLOR_F	hotPink = ColorF(ColorF::HotPink);
	D2D1_COLOR_F	deepPink = ColorF(ColorF::DeepPink);
	D2D1_COLOR_F	mediumVioletRed = ColorF(ColorF::MediumVioletRed);
	D2D1_COLOR_F	paleVioletRed = ColorF(ColorF::PaleVioletRed);
	D2D1_COLOR_F	coral = ColorF(ColorF::Coral);
	D2D1_COLOR_F	tomato = ColorF(ColorF::Tomato);
	D2D1_COLOR_F	orangeRed = ColorF(ColorF::OrangeRed);
	D2D1_COLOR_F	darkOrange = ColorF(ColorF::DarkOrange);
	D2D1_COLOR_F	orange = ColorF(ColorF::Orange);
	D2D1_COLOR_F	gold = ColorF(ColorF::Gold);
	D2D1_COLOR_F	yellow = ColorF(ColorF::Yellow);
	D2D1_COLOR_F	lightYellow = ColorF(ColorF::LightYellow);
	D2D1_COLOR_F	lemonChiffon = ColorF(ColorF::LemonChiffon);
	D2D1_COLOR_F	lightGoldenrodYellow = ColorF(ColorF::LightGoldenrodYellow);
	D2D1_COLOR_F	papayaWhip = ColorF(ColorF::PapayaWhip);
	D2D1_COLOR_F	moccasin = ColorF(ColorF::Moccasin);
	D2D1_COLOR_F	peachPuff = ColorF(ColorF::PeachPuff);
	D2D1_COLOR_F	paleGoldenrod = ColorF(ColorF::PaleGoldenrod);
	D2D1_COLOR_F	khaki = ColorF(ColorF::Khaki);
	D2D1_COLOR_F	lavender = ColorF(ColorF::Lavender);
	D2D1_COLOR_F	thistle = ColorF(ColorF::Thistle);
	D2D1_COLOR_F	plum = ColorF(ColorF::Plum);
	D2D1_COLOR_F	violet = ColorF(ColorF::Violet);
	D2D1_COLOR_F	orchid = ColorF(ColorF::Orchid);
	D2D1_COLOR_F	magenta = ColorF(ColorF::Magenta);
	D2D1_COLOR_F	mediumOrchid = ColorF(ColorF::MediumOrchid);
	D2D1_COLOR_F	mediumPurple = ColorF(ColorF::MediumPurple);
	D2D1_COLOR_F	blueViolet = ColorF(ColorF::BlueViolet);
	D2D1_COLOR_F	darkViolet = ColorF(ColorF::DarkViolet);
	D2D1_COLOR_F	darkOrchid = ColorF(ColorF::DarkOrchid);
	D2D1_COLOR_F	darkMagenta = ColorF(ColorF::DarkMagenta);
	D2D1_COLOR_F	purple = ColorF(ColorF::Purple);
	D2D1_COLOR_F	indigo = ColorF(ColorF::Indigo);
	D2D1_COLOR_F	slateBlue = ColorF(ColorF::SlateBlue);
	D2D1_COLOR_F	darkSlateBlue = ColorF(ColorF::DarkSlateBlue);
	D2D1_COLOR_F	cornsilk = ColorF(ColorF::Cornsilk);
	D2D1_COLOR_F	blanchedAlmond = ColorF(ColorF::BlanchedAlmond);
	D2D1_COLOR_F	bisque = ColorF(ColorF::Bisque);
	D2D1_COLOR_F	navajoWhite = ColorF(ColorF::NavajoWhite);
	D2D1_COLOR_F	wheat = ColorF(ColorF::Wheat);
	D2D1_COLOR_F	burlyWood = ColorF(ColorF::BurlyWood);
	D2D1_COLOR_F	tan = ColorF(ColorF::Tan);
	D2D1_COLOR_F	rosyBrown = ColorF(ColorF::RosyBrown);
	D2D1_COLOR_F	sandyBrown = ColorF(ColorF::SandyBrown);
	D2D1_COLOR_F	goldenrod = ColorF(ColorF::Goldenrod);
	D2D1_COLOR_F	darkGoldenrod = ColorF(ColorF::DarkGoldenrod);
	D2D1_COLOR_F	peru = ColorF(ColorF::Peru);
	D2D1_COLOR_F	chocolate = ColorF(ColorF::Chocolate);
	D2D1_COLOR_F	saddleBrown = ColorF(ColorF::SaddleBrown);
	D2D1_COLOR_F	sienna = ColorF(ColorF::Sienna);
	D2D1_COLOR_F	brown = ColorF(ColorF::Brown);
	D2D1_COLOR_F	maroon = ColorF(ColorF::Maroon);
	D2D1_COLOR_F	greenYellow = ColorF(ColorF::GreenYellow);
	D2D1_COLOR_F	chartreuse = ColorF(ColorF::Chartreuse);
	D2D1_COLOR_F	lawnGreen = ColorF(ColorF::LawnGreen);
	D2D1_COLOR_F	lime = ColorF(ColorF::Lime);
	D2D1_COLOR_F	limeGreen = ColorF(ColorF::LimeGreen);
	D2D1_COLOR_F	paleGreen = ColorF(ColorF::PaleGreen);
	D2D1_COLOR_F	lightGreen = ColorF(ColorF::LightGreen);
	D2D1_COLOR_F	mediumSpringGreen = ColorF(ColorF::MediumSpringGreen);
	D2D1_COLOR_F	springGreen = ColorF(ColorF::SpringGreen);
	D2D1_COLOR_F	mediumSeaGreen = ColorF(ColorF::MediumSeaGreen);
	D2D1_COLOR_F	seaGreen = ColorF(ColorF::SeaGreen);
	D2D1_COLOR_F	forestGreen = ColorF(ColorF::ForestGreen);
	D2D1_COLOR_F	green = ColorF(ColorF::Green);
	D2D1_COLOR_F	darkGreen = ColorF(ColorF::DarkGreen);
	D2D1_COLOR_F	yellowGreen = ColorF(ColorF::YellowGreen);
	D2D1_COLOR_F	oliveDrab = ColorF(ColorF::OliveDrab);
	D2D1_COLOR_F	olive = ColorF(ColorF::Olive);
	D2D1_COLOR_F	darkOliveGreen = ColorF(ColorF::DarkOliveGreen);
	D2D1_COLOR_F	mediumAquamarine = ColorF(ColorF::MediumAquamarine);
	D2D1_COLOR_F	darkSeaGreen = ColorF(ColorF::DarkSeaGreen);
	D2D1_COLOR_F	lightSeaGreen = ColorF(ColorF::LightSeaGreen);
	D2D1_COLOR_F	darkCyan = ColorF(ColorF::DarkCyan);
	D2D1_COLOR_F	teal = ColorF(ColorF::Teal);
	D2D1_COLOR_F	cyan = ColorF(ColorF::Cyan);
	D2D1_COLOR_F	lightCyan = ColorF(ColorF::LightCyan);
	D2D1_COLOR_F	paleTurquoise = ColorF(ColorF::PaleTurquoise);
	D2D1_COLOR_F	aquamarine = ColorF(ColorF::Aquamarine);
	D2D1_COLOR_F	turquoise = ColorF(ColorF::Turquoise);
	D2D1_COLOR_F	mediumTurquoise = ColorF(ColorF::MediumTurquoise);
	D2D1_COLOR_F	darkTurquoise = ColorF(ColorF::DarkTurquoise);
	D2D1_COLOR_F	cadetBlue = ColorF(ColorF::CadetBlue);
	D2D1_COLOR_F	steelBlue = ColorF(ColorF::SteelBlue);
	D2D1_COLOR_F	lightSteelBlue = ColorF(ColorF::LightSteelBlue);
	D2D1_COLOR_F	powderBlue = ColorF(ColorF::PowderBlue);
	D2D1_COLOR_F	lightBlue = ColorF(ColorF::LightBlue);
	D2D1_COLOR_F	skyBlue = ColorF(ColorF::SkyBlue);
	D2D1_COLOR_F	lightSkyBlue = ColorF(ColorF::LightSkyBlue);
	D2D1_COLOR_F	deepSkyBlue = ColorF(ColorF::DeepSkyBlue);
	D2D1_COLOR_F	dodgerBlue = ColorF(ColorF::DodgerBlue);
	D2D1_COLOR_F	cornflowerBlue = ColorF(ColorF::CornflowerBlue);
	D2D1_COLOR_F	mediumSlateBlue = ColorF(ColorF::MediumSlateBlue);
	D2D1_COLOR_F	royalBlue = ColorF(ColorF::RoyalBlue);
	D2D1_COLOR_F	blue = ColorF(ColorF::Blue);
	D2D1_COLOR_F	mediumBlue = ColorF(ColorF::MediumBlue);
	D2D1_COLOR_F	darkBlue = ColorF(ColorF::DarkBlue);
	D2D1_COLOR_F	navy = ColorF(ColorF::Navy);
	D2D1_COLOR_F	midnightBlue = ColorF(ColorF::MidnightBlue);

	rwfont			agency = L"Agency FB";
	rwfont			agencyCyrillic = L"Agency FB Cyrillic";
	rwfont			alien = L"Alien Encounters(RUS BY LYAJKA)";
	rwfont			arial = L"Arial";
	rwfont			b52 = L"B52";
	rwfont			consolas = L"Consolas";
	rwfont			digital7 = L"Digital-7 Mono";
	rwfont			fixedsys = L"Fixedsys";
	rwfont			gost = L"GOST type A";
	rwfont			holoLens = L"HoloLens MDL2 Assets";
	rwfont			roboto = L"Roboto Thin";
	rwfont			larabiefont = L"Larabiefont Free";
	rwfont			segoe = L"Segoe MDL2 Assets";
	rwfont			system = L"System";
	rwfont			symbol = L"Symbol type A";
	rwfont			terminal = L"Terminal";

	LPCWSTR			RW_Agency = agency.c_str();
	LPCWSTR			RW_AgencyCyrillic = agencyCyrillic.c_str();
	LPCWSTR			RW_Alien = alien.c_str();
	LPCWSTR			RW_Arial = arial.c_str();
	LPCWSTR			RW_B52 = b52.c_str();
	LPCWSTR			RW_Consolas = consolas.c_str();
	LPCWSTR			RW_Digital7 = digital7.c_str();
	LPCWSTR			RW_Fixedsys = fixedsys.c_str();
	LPCWSTR			RW_GOST = gost.c_str();
	LPCWSTR			RW_HoloLens = holoLens.c_str();
	LPCWSTR			RW_Roboto = roboto.c_str();
	LPCWSTR			RW_Larabiefont = larabiefont.c_str();
	LPCWSTR			RW_Segoe = segoe.c_str();
	LPCWSTR			RW_System = system.c_str();
	LPCWSTR			RW_Symbol = symbol.c_str();
	LPCWSTR			RW_Terminal = terminal.c_str();

	RWGraphics();
	~RWGraphics();

	ID2D1RenderTarget* getRenderTarget() {
		return RT;
	}

	bool init(HWND windowHandle);

	void beginDraw() {
		RT->BeginDraw();
	}
	void endDraw() {
		RT->EndDraw();
	}

	void clearScreen(XMFLOAT3 color);
	void clearScreen(D2D1_COLOR_F color);

	void resize(UINT width, UINT height) {
		RT->Resize(SizeU(width, height));
	}

	void drawCircle(XMFLOAT2 coord, XMFLOAT2 radius, XMFLOAT4 color,
		double thick, bool fill = false);
	void drawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color,
		double thick, bool fill = false);
	void drawRectangle(XMFLOAT4 coord, D2D1_COLOR_F color,
		double thick, bool fill = false);
	void drawRectangle(XMFLOAT4 coord, XMFLOAT4 color,
		double thick, bool fill = false);
	void progressBar(XMFLOAT2 coord, XMFLOAT2 size,
		double maxval, double curval, D2D1_COLOR_F color);
	void progressBar(XMFLOAT2 coord, XMFLOAT2 size,
		double maxval, double curval, XMFLOAT4 color);
	void drawLine(XMFLOAT4 coord, D2D1_COLOR_F color, double thick = 1.0f);
	void drawLine(XMFLOAT4 coord, XMFLOAT4 color, double thick = 1.0f);
	void drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB,
		XMFLOAT2 pointC, D2D1_COLOR_F color, double thick = 1.0f);
	void drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB,
		XMFLOAT2 pointC, XMFLOAT4 color, double thick = 1.0f);
	void drawArc(XMFLOAT2 center, XMFLOAT2 radius,
		D2D1_COLOR_F color, double angle, double thick = 1.0f);
	void drawArc(XMFLOAT2 center, XMFLOAT2 radius,
		XMFLOAT4 color, double angle, double thick = 1.0f);
	void printText(LPCWSTR output, XMFLOAT2 coord, D2D1_COLOR_F color);
	void printText(LPCWSTR output, XMFLOAT2 coord, XMFLOAT4 color);
	void printNum(double output, XMFLOAT2 coord, double shift,
		LPCWSTR font, double size, XMFLOAT4 color,
		DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING);
	void printNum(double output, XMFLOAT2 coord, double shift,
		LPCWSTR font, double size, D2D1_COLOR_F color,
		DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING);
	void printTextManual(LPCWSTR output, XMFLOAT2 coord, double size,
		LPCWSTR family, D2D1_COLOR_F color);
	void printTextManual(LPCWSTR output, XMFLOAT2 coord, double size,
		LPCWSTR family, XMFLOAT4 color);
	void drawEntity(Item obj, XMFLOAT2 coord, XMFLOAT2 properties, int type);
	void drawScalableObject(ScalableObjectProperties config, XMFLOAT2 offsetA,
		XMFLOAT2 offsetB, XMFLOAT2 offsetC, XMFLOAT4 offsetD, RWGraphics func);
	void showInfo(const char* argv);
	void showHardware(double timerIn, wstring buildName, wstring buildNum);
	void showMenu();
	void drawInterface(const char* argv);
};