#include <DXGI.h>
#include <sstream>
#include <Psapi.h>
#include "RWGraphics.h"

#define _RW_USE_PHYSICS_CONSTANTS
#include "RWPhysicsConstants.h"

RWGraphics::RWGraphics() {
	factory = NULL;
	wfactory = NULL;
	RT = NULL;
	brush = NULL;
}

RWGraphics::~RWGraphics() {
	if (factory) factory->Release();
	if (wfactory) wfactory->Release();
	if (RT) RT->Release();
	if (!brush) brush->Release();
}

bool RWGraphics::Init(HWND windowHandle) {
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

void RWGraphics::CreateConsole(WCHAR* input) {
	std::wstringstream wss;
	LPCWCHAR com;
	wss << input;
	com = wss.str().c_str();
	RT->CreateSolidColorBrush(D2D1::ColorF(30 / 255.0f, 30 / 255.0f, 30 / 255.0f, 100 / 255.0f), &brush);
	RT->FillRectangle(D2D1::RectF(0, GetSystemMetrics(SM_CYSCREEN) - 100, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)-3), brush);
	brush->Release();
	PrintTextManual(com, XMFLOAT2(0, GetSystemMetrics(SM_CYSCREEN) - 100), 12, RW_Consolas, Yellow);
}

void RWGraphics::ClearScreen(XMFLOAT3 color) {
	RT->Clear(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f));
}

void RWGraphics::ClearScreen(D2D1_COLOR_F color) {
	RT->Clear(color);
}

void RWGraphics::DrawLine(XMFLOAT4 coord, D2D1_COLOR_F color, float thick) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawLine(D2D1::Point2F(coord.x, coord.y), D2D1::Point2F(coord.z, coord.w), brush, thick);
	brush->Release();
}

void RWGraphics::DrawLine(XMFLOAT4 coord, XMFLOAT4 color, float thick) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawLine(D2D1::Point2F(coord.x, coord.y), D2D1::Point2F(coord.z, coord.w), brush, thick);
	brush->Release();
}

void RWGraphics::DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, XMFLOAT4 color, float thick, bool fill) {
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

void RWGraphics::DrawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color, float thick, bool fill) {
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

void RWGraphics::DrawRectangle(XMFLOAT4 coord, D2D1_COLOR_F color, float thick, bool fill) {
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

void RWGraphics::DrawRectangle(XMFLOAT4 coord, XMFLOAT4 color, float thick, bool fill) {
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
void RWGraphics::PrintText(LPWSTR text, int lenght, float x, float y, float r, float g, float b, float a) {
	r = r / 255.0f;
	g = g / 255.0f;
	b = b / 255.0f;
	a = a / 255.0f;
	RT->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
	RT->DrawText(text, lenght, textformat, D2D1::RectF(x, y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void RWGraphics::PrintText(LPCWSTR text, XMFLOAT2 coord, D2D1_COLOR_F color) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawText(text, wcslen(text), textformat, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void RWGraphics::PrintText(LPCWSTR text, XMFLOAT2 coord, XMFLOAT4 color) {
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawText(text, wcslen(text), textformat, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void RWGraphics::PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, XMFLOAT4 color, DWRITE_TEXT_ALIGNMENT align) {
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

void RWGraphics::PrintNum(float num, XMFLOAT2 coord, float shift, LPCWSTR font, float size, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT align) {
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

void RWGraphics::PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, lenght, textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void RWGraphics::PrintTextManual(LPCWSTR text, int lenght, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(color, &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, lenght, textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void RWGraphics::PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, D2D1_COLOR_F color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(color, &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, wcslen(text), textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void RWGraphics::PrintTextManual(LPCWSTR text, XMFLOAT2 coord, float size, LPCWSTR family, XMFLOAT4 color) {
	IDWriteTextFormat* textformatmanual;
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x/255.0f, color.y/255.0f, color.z/255.0f, color.w/255.0f), &brush);
	wfactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textformatmanual);
	RT->DrawTextA(text, wcslen(text), textformatmanual, D2D1::RectF(coord.x, coord.y, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textformatmanual->Release();
}

void RWGraphics::CreateButton(LPCWSTR name, LPCWSTR text, XMFLOAT2 coord, XMFLOAT2 size, UINT id, HINSTANCE hInst) {
	HWND handleButton = CreateWindow((LPCSTR)name,
		(LPCSTR)text,
		WS_VISIBLE | WS_CHILD,
		coord.x, coord.y, size.x, size.y,
		mainHWND,
		(HMENU)id,
		hInst,
		NULL);
}

void RWGraphics::ProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval, double curval, D2D1_COLOR_F color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;

	D2D1_COLOR_F clr;
	if (curr < 0.3 * size.x) clr = YellowGreen;
	else if (curr >= 0.3 * size.x && curr < 0.7 * size.x) clr = Yellow;
	else if (curr >= 0.7 * size.x) clr = Red;

	DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + size.x, coord.y + size.y), color, 1);
	DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + curr, coord.y + size.y), color, 1, true);
	DrawLine(XMFLOAT4(coord.x + curr, coord.y - 5, coord.x + curr, coord.y + size.y + 5), clr, 2);
	PrintNum(curval, XMFLOAT2(coord.x + curr, coord.y - 8), size.y, RW_Roboto, size.y, clr, DWRITE_TEXT_ALIGNMENT_CENTER);
	PrintNum(maxval, XMFLOAT2(coord.x + size.x + 5, coord.y), size.y, RW_Roboto, size.y, color);
}

void RWGraphics::ProgressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval, double curval, XMFLOAT4 color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;

	D2D1_COLOR_F clr;
	if (curr < 0.3 * size.x) clr = YellowGreen;
	else if (curr >= 0.3 * size.x && curr < 0.7 * size.x) clr = Yellow;
	else if (curr >= 0.7 * size.x) clr = Red;

	DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + size.x, coord.y + size.y), color, 1);
	DrawRectangle(XMFLOAT4(coord.x, coord.y, coord.x + curr, coord.y + size.y), color, 1, true);
	DrawLine(XMFLOAT4(curr, coord.y - 5, curr, size.y + 5), clr, 2);
	PrintNum(curval, XMFLOAT2(coord.x + curr, coord.y - 8), size.y, RW_Roboto, size.y, clr, DWRITE_TEXT_ALIGNMENT_CENTER);
	PrintNum(maxval, XMFLOAT2(coord.x + size.x + 5, coord.y), size.y, RW_Roboto, size.y, color);
}

void RWGraphics::DrawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC, D2D1_COLOR_F color, float thick) {
	DrawLine(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), color, thick);
	DrawLine(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), color, thick);
	DrawLine(XMFLOAT4(pointC.x, pointC.y, pointA.x, pointA.y), color, thick);
}

void RWGraphics::DrawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC, XMFLOAT4 color, float thick) {
	DrawLine(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), color, thick);
	DrawLine(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), color, thick);
	DrawLine(XMFLOAT4(pointC.x, pointC.y, pointA.x, pointA.y), color, thick);
}

