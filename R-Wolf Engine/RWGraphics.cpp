//
//
//
//
//
//	kalterseele, 2018
//

#include "RWGraphics.h"

RWGraphics::RWGraphics() {
	factory = NULL;
	wFactory = NULL;
	RT = NULL;
	brush = NULL;
}

RWGraphics::~RWGraphics() {
	if (factory) factory->Release();
	if (wFactory) wFactory->Release();
	if (RT) RT->Release();
	if (!brush) brush->Release();
}

bool RWGraphics::init(HWND windowHandle) {
	window = windowHandle;
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
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(wFactory),
		reinterpret_cast<IUnknown**>(&wFactory));
	if (!SUCCEEDED(hr)) return false;
	static const WCHAR fontName[] = L"Consolas";
	hr = wFactory->CreateTextFormat(fontName, NULL,
		DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"", &textFormat);
	if (!SUCCEEDED(hr)) return false;
	return true;
}


void RWGraphics::clearScreen(XMFLOAT3 color) {
	RT->Clear(ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f));
}

void RWGraphics::clearScreen(D2D1_COLOR_F color) {
	RT->Clear(color);
}

void RWGraphics::drawLine(XMFLOAT4 coord, D2D1_COLOR_F color, double thick) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawLine(Point2F(coord.x, coord.y), Point2F(coord.z, coord.w), brush, thick);
	brush->Release();
}

void RWGraphics::drawLine(XMFLOAT4 coord, XMFLOAT4 color, double thick) {
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawLine(Point2F(coord.x, coord.y), Point2F(coord.z, coord.w), brush, thick);
	brush->Release();
}

void RWGraphics::drawCircle(XMFLOAT2 coord, XMFLOAT2 radius, XMFLOAT4 color,
	double thick, bool fill) {
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	if (fill) {
		RT->FillEllipse(Ellipse(Point2F(coord.x, coord.y), radius.x, radius.y), brush);
	}
	else {
		RT->DrawEllipse(Ellipse(Point2F(coord.x, coord.y), radius.x, radius.y), brush, thick);
	}
	brush->Release();
}

void RWGraphics::drawCircle(XMFLOAT2 coord, XMFLOAT2 radius, D2D1_COLOR_F color,
	double thick, bool fill) {
	RT->CreateSolidColorBrush(color, &brush);
	if (fill) {
		RT->FillEllipse(Ellipse(Point2F(coord.x, coord.y), radius.x, radius.y), brush);
	}
	else {
		RT->DrawEllipse(Ellipse(Point2F(coord.x, coord.y), radius.x, radius.y), brush, thick);
	}
	brush->Release();
}

void RWGraphics::drawRectangle(XMFLOAT4 coord, D2D1_COLOR_F color, double thick, bool fill) {
	RT->CreateSolidColorBrush(color, &brush);
	if (fill) {
		RT->FillRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush);
	}
	else {
		RT->DrawRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush, thick);
	}
	brush->Release();
}

void RWGraphics::drawRectangle(XMFLOAT4 coord, XMFLOAT4 color, double thick, bool fill) {
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	if (fill) {
		RT->FillRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush);
	}
	else {
		RT->DrawRectangle(D2D1::RectF(coord.x, coord.y, coord.z, coord.w), brush, thick);
	}
	brush->Release();
}

