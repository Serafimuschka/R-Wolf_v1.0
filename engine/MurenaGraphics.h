#pragma once
#include <Windows.h>
#include <D2D1.h>
#include <DWrite.h>
#include <xnamath.h>
#include <string>
typedef const wchar_t* LPCWSTR;
//--------------------------------------------------
//	Класс:			Graphics
//	Заголовок:		MurenaGraphics
//	Описывает основной функционал графического модуля
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
class Graphics {
	HWND						mainHWND;
	ID2D1Factory*				factory;
	IDWriteFactory*				wfactory;
	IDWriteTextFormat*			textformat;
	IDWriteTextFormat*			textformatfps;
	ID2D1HwndRenderTarget*		RT;
	ID2D1SolidColorBrush*		brush;
public:
		// White -> Black
	D2D1_COLOR_F	White = D2D1::ColorF(D2D1::ColorF::White);
	D2D1_COLOR_F	Snow = D2D1::ColorF(D2D1::ColorF::Snow);
	D2D1_COLOR_F	Honeydew = D2D1::ColorF(D2D1::ColorF::Honeydew);
	D2D1_COLOR_F	MintCream = D2D1::ColorF(D2D1::ColorF::MintCream);
	D2D1_COLOR_F	Azure = D2D1::ColorF(D2D1::ColorF::Azure);
	D2D1_COLOR_F	AliceBlue = D2D1::ColorF(D2D1::ColorF::AliceBlue);
	D2D1_COLOR_F	GhostWhite = D2D1::ColorF(D2D1::ColorF::GhostWhite);
	D2D1_COLOR_F	WhiteSmoke = D2D1::ColorF(D2D1::ColorF::WhiteSmoke);
	D2D1_COLOR_F	SeaShell = D2D1::ColorF(D2D1::ColorF::SeaShell);
	D2D1_COLOR_F	Beige = D2D1::ColorF(D2D1::ColorF::Beige);
	D2D1_COLOR_F	OldLace = D2D1::ColorF(D2D1::ColorF::OldLace);
	D2D1_COLOR_F	FloralWhite = D2D1::ColorF(D2D1::ColorF::FloralWhite);
	D2D1_COLOR_F	Ivory = D2D1::ColorF(D2D1::ColorF::Ivory);
	D2D1_COLOR_F	AntiqueWhite = D2D1::ColorF(D2D1::ColorF::AntiqueWhite);
	D2D1_COLOR_F	Linen = D2D1::ColorF(D2D1::ColorF::Linen);
	D2D1_COLOR_F	MistyRose = D2D1::ColorF(D2D1::ColorF::MistyRose);
	D2D1_COLOR_F	LavenderBlush = D2D1::ColorF(D2D1::ColorF::LavenderBlush);
	D2D1_COLOR_F	Gainsboro = D2D1::ColorF(D2D1::ColorF::Gainsboro);
	D2D1_COLOR_F	LightGray = D2D1::ColorF(D2D1::ColorF::LightGray);
	D2D1_COLOR_F	Silver = D2D1::ColorF(D2D1::ColorF::Silver);
	D2D1_COLOR_F	DarkGray = D2D1::ColorF(D2D1::ColorF::DarkGray);
	D2D1_COLOR_F	Gray = D2D1::ColorF(D2D1::ColorF::Gray);
	D2D1_COLOR_F	DimGray = D2D1::ColorF(D2D1::ColorF::DimGray);
	D2D1_COLOR_F	LightSlateGray = D2D1::ColorF(D2D1::ColorF::LightSlateGray);
	D2D1_COLOR_F	SlateGray = D2D1::ColorF(D2D1::ColorF::SlateGray);
	D2D1_COLOR_F	DarkSlateGray = D2D1::ColorF(D2D1::ColorF::DarkSlateGray);
	D2D1_COLOR_F	Black = D2D1::ColorF(D2D1::ColorF::Black);
		// Other colors (Red -> Blue):
	D2D1_COLOR_F	IndianRed = D2D1::ColorF(D2D1::ColorF::IndianRed);
	D2D1_COLOR_F	LightCoral = D2D1::ColorF(D2D1::ColorF::LightCoral);
	D2D1_COLOR_F	Salmon = D2D1::ColorF(D2D1::ColorF::Salmon);
	D2D1_COLOR_F	DarkSalmon = D2D1::ColorF(D2D1::ColorF::DarkSalmon);
	D2D1_COLOR_F	LightSalmon = D2D1::ColorF(D2D1::ColorF::LightSalmon);
	D2D1_COLOR_F	Crimson = D2D1::ColorF(D2D1::ColorF::Crimson);
	D2D1_COLOR_F	Red = D2D1::ColorF(D2D1::ColorF::Red);
	D2D1_COLOR_F	Firebrick = D2D1::ColorF(D2D1::ColorF::Firebrick);
	D2D1_COLOR_F	DarkRed = D2D1::ColorF(D2D1::ColorF::DarkRed);
	D2D1_COLOR_F	Pink = D2D1::ColorF(D2D1::ColorF::Pink);
	D2D1_COLOR_F	LightPink = D2D1::ColorF(D2D1::ColorF::LightPink);
	D2D1_COLOR_F	HotPink = D2D1::ColorF(D2D1::ColorF::HotPink);
	D2D1_COLOR_F	DeepPink = D2D1::ColorF(D2D1::ColorF::DeepPink);
	D2D1_COLOR_F	MediumVioletRed = D2D1::ColorF(D2D1::ColorF::MediumVioletRed);
	D2D1_COLOR_F	PaleVioletRed = D2D1::ColorF(D2D1::ColorF::PaleVioletRed);
	D2D1_COLOR_F	Coral = D2D1::ColorF(D2D1::ColorF::Coral);
	D2D1_COLOR_F	Tomato = D2D1::ColorF(D2D1::ColorF::Tomato);
	D2D1_COLOR_F	OrangeRed = D2D1::ColorF(D2D1::ColorF::OrangeRed);
	D2D1_COLOR_F	DarkOrange = D2D1::ColorF(D2D1::ColorF::DarkOrange);
	D2D1_COLOR_F	Orange = D2D1::ColorF(D2D1::ColorF::Orange);
	D2D1_COLOR_F	Gold = D2D1::ColorF(D2D1::ColorF::Gold);
	D2D1_COLOR_F	Yellow = D2D1::ColorF(D2D1::ColorF::Yellow);
	D2D1_COLOR_F	LightYellow = D2D1::ColorF(D2D1::ColorF::LightYellow);
	D2D1_COLOR_F	LemonChiffon = D2D1::ColorF(D2D1::ColorF::LemonChiffon);
	D2D1_COLOR_F	LightGoldenrodYellow = D2D1::ColorF(D2D1::ColorF::LightGoldenrodYellow);
	D2D1_COLOR_F	PapayaWhip = D2D1::ColorF(D2D1::ColorF::PapayaWhip);
	D2D1_COLOR_F	Moccasin = D2D1::ColorF(D2D1::ColorF::Moccasin);
	D2D1_COLOR_F	PeachPuff = D2D1::ColorF(D2D1::ColorF::PeachPuff);
	D2D1_COLOR_F	PaleGoldenrod = D2D1::ColorF(D2D1::ColorF::PaleGoldenrod);
	D2D1_COLOR_F	Khaki = D2D1::ColorF(D2D1::ColorF::Khaki);
	D2D1_COLOR_F	Lavender = D2D1::ColorF(D2D1::ColorF::Lavender);
	D2D1_COLOR_F	Thistle = D2D1::ColorF(D2D1::ColorF::Thistle);
	D2D1_COLOR_F	Plum = D2D1::ColorF(D2D1::ColorF::Plum);
	D2D1_COLOR_F	Violet = D2D1::ColorF(D2D1::ColorF::Violet);
	D2D1_COLOR_F	Orchid = D2D1::ColorF(D2D1::ColorF::Orchid);
	D2D1_COLOR_F	Magenta = D2D1::ColorF(D2D1::ColorF::Magenta);
	D2D1_COLOR_F	MediumOrchid = D2D1::ColorF(D2D1::ColorF::MediumOrchid);
	D2D1_COLOR_F	MediumPurple = D2D1::ColorF(D2D1::ColorF::MediumPurple);
	D2D1_COLOR_F	BlueViolet = D2D1::ColorF(D2D1::ColorF::BlueViolet);
	D2D1_COLOR_F	DarkViolet = D2D1::ColorF(D2D1::ColorF::DarkViolet);
	D2D1_COLOR_F	DarkOrchid = D2D1::ColorF(D2D1::ColorF::DarkOrchid);
	D2D1_COLOR_F	DarkMagenta = D2D1::ColorF(D2D1::ColorF::DarkMagenta);
	D2D1_COLOR_F	Purple = D2D1::ColorF(D2D1::ColorF::Purple);
	D2D1_COLOR_F	Indigo = D2D1::ColorF(D2D1::ColorF::Indigo);
	D2D1_COLOR_F	SlateBlue = D2D1::ColorF(D2D1::ColorF::SlateBlue);
	D2D1_COLOR_F	DarkSlateBlue = D2D1::ColorF(D2D1::ColorF::DarkSlateBlue);
	D2D1_COLOR_F	Cornsilk = D2D1::ColorF(D2D1::ColorF::Cornsilk);
	D2D1_COLOR_F	BlanchedAlmond = D2D1::ColorF(D2D1::ColorF::BlanchedAlmond);
	D2D1_COLOR_F	Bisque = D2D1::ColorF(D2D1::ColorF::Bisque);
	D2D1_COLOR_F	NavajoWhite = D2D1::ColorF(D2D1::ColorF::NavajoWhite);
	D2D1_COLOR_F	Wheat = D2D1::ColorF(D2D1::ColorF::Wheat);
	D2D1_COLOR_F	BurlyWood = D2D1::ColorF(D2D1::ColorF::BurlyWood);
	D2D1_COLOR_F	Tan = D2D1::ColorF(D2D1::ColorF::Tan);
	D2D1_COLOR_F	RosyBrown = D2D1::ColorF(D2D1::ColorF::RosyBrown);
	D2D1_COLOR_F	SandyBrown = D2D1::ColorF(D2D1::ColorF::SandyBrown);
	D2D1_COLOR_F	Goldenrod = D2D1::ColorF(D2D1::ColorF::Goldenrod);
	D2D1_COLOR_F	DarkGoldenrod = D2D1::ColorF(D2D1::ColorF::DarkGoldenrod);
	D2D1_COLOR_F	Peru = D2D1::ColorF(D2D1::ColorF::Peru);
	D2D1_COLOR_F	Chocolate = D2D1::ColorF(D2D1::ColorF::Chocolate);
	D2D1_COLOR_F	SaddleBrown = D2D1::ColorF(D2D1::ColorF::SaddleBrown);
	D2D1_COLOR_F	Sienna = D2D1::ColorF(D2D1::ColorF::Sienna);
	D2D1_COLOR_F	Brown = D2D1::ColorF(D2D1::ColorF::Brown);
	D2D1_COLOR_F	Maroon = D2D1::ColorF(D2D1::ColorF::Maroon);
	D2D1_COLOR_F	GreenYellow = D2D1::ColorF(D2D1::ColorF::GreenYellow);
	D2D1_COLOR_F	Chartreuse = D2D1::ColorF(D2D1::ColorF::Chartreuse);
	D2D1_COLOR_F	LawnGreen = D2D1::ColorF(D2D1::ColorF::LawnGreen);
	D2D1_COLOR_F	Lime = D2D1::ColorF(D2D1::ColorF::Lime);
	D2D1_COLOR_F	LimeGreen = D2D1::ColorF(D2D1::ColorF::LimeGreen);
	D2D1_COLOR_F	PaleGreen = D2D1::ColorF(D2D1::ColorF::PaleGreen);
	D2D1_COLOR_F	LightGreen = D2D1::ColorF(D2D1::ColorF::LightGreen);
	D2D1_COLOR_F	MediumSpringGreen = D2D1::ColorF(D2D1::ColorF::MediumSpringGreen);
	D2D1_COLOR_F	SpringGreen = D2D1::ColorF(D2D1::ColorF::SpringGreen);
	D2D1_COLOR_F	MediumSeaGreen = D2D1::ColorF(D2D1::ColorF::MediumSeaGreen);
	D2D1_COLOR_F	SeaGreen = D2D1::ColorF(D2D1::ColorF::SeaGreen);
	D2D1_COLOR_F	ForestGreen = D2D1::ColorF(D2D1::ColorF::ForestGreen);
	D2D1_COLOR_F	Green = D2D1::ColorF(D2D1::ColorF::Green);
	D2D1_COLOR_F	DarkGreen = D2D1::ColorF(D2D1::ColorF::DarkGreen);
	D2D1_COLOR_F	YellowGreen = D2D1::ColorF(D2D1::ColorF::YellowGreen);
	D2D1_COLOR_F	OliveDrab = D2D1::ColorF(D2D1::ColorF::OliveDrab);
	D2D1_COLOR_F	Olive = D2D1::ColorF(D2D1::ColorF::Olive);
	D2D1_COLOR_F	DarkOliveGreen = D2D1::ColorF(D2D1::ColorF::DarkOliveGreen);
	D2D1_COLOR_F	MediumAquamarine = D2D1::ColorF(D2D1::ColorF::MediumAquamarine);
	D2D1_COLOR_F	DarkSeaGreen = D2D1::ColorF(D2D1::ColorF::DarkSeaGreen);
	D2D1_COLOR_F	LightSeaGreen = D2D1::ColorF(D2D1::ColorF::LightSeaGreen);
	D2D1_COLOR_F	DarkCyan = D2D1::ColorF(D2D1::ColorF::DarkCyan);
	D2D1_COLOR_F	Teal = D2D1::ColorF(D2D1::ColorF::Teal);
	D2D1_COLOR_F	Cyan = D2D1::ColorF(D2D1::ColorF::Cyan);
	D2D1_COLOR_F	LightCyan = D2D1::ColorF(D2D1::ColorF::LightCyan);
	D2D1_COLOR_F	PaleTurquoise = D2D1::ColorF(D2D1::ColorF::PaleTurquoise);
	D2D1_COLOR_F	Aquamarine = D2D1::ColorF(D2D1::ColorF::Aquamarine);
	D2D1_COLOR_F	Turquoise = D2D1::ColorF(D2D1::ColorF::Turquoise);
	D2D1_COLOR_F	MediumTurquoise = D2D1::ColorF(D2D1::ColorF::MediumTurquoise);
	D2D1_COLOR_F	DarkTurquoise = D2D1::ColorF(D2D1::ColorF::DarkTurquoise);
	D2D1_COLOR_F	CadetBlue = D2D1::ColorF(D2D1::ColorF::CadetBlue);
	D2D1_COLOR_F	SteelBlue = D2D1::ColorF(D2D1::ColorF::SteelBlue);
	D2D1_COLOR_F	LightSteelBlue = D2D1::ColorF(D2D1::ColorF::LightSteelBlue);
	D2D1_COLOR_F	PowderBlue = D2D1::ColorF(D2D1::ColorF::PowderBlue);
	D2D1_COLOR_F	LightBlue = D2D1::ColorF(D2D1::ColorF::LightBlue);
	D2D1_COLOR_F	SkyBlue = D2D1::ColorF(D2D1::ColorF::SkyBlue);
	D2D1_COLOR_F	LightSkyBlue = D2D1::ColorF(D2D1::ColorF::LightSkyBlue);
	D2D1_COLOR_F	DeepSkyBlue = D2D1::ColorF(D2D1::ColorF::DeepSkyBlue);
	D2D1_COLOR_F	DodgerBlue = D2D1::ColorF(D2D1::ColorF::DodgerBlue);
	D2D1_COLOR_F	CornflowerBlue = D2D1::ColorF(D2D1::ColorF::CornflowerBlue);
	D2D1_COLOR_F	MediumSlateBlue = D2D1::ColorF(D2D1::ColorF::MediumSlateBlue);
	D2D1_COLOR_F	RoyalBlue = D2D1::ColorF(D2D1::ColorF::RoyalBlue);
	D2D1_COLOR_F	Blue = D2D1::ColorF(D2D1::ColorF::Blue);
	D2D1_COLOR_F	MediumBlue = D2D1::ColorF(D2D1::ColorF::MediumBlue);
	D2D1_COLOR_F	DarkBlue = D2D1::ColorF(D2D1::ColorF::DarkBlue);
	D2D1_COLOR_F	Navy = D2D1::ColorF(D2D1::ColorF::Navy);
	D2D1_COLOR_F	MidnightBlue = D2D1::ColorF(D2D1::ColorF::MidnightBlue);
	ID2D1RenderTarget*			GetRenderTarget() {
		return RT;
	}
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	void BeginDraw() {
		RT->BeginDraw();
	}
	void EndDraw() {
		RT->EndDraw();
	}

