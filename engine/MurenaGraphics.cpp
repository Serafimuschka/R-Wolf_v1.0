#include <DXGI.h>
#include <sstream>
#include "MurenaGraphics.h"

//--------------------------------------------------
//	Класс:			Graphics
//	Исходник:		MurenaGraphics
//	Реализовывает основной функционал графического модуля
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
Graphics::Graphics() {
	factory = NULL;
	wfactory = NULL;
	RT = NULL;
	brush = NULL;
}

Graphics::~Graphics() {
	if (factory) factory->Release();
	if (wfactory) wfactory->Release();
	if (RT) RT->Release();
	if (!brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle) {
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (!SUCCEEDED(hr)) return false;
	RECT rc;
	GetClientRect(windowHandle, &rc);
	hr = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle,
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)),
		&RT);
	if (!SUCCEEDED(hr)) return false;
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(wfactory), reinterpret_cast<IUnknown**>(&wfactory));
	if (!SUCCEEDED(hr)) return false;
	static const WCHAR fontName[] = L"Consolas";
	hr = wfactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"", &textformat);
	hr = wfactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, 15.0f, L"", &textformatfps);
	if (!SUCCEEDED(hr)) return false;
	return true;
}

void Graphics::CreateConsole(std::wstring input) {
	RT->CreateSolidColorBrush(D2D1::ColorF(30 / 255.0f, 30 / 255.0f, 30 / 255.0f, 100 / 255.0f), &brush);
	RT->FillRectangle(D2D1::RectF(0, GetSystemMetrics(SM_CYSCREEN) - 100, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)-3), brush);
	brush->Release();
	PrintTextManual(input.c_str(), XMFLOAT2(0, GetSystemMetrics(SM_CYSCREEN) - 100), 12, L"Consolas", Yellow);
}

void Graphics::ClearScreen(XMFLOAT3 color) {
	RT->Clear(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f));
}

void Graphics::ClearScreen(D2D1_COLOR_F color) {
	RT->Clear(color);
}

void Graphics::DrawLine(XMFLOAT4 coord, D2D1_COLOR_F color) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawLine(D2D1::Point2F(coord.x, coord.y), D2D1::Point2F(coord.z, coord.w), brush);
	brush->Release();
}

void Graphics::DrawLine(XMFLOAT4 coord, XMFLOAT4 color) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawLine(D2D1::Point2F(coord.x, coord.y), D2D1::Point2F(coord.z, coord.w), brush);
	brush->Release();
}

/*
void Graphics::DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color, bool fill) {
	RT->CreateSolidColorBrush(color, &brush);
	switch(fill) {
	case true:
		RT->FillEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush);
		break;
	case false:
		RT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush, 3.0f);
		break;
	}
	brush->Release();
}*/

void Graphics::DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, XMFLOAT4 color, float thick, bool fill) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	switch (fill) {
	case true:
		RT->FillEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush);
		break;
	case false:
		RT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush, thick);
		break;
	}
	brush->Release();
}

void Graphics::DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color, float thick, bool fill) {
	RT->CreateSolidColorBrush(color, &brush);
	switch (fill) {
	case true:
		RT->FillEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush);
		break;
	case false:
		RT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(coord.x, coord.y), radius.x, radius.y), brush, thick);
		break;
	}
	brush->Release();
}

void Graphics::DrawRectangle(XMFLOAT4 coord, D2D1_COLOR_F color, float thick, bool fill) {
	RT->CreateSolidColorBrush(color, &brush);
	switch (fill) {
	case true:
		RT->FillRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush);
		break;
	case false:
		RT->DrawRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush, thick);
		break;
	}
	brush->Release();
}

void Graphics::DrawRectangle(XMFLOAT4 coord, XMFLOAT4 color, float thick, bool fill) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	switch (fill) {
	case true:
		RT->FillRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush);
		break;
	case false:
		RT->DrawRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush, thick);
		break;
	}
	brush->Release();
}

// Устаревший тип
void Graphics::PrintText(LPWSTR text, int lenght, float x, float y, float r, float g, float b, float a) {
	r = r / 255.0f;
	g = g / 255.0f;
	b = b / 255.0f;
	a = a / 255.0f;
	RT->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
	RT->DrawText(text, lenght, textformat, D2D1::RectF(x, y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void Graphics::PrintText(LPCWSTR text, XMFLOAT2 coord, D2D1_COLOR_F color) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawText(text, wcslen(text), textformat, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void Graphics::PrintText(LPCWSTR text, XMFLOAT2 coord, XMFLOAT4 color) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawText(text, wcslen(text), textformat, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void Graphics::PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, XMFLOAT4 color, DWRITE_TEXT_ALIGNMENT align) {
	int input = num;
	D2D_RECT_F baserect;
	if (align != DWRITE_TEXT_ALIGNMENT_CENTER) {
		baserect = D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
	else {
		baserect = D2D1::RectF(coord.x - shift, coord.y - shift, coord.x + shift, coord.y + shift);
	}
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush);
	wfactory->CreateTextFormat(font, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	textformatmanual->SetTextAlignment(align);
	std::wstringstream wss;
	wss << num;
	RT->DrawText(wss.str().c_str(), (ceil(log10(input + 1))), textformatmanual, &baserect, brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT align) {
	int input = num;
	D2D_RECT_F baserect;
	if (align != DWRITE_TEXT_ALIGNMENT_CENTER) {
		baserect = D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
	else {
		baserect = D2D1::RectF(coord.x - shift, coord.y - shift, coord.x + shift, coord.y + shift);
	}
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(color, &brush);
	wfactory->CreateTextFormat(font, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	textformatmanual->SetTextAlignment(align);
	std::wstringstream wss;
	wss << num;
	RT->DrawText(wss.str().c_str(), (ceil(log10(input + 1))), textformatmanual, &baserect, brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, lenght, textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(color, &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, lenght, textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(color, &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, wcslen(text), textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x/255.0f, color.y/255.0f, color.z/255.0f, color.w/255.0f), &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, wcslen(text), textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void Graphics::CreateButton(LPCWSTR name, LPCWSTR text, XMFLOAT2 coord, XMFLOAT2 size, UINT id, HINSTANCE hInst) {
	HWND handleButton = CreateWindow((LPCSTR)name,
		(LPCSTR)text,
		WS_VISIBLE | WS_CHILD,
		coord.x, coord.y, size.x, size.y,
		mainHWND,
		(HMENU)id,
		hInst,
		NULL);
}