void RWGraphics::printText(LPCWSTR output, XMFLOAT2 coord, D2D1_COLOR_F color, double size,
	LPCWSTR font, DWRITE_TEXT_ALIGNMENT align,
	DWRITE_FONT_WEIGHT fw,
	DWRITE_FONT_STYLE fs,
	DWRITE_FONT_STRETCH fst) {
	IDWriteTextFormat* textFormatManual;
	RT->CreateSolidColorBrush(color, &brush);
	wFactory->CreateTextFormat(font, NULL, fw, fs,
		fst, size, L"", &textFormatManual);
	textFormatManual->SetTextAlignment(align);
	RT->DrawText(output, wcslen(output), textFormatManual, RectF(coord.x, coord.y,
		coord.x + (size * wcslen(output)) + 1, coord.y + 100 * size), brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::printText(LPCWSTR output, XMFLOAT2 coord, XMFLOAT4 color, double size,
	LPCWSTR font, DWRITE_TEXT_ALIGNMENT align,
	DWRITE_FONT_WEIGHT fw,
	DWRITE_FONT_STYLE fs,
	DWRITE_FONT_STRETCH fst) {
	IDWriteTextFormat* textFormatManual;
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	wFactory->CreateTextFormat(font, NULL, fw, fs, fst, size, L"", &textFormatManual);
	textFormatManual->SetTextAlignment(align);
	RT->DrawText(output, wcslen(output), textFormatManual, RectF(coord.x, coord.y,
		coord.x + (size * wcslen(output)) + 1, coord.y + size), brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::progressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval,
	double curval, D2D1_COLOR_F color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;

	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + size.x, coord.y + size.y), color, 1.0f);
	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + curr, coord.y + size.y), color, 1.0f, true);
}

void RWGraphics::progressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval,
	double curval, XMFLOAT4 color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;
	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + size.x, coord.y + size.y), color, 1.0f);
	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + curr, coord.y + size.y), color, 1.0f, true);
}

void RWGraphics::loadBar(UINT sw, UINT sh, int timeoutCurrent, int timeoutMax) {
	double length = 400.0;
	double start = sw * 0.5 - 200.0;
	double current = length * (timeoutCurrent / (timeoutMax * 0.01)) / 100;
	RT->CreateSolidColorBrush(lightSeaGreen, &brush);
	RT->DrawRoundedRectangle(RoundedRect(
		RectF(start, sh * 0.5f + 272, start + length, sh * 0.5f + 275),
		2.0f, 2.0f), brush);
	RT->FillRoundedRectangle(RoundedRect(
		RectF(start, sh * 0.5f + 272, start + current, sh * 0.5f + 275),
		2.0f, 2.0f), brush);
	brush->Release();
}