	void CreateConsole(std::wstring input = L"MURENA2 CONSOLE TERMINAL");

	void CreateButton(LPCWSTR name, LPCWSTR text, XMFLOAT2 coord, XMFLOAT2 size, UINT id, HINSTANCE hInst = GetModuleHandle(NULL));
	void GetCurrentMainHWND(HWND hWindow) {
		mainHWND = hWindow;
	}

	// Функция ClearScreen(XMFLOAT3 color) принимает значения в диапазоне от 0 до 255!
	void ClearScreen(XMFLOAT3 color);
	void ClearScreen(D2D1_COLOR_F color);
	void Resize(UINT width, UINT height) {
		RT->Resize(D2D1::SizeU(width, height));
	}

	//void DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color, bool fill);
	void DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, XMFLOAT4 color, float thick, bool fill = false);
	void DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color, float thick, bool fill = false);

	void DrawRectangle(XMFLOAT4 coord, D2D1_COLOR_F color, float thick, bool fill = false);
	void DrawRectangle(XMFLOAT4 coord, XMFLOAT4 color, float thick, bool fill = false);

	void DrawLine(XMFLOAT4 coord, D2D1_COLOR_F color);
	void DrawLine(XMFLOAT4 coord, XMFLOAT4 color);

	void PrintText(LPWSTR text, int lenght, float x, float y, float r, float g, float b, float a);
	void PrintText(LPCWSTR text, XMFLOAT2 coord, D2D1_COLOR_F color);
	void PrintText(LPCWSTR text, XMFLOAT2 coord, XMFLOAT4 color);

	void PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, XMFLOAT4 color, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING);
	void PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING);

	void PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color);
	void PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color);
	void PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color);
	void PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color);
};