void RWGraphics::DrawArc(XMFLOAT2 center, XMFLOAT2 radius, D2D1_COLOR_F color, float angle, float thick) {
	ID2D1GeometrySink* sink;
	XMFLOAT2 add = XMFLOAT2(0, 0);
	int k = 1;
	RT->CreateSolidColorBrush(color, &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);
	sink->BeginFigure(D2D1::Point2F(center.x - radius.x, center.y), D2D1_FIGURE_BEGIN_FILLED);
	if ((angle > 90) && (angle < 180)) {
		angle -= 90;
	}
	sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(center.x + radius.x * cos((180 - angle) * 3.14159265 / 180), center.y - radius.y * sin((180 - angle) * 3.14159265 / 180)), D2D1::SizeF(radius.x, radius.y), angle, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	RT->DrawLine(D2D1::Point2F(center.x, center.y), D2D1::Point2F(center.x + radius.x * cos((180 - angle) * 3.14159265 / 180), center.y - k * radius.y * sin((180 - angle) * 3.14159265 / 180)), brush, thick);
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	sink->Close();
	RT->DrawGeometry(path, brush, thick);
	if (angle > 180) {
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(center.x - radius.x * cos((angle) * 3.14159265 / 180), center.y + radius.y * sin((angle) * 3.14159265 / 180)), D2D1::SizeF(radius.x, radius.y), angle, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	}
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::DrawArc(XMFLOAT2 center, XMFLOAT2 radius, XMFLOAT4 color, float angle, float thick) {
	ID2D1GeometrySink* sink;
	XMFLOAT2 arg;
	int k = 1;
	arg.x = angle * (PI / 180);
	arg.y = arg.x;
	if (angle > 90) {
		arg.y -= 90;
		k *= -1;
	}
	RT->CreateSolidColorBrush(D2D1::ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);
	sink->BeginFigure(D2D1::Point2F(center.x - radius.x, center.y), D2D1_FIGURE_BEGIN_FILLED);
	sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(center.x - cosf(arg.x)*radius.x, center.y - k * sinf(arg.y)*radius.y), D2D1::SizeF(radius.x, radius.y), 0, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	sink->Close();
	RT->DrawGeometry(path, brush, thick);
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::logic_DrawEntity(item entity, XMFLOAT2 coord, XMFLOAT2 properties, int type) {
	switch (type) {
	case ENTITY_RECT:
		rect(XMFLOAT4(coord.x, coord.y, 50, 50), Black, 1, true);
		break;
	case ENTITY_BULLET:
		rect(XMFLOAT4(coord.x, coord.y - 2.5, coord.x + 15, coord.y + 2.5), OrangeRed, 1, true);
	}
}

VOID RWGraphics::DEBUG_ShowInfo(const char* argv) {
	MEMORYSTATUSEX msex;
	double oldTime, newTime, delta, elapsed = 0, frame = 0, fps;
	msex.dwLength = sizeof(msex);
	GlobalMemoryStatusEx(&msex);
	unsigned long long int memoryAll = msex.ullAvailPhys / 1024 / 1024;
	PROCESS_MEMORY_COUNTERS memCounter;
	GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(PROCESS_MEMORY_COUNTERS));
	UINT mem = memCounter.WorkingSetSize / 1024 / 1024;
	UINT memp = memCounter.PeakWorkingSetSize / 1024 / 1024;

	DrawLine(XMFLOAT4(15, 35, 35, 15), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(35, 15, 530, 15), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(530, 15, 530, 35), DeepSkyBlue, 2);
	DrawRectangle(XMFLOAT4(15, 35, 530, 100), DeepSkyBlue, 2);

	PrintTextManual(L"Используемая/пиковая ОЗУ и FPS:", XMFLOAT2(45, 15), 16, RW_Consolas, DeepSkyBlue);

	if (argv == "begin") oldTime = GetTickCount();
	if (argv == "end") newTime = GetTickCount();
	delta = newTime - oldTime;
	fps = 1000 / delta;
	ProgressBar(XMFLOAT2(35, 65), XMFLOAT2(200, 20), memp, mem, DeepSkyBlue);
	ProgressBar(XMFLOAT2(285, 65), XMFLOAT2(200, 20), 90, fps, DeepSkyBlue);
}

VOID RWGraphics::DEBUG_ShowHardware(double timerIn, std::wstring b_name, std::wstring b_num) {

	int hour = timerIn / 3600,
		min = timerIn / 60,
		sec = timerIn;

	DrawLine(XMFLOAT4(15, 150, 35, 130), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(35, 130, 530, 130), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(530, 130, 530, 150), DeepSkyBlue, 2);
	DrawRectangle(XMFLOAT4(15, 150, 530, 235), DeepSkyBlue, 2);

	PrintTextManual(L"Информационный блок:", XMFLOAT2(45, 130), 16, RW_Consolas, DeepSkyBlue);

	std::wstring text;
	IDXGIFactory1* pFactory;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
	IDXGIAdapter1* Adapter;
	pFactory->EnumAdapters1(0, &Adapter);
	DXGI_ADAPTER_DESC1 Desc;
	Adapter->GetDesc1(&Desc);
	std::wstringstream wss;
	wss << Desc.Description;
	std::wstring AdapterName = wss.str().c_str();
	wss.str(L"");
	Adapter->Release();
	pFactory->Release();

	text = L"Видеоадаптер ";
	text += AdapterName;
	text += L"\nВремя работы: ";
	wss << hour;
	text += wss.str().c_str();
	text += L" часов, ";
	wss.str(L"");
	wss << min - 60 * hour;
	text += wss.str().c_str();
	text += L" минут, ";
	wss.str(L"");
	wss << sec - 60 * min;
	text += wss.str().c_str();
	text += L" секунд\n";
	wss.str(L"");
	text += L"Сборка R-Wolf: ";
	text += b_name;
	text += L", билд ";
	text += b_num;
	text += L"\nДата сборки/компиляции RWGraphics: ";
	wss << __TIMESTAMP__;
	text += wss.str().c_str();
	wss.str(L"");

	PrintTextManual(text.c_str(), XMFLOAT2(25, 155), 15, RW_Consolas, DeepSkyBlue);
}

VOID RWGraphics::DEBUG_ShowMenu() {
	DrawLine(XMFLOAT4(15, 265, 530, 265), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(15, 265, 15, 285), DeepSkyBlue, 2);
	DrawLine(XMFLOAT4(530, 265, 530, 285), DeepSkyBlue, 2);

	PrintTextManual(L"Панель инструментов:", XMFLOAT2(45, 265), 16, RW_Consolas, DeepSkyBlue);

	DrawRectangle(XMFLOAT4(15, 295, 530, GetSystemMetrics(SM_CYSCREEN) - 15), DeepSkyBlue, 2);
}

VOID RWGraphics::RW_DrawInterface(const char* argv) {
	if (argv == "open") {
		DrawRectangle(XMFLOAT4(545, 15, GetSystemMetrics(SM_CXSCREEN) - 15, GetSystemMetrics(SM_CYSCREEN) - 15), DeepSkyBlue, 2);
	}

	if (argv == "close") {
		DrawRectangle(XMFLOAT4(0, 0, 545, GetSystemMetrics(SM_CYSCREEN)), XMFLOAT4(15, 15, 15, 255), 1, true);
		DrawRectangle(XMFLOAT4(545, 0, GetSystemMetrics(SM_CXSCREEN), 15), XMFLOAT4(15, 15, 15, 255), 1, true);
		DrawRectangle(XMFLOAT4(545, GetSystemMetrics(SM_CYSCREEN) - 15, GetSystemMetrics(SM_CXSCREEN) - 15, GetSystemMetrics(SM_CYSCREEN)), XMFLOAT4(15, 15, 15, 255), 1, true);
		DrawRectangle(XMFLOAT4(GetSystemMetrics(SM_CXSCREEN) - 15, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), XMFLOAT4(15, 15, 15, 255), 1, true);
		DrawRectangle(XMFLOAT4(545, 15, GetSystemMetrics(SM_CXSCREEN) - 15, GetSystemMetrics(SM_CYSCREEN) - 15), DeepSkyBlue, 2);
	}
}