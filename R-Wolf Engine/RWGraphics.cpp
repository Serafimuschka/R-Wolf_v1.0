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

void RWGraphics::printText(LPCWSTR output, XMFLOAT2 coord, D2D1_COLOR_F color) {
	RT->CreateSolidColorBrush(color, &brush);
	RT->DrawText(output, wcslen(output), textFormat, RectF(coord.x, coord.y,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void RWGraphics::printText(LPCWSTR output, XMFLOAT2 coord, XMFLOAT4 color) {
	RT->CreateSolidColorBrush(
		ColorF(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f), &brush);
	RT->DrawText(output, wcslen(output), textFormat, RectF(coord.x, coord.y,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
}

void RWGraphics::printNum(double output, XMFLOAT2 coord, double shift,
	LPCWSTR font, double size, XMFLOAT4 color, DWRITE_TEXT_ALIGNMENT align) {
	IDWriteTextFormat* textFormatManual;
	D2D_RECT_F baserect;
	wstringstream wss;
	
	wss << output;

	if (align != DWRITE_TEXT_ALIGNMENT_CENTER) {
		baserect = RectF(coord.x, coord.y,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
	else {
		baserect = RectF(coord.x - shift, coord.y - shift,
			coord.x + shift, coord.y + shift);
	}

	RT->CreateSolidColorBrush(ColorF(color.x, color.y, color.z, color.w), &brush);
	wFactory->CreateTextFormat(font, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormatManual);

	textFormatManual->SetTextAlignment(align);
	RT->DrawText(wss.str().c_str(), wcslen(wss.str().c_str()), textFormatManual, &baserect, brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::printNum(double output, XMFLOAT2 coord, double shift,
	LPCWSTR font, double size, D2D1_COLOR_F color, DWRITE_TEXT_ALIGNMENT align) {
	IDWriteTextFormat* textFormatManual;
	D2D_RECT_F baserect;
	wstringstream wss;

	wss << output;

	if (align != DWRITE_TEXT_ALIGNMENT_CENTER) {
		baserect = RectF(coord.x, coord.y,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
	else {
		baserect = RectF(coord.x - shift, coord.y - shift,
			coord.x + shift, coord.y + shift);
	}

	RT->CreateSolidColorBrush(color, &brush);
	wFactory->CreateTextFormat(font, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormatManual);

	textFormatManual->SetTextAlignment(align);
	RT->DrawText(wss.str().c_str(), wcslen(wss.str().c_str()), textFormatManual, &baserect, brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::printTextManual(LPCWSTR output, XMFLOAT2 coord, double size,
	LPCWSTR family, D2D1_COLOR_F color) {
	IDWriteTextFormat* textFormatManual;

	RT->CreateSolidColorBrush(color, &brush);
	wFactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormatManual);
	RT->DrawText(output, wcslen(output), textFormatManual, RectF(coord.x, coord.y,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::printTextManual(LPCWSTR text, XMFLOAT2 coord, double size,
	LPCWSTR family, XMFLOAT4 color) {
	IDWriteTextFormat* textFormatManual;

	RT->CreateSolidColorBrush(
		ColorF(color.x/255.0f, color.y/255.0f, color.z/255.0f, color.w/255.0f), &brush);
	wFactory->CreateTextFormat(family, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormatManual);
	RT->DrawText(text, wcslen(text), textFormatManual, RectF(coord.x, coord.y,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), brush);
	brush->Release();
	textFormatManual->Release();
}

void RWGraphics::progressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval,
	double curval, D2D1_COLOR_F color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;

	D2D1_COLOR_F clr;
	if (curr < 0.3 * size.x) clr = yellowGreen;
	else if (curr >= 0.3 * size.x && curr < 0.7 * size.x) clr = yellow;
	else if (curr >= 0.7 * size.x) clr = red;

	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + size.x, coord.y + size.y), color, 1.0f);
	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + curr, coord.y + size.y), color, 1.0f, true);
	line(XMFLOAT4(coord.x + curr, coord.y - 5,
		coord.x + curr, coord.y + size.y + 5), clr, 2.0f);
	textnum(curval, XMFLOAT2(coord.x + curr, coord.y - 8),
		size.y, RW_Roboto, size.y, clr, DWRITE_TEXT_ALIGNMENT_CENTER);
	textnum(maxval, XMFLOAT2(coord.x + size.x + 5, coord.y),
		size.y, RW_Roboto, size.y, color);
}

void RWGraphics::progressBar(XMFLOAT2 coord, XMFLOAT2 size, double maxval,
	double curval, XMFLOAT4 color) {
	double curr = size.x * (curval / (maxval * 0.01)) / 100;
	if (curr >= size.x) curr = size.x;

	D2D1_COLOR_F clr;
	if (curr < 0.3 * size.x) clr = yellowGreen;
	else if (curr >= 0.3 * size.x && curr < 0.7 * size.x) clr = yellow;
	else if (curr >= 0.7 * size.x) clr = red;

	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + size.x, coord.y + size.y), color, 1.0f);
	rect(XMFLOAT4(coord.x, coord.y,
		coord.x + curr, coord.y + size.y), color, 1.0f, true);
	line(XMFLOAT4(curr, coord.y - 5,
		curr, size.y + 5), clr, 2.0f);
	textnum(curval, XMFLOAT2(coord.x + curr,
		coord.y - 8), size.y, RW_Roboto, size.y, clr, DWRITE_TEXT_ALIGNMENT_CENTER);
	textnum(maxval, XMFLOAT2(coord.x + size.x + 5, coord.y),
		size.y, RW_Roboto, size.y, color);
}

void RWGraphics::drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC,
	D2D1_COLOR_F color, double thick) {
	line(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), color, thick);
	line(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), color, thick);
	line(XMFLOAT4(pointC.x, pointC.y, pointA.x, pointA.y), color, thick);
}

void RWGraphics::drawTriangle(XMFLOAT2 pointA, XMFLOAT2 pointB, XMFLOAT2 pointC,
	XMFLOAT4 color, double thick) {
	line(XMFLOAT4(pointA.x, pointA.y, pointB.x, pointB.y), color, thick);
	line(XMFLOAT4(pointB.x, pointB.y, pointC.x, pointC.y), color, thick);
	line(XMFLOAT4(pointC.x, pointC.y, pointA.x, pointA.y), color, thick);
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

void RWGraphics::drawEntity(Item obj, XMFLOAT2 coord, XMFLOAT2 properties, int type) {
	switch (type) {
	case ENTITY_RECT:
		rect(XMFLOAT4(coord.x, coord.y, 50, 50), black, 1.0f, true);
		break;
	case ENTITY_BULLET:
		rect(XMFLOAT4(coord.x, coord.y - 2.5, coord.x + 15, coord.y + 2.5), orangeRed, 1.0f, true);
	}
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

	textman(L"Используемая/пиковая ОЗУ и FPS:", XMFLOAT2(45, 15), 16.0f,
		RW_Consolas, deepSkyBlue);

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

	textman(L"Информационный блок:", XMFLOAT2(45, 130), 16.0f, RW_Consolas, deepSkyBlue);

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

	textman(text.c_str(), XMFLOAT2(25, 155), 15.0f, RW_Consolas, deepSkyBlue);
}

void RWGraphics::showMenu() {
	line(XMFLOAT4(15, 265, 530, 265), deepSkyBlue, 2.0f);
	line(XMFLOAT4(15, 265, 15, 285), deepSkyBlue, 2.0f);
	line(XMFLOAT4(530, 265, 530, 285), deepSkyBlue, 2.0f);

	textman(L"Панель инструментов:", XMFLOAT2(45, 265), 16.0f, RW_Consolas, deepSkyBlue);
	rect(XMFLOAT4(15, 295, 530, GetSystemMetrics(SM_CYSCREEN) - 15), deepSkyBlue, 2.0f);
}

void RWGraphics::drawInterface(const char* argv) {
	if (argv == "open") {
		rect(XMFLOAT4(545, 15, GetSystemMetrics(SM_CXSCREEN) - 15,
			GetSystemMetrics(SM_CYSCREEN) - 15), deepSkyBlue, 2.0f);
	}

	if (argv == "close") {
		rect(XMFLOAT4(0, 0, 545, GetSystemMetrics(SM_CYSCREEN)),
			XMFLOAT4(15, 15, 15, 255), 1.0f, true);
		rect(XMFLOAT4(545, 0, GetSystemMetrics(SM_CXSCREEN), 15),
			XMFLOAT4(15, 15, 15, 255), 1.0f, true);
		rect(XMFLOAT4(545, GetSystemMetrics(SM_CYSCREEN) - 15,
			GetSystemMetrics(SM_CXSCREEN) - 15, GetSystemMetrics(SM_CYSCREEN)),
			XMFLOAT4(15, 15, 15, 255), 1.0f, true);
		rect(XMFLOAT4(GetSystemMetrics(SM_CXSCREEN) - 15, 0,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)),
			XMFLOAT4(15, 15, 15, 255), 1.0f, true);
		rect(XMFLOAT4(545, 15, GetSystemMetrics(SM_CXSCREEN) - 15,
			GetSystemMetrics(SM_CYSCREEN) - 15), deepSkyBlue, 2.0f);
	}
}

void RWGraphics::drawScalableObject(ScalableObjectProperties config, XMFLOAT2 offsetA,
	XMFLOAT2 offsetB, XMFLOAT2 offsetC, XMFLOAT2 offsetD, D2D1_COLOR_F color) {
	ID2D1GeometrySink* sink;
	factory->CreatePathGeometry(&path);
	path->Open(&sink);

	RT->CreateSolidColorBrush(color, &brush);

	sink->BeginFigure(Point2F(config._11 + offsetA.x, config._12 + offsetA.y),
		config.figureBegin);

	sink->AddLine(Point2F(config._13 - offsetB.x, config._14 + offsetB.y));
	sink->AddLine(Point2F(config._23 - offsetC.x, config._24 - offsetC.y));
	sink->AddLine(Point2F(config._21 + offsetD.x, config._22 - offsetD.y));

	sink->EndFigure(config.figureEnd);

	RT->DrawGeometry(path, brush, 2.0f);

	sink->Close();
	sink->Release();
	brush->Release();
}