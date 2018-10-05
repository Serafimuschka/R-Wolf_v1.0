#include "MurenaSpriteSheet.h"

//--------------------------------------------------
//	Класс:			MurenaSpriteSheet
//	Исходник:		MurenaSpriteSheet
//	Реализует модуль преобразования изображений и
//	покадровой анимации
//	Автор модуля:	Einhorn32 [Арсений Бечин]
//					2018, Einhorn32(c)
//--------------------------------------------------
MurenaSpriteSheet::MurenaSpriteSheet(LPCWSTR filename, Graphics* gfx) {
	// Инициализация:
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;
	// Создание фабрики WIC:
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// Создание декодера:
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	// Чтение изображения:
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// Создание конвертёра:
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Настройка конвертёра:
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	// Конвертация в формат ID2D1Bitmap:
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	// Убираем объекты WIC:
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame)wicFrame->Release();
	// Инициализируем дополнительные переменные:
	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAcross = 1;
}
MurenaSpriteSheet::MurenaSpriteSheet(LPCWSTR filename, Graphics* gfx, int spriteWidth, int spriteHeight):
	MurenaSpriteSheet::MurenaSpriteSheet(filename, gfx)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spritesAcross = (int)bmp->GetSize().width / spriteWidth;
}
MurenaSpriteSheet::~MurenaSpriteSheet() {
	if (bmp) bmp->Release();
}
// Функция Draw(FLOAT X, Y): рисует заданное изображение на сцене в заданных координатах
void MurenaSpriteSheet::Draw(float x, float y) {
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(x, y, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(x, y, bmp->GetSize().width, bmp->GetSize().height));
}
// Функция Draw(INT INDEX, X, Y): перегруженный аналог Draw(). Работает с покадровой анимацией
void MurenaSpriteSheet::Draw(int index, int x, int y, int deg) {
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spritesAcross)*spriteWidth),
		(float)((index % spritesAcross)*spriteHeight),
		(float)((index % spritesAcross)*spriteWidth) + spriteWidth,
		(float)((index % spritesAcross)*spriteHeight) + spriteHeight);
	D2D_RECT_F dest = D2D1::RectF(
		x, y, x + spriteWidth, y + spriteHeight);
	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(deg, D2D1::Point2F(x / 2, y / 2)));
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		src);
}