void RWGraphics::drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC,
	D2D1_COLOR_F color, double thick, bool fill) {
	ID2D1GeometrySink* sink;
	D2D1_FIGURE_BEGIN type;
	RT->CreateSolidColorBrush(color, &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);

	switch (fill) {
	case true:
		type = D2D1_FIGURE_BEGIN_FILLED;
		break;
	case false:
		type = D2D1_FIGURE_BEGIN_HOLLOW;
		break;
	}

	sink->BeginFigure(Point2F(pointA.x, pointA.y), type);
	sink->AddLine(Point2F(pointB.x, pointB.y));
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);

	RT->DrawGeometry(path, brush, thick);
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC,
	XMFLOAT4 color, double thick, bool fill) {
	ID2D1GeometrySink* sink;
	D2D1_FIGURE_BEGIN type;
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);

	switch (fill) {
	case true:
		type = D2D1_FIGURE_BEGIN_FILLED;
		break;
	case false:
		type = D2D1_FIGURE_BEGIN_HOLLOW;
		break;
	}

	sink->BeginFigure(Point2F(pointA.x, pointA.y), type);
	sink->AddLine(Point2F(pointB.x, pointB.y));
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);

	RT->DrawGeometry(path, brush, thick);
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::drawArc(XMFLOAT2 center, XMFLOAT2 radius, D2D1_COLOR_F color,
	double angle, double thick) {
	ID2D1GeometrySink* sink;
	XMFLOAT2 add = XMFLOAT2(0, 0);
	int k = 1;

	RT->CreateSolidColorBrush(color, &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);
	sink->BeginFigure(Point2F(center.x - radius.x, center.y), D2D1_FIGURE_BEGIN_FILLED);

	if ((angle > 90) && (angle < 180)) {
		angle -= 90;
	}

	sink->AddArc(ArcSegment(Point2F(
		center.x + radius.x * cos((180 - angle) * PI / 180),
		center.y - radius.y * sin((180 - angle) * PI / 180)),
		SizeF(radius.x, radius.y), angle,
		D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	RT->DrawLine(Point2F(center.x, center.y),
		Point2F(center.x + radius.x * cos((180 - angle) * PI / 180),
			center.y - k * radius.y * sin((180 - angle) * PI / 180)), brush, thick);
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	sink->Close();

	if (angle > 180) {
		sink->AddArc(ArcSegment(
			Point2F(center.x - radius.x * cos((angle) * PI / 180),
				center.y + radius.y * sin((angle) * PI / 180)),
			SizeF(radius.x, radius.y), angle,
			D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	}

	RT->DrawGeometry(path, brush, thick);
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::drawArc(XMFLOAT2 center, XMFLOAT2 radius, XMFLOAT4 color,
	double angle, double thick) {
	ID2D1GeometrySink* sink;
	XMFLOAT2 arg;
	int k = 1;
	arg.x = angle * (PI / 180);
	arg.y = arg.x;

	if (angle > 90) {
		arg.y -= 90;
		k *= -1;
	}

	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	factory->CreatePathGeometry(&path);
	path->Open(&sink);
	sink->BeginFigure(Point2F(center.x - radius.x, center.y), D2D1_FIGURE_BEGIN_FILLED);
	sink->AddArc(ArcSegment(
		Point2F(center.x - cosf(arg.x) * radius.x, center.y - k * sinf(arg.y) * radius.y),
		SizeF(radius.x, radius.y), 0, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	sink->Close();

	RT->DrawGeometry(path, brush, thick);
	brush->Release();
	sink->Release();
	path->Release();
}

void RWGraphics::showInfo(const char* argv) {
	MEMORYSTATUSEX msex;
	PROCESS_MEMORY_COUNTERS memCounter;
	msex.dwLength = sizeof(msex);

	GlobalMemoryStatusEx(&msex);
	unsigned long long int memoryAll = msex.ullAvailPhys / pow(1024, 2);

	GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(PROCESS_MEMORY_COUNTERS));

	line(XMFLOAT4(15, 35, 35, 15), deepSkyBlue, 2.0f);
	line(XMFLOAT4(35, 15, 530, 15), deepSkyBlue, 2.0f);
	line(XMFLOAT4(530, 15, 530, 35), deepSkyBlue, 2.0f);
	rect(XMFLOAT4(15, 35, 530, 100), deepSkyBlue, 2.0f);

	bar(XMFLOAT2(35, 65), XMFLOAT2(200, 20),
		memCounter.PeakWorkingSetSize / pow(1024, 2),
		memCounter.WorkingSetSize / pow(1024, 2), deepSkyBlue);
	bar(XMFLOAT2(285, 65), XMFLOAT2(200, 20), 90, 60, deepSkyBlue);
}

void RWGraphics::showHardware(double timerIn, std::wstring b_name, std::wstring b_num) {
	wstring text;
	IDXGIFactory1* pFactory;
	IDXGIAdapter1* Adapter;
	DXGI_ADAPTER_DESC1 Desc;
	wstringstream wss;
	int hour = timerIn / 3600,
		min = timerIn / 60,
		sec = timerIn;

	line(XMFLOAT4(15, 150, 35, 130), deepSkyBlue, 2.0f);
	line(XMFLOAT4(35, 130, 530, 130), deepSkyBlue, 2.0f);
	line(XMFLOAT4(530, 130, 530, 150), deepSkyBlue, 2.0f);
	rect(XMFLOAT4(15, 150, 530, 235), deepSkyBlue, 2.0f);

	

	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
	pFactory->EnumAdapters1(0, &Adapter);
	Adapter->GetDesc1(&Desc);
	wss << Desc.Description;
	wstring AdapterName = wss.str().c_str();
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
}

void RWGraphics::showMenu() {
	line(XMFLOAT4(15, 265, 530, 265), deepSkyBlue, 2.0f);
	line(XMFLOAT4(15, 265, 15, 285), deepSkyBlue, 2.0f);
	line(XMFLOAT4(530, 265, 530, 285), deepSkyBlue, 2.0f);
	rect(XMFLOAT4(15, 295, 530, GetSystemMetrics(SM_CYSCREEN) - 15), deepSkyBlue, 2.0f);
}

bool exist(XMFLOAT2 point, XMFLOAT4 rectangle) {
	bool result = false;
	if (point.x >= rectangle.x && point.x <= rectangle.z &&
		point.y >= rectangle.y && point.y <= rectangle.w) result = true;
	return result;
}