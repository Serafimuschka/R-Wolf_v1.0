#include "RWSpriteSystem.h"

RWSpriteSystem::RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx) {
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
	if (FAILED(hr)) {
		wstring str = L"Error handled: can't load image ";
		str += filename;
		MessageBoxW(NULL, str.c_str(), L"R-Wolf 1.2 Fatal error message", MB_ICONERROR | MB_OK);
		exit(-1);
	}

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
	gfx->getRenderTarget()->CreateBitmapFromWicBitmap(
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
RWSpriteSystem::RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx,
	int spriteWidth, int spriteHeight):
	RWSpriteSystem::RWSpriteSystem(filename, gfx)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spritesAcross = (int)bmp->GetSize().width / spriteWidth;
}
RWSpriteSystem::~RWSpriteSystem() {
	if (bmp) bmp->Release();
}
// Функция Draw(FLOAT X, Y): рисует заданное изображение на сцене в заданных координатах
void RWSpriteSystem::draw(XMFLOAT2 coord) {
	gfx->getRenderTarget()->DrawBitmap(
		bmp,
		RectF(coord.x, coord.y,
			coord.x + bmp->GetSize().width, coord.y + bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		RectF(coord.x, coord.y,
			coord.x + bmp->GetSize().width, coord.y + bmp->GetSize().height)
	);
}
// Функция Draw(INT INDEX, X, Y): перегруженный аналог Draw(). Работает с покадровой анимацией
void RWSpriteSystem::draw(int index, XMFLOAT2 coord, double opacity) {
	opacity /= 255.0f;
	D2D_RECT_F src = D2D1::RectF(
			(index % spritesAcross) * spriteWidth,
			(index / spritesAcross) * spriteHeight,
			(index % spritesAcross) * spriteWidth + spriteWidth,
			(index / spritesAcross) * spriteHeight + spriteHeight
	);
	D2D_RECT_F dest = D2D1::RectF(
		coord.x, coord.y, coord.x + spriteWidth, coord.y + spriteHeight);
	gfx->getRenderTarget()->DrawBitmap(
		bmp,
		dest,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src
	);
}

void RWSpriteSystem::texturize(XMFLOAT2 coord, XMFLOAT2 mapsize, double opacity) {
	int indexA = mapsize.x / spriteWidth;
	int indexB = mapsize.y / spriteHeight;

	for (int it = 0; it < indexB; it++) {
		for (int i = 0; i < indexA; i++) {
			draw(0, XMFLOAT2(coord.x + i * spriteWidth, coord.y + it * spriteHeight), opacity);
		}
	}
}

RWSpriteSystem* RWSpriteSystemA::rwss;

void RWSpriteSystemA::draw(LPCWSTR filename, RWGraphics* gfx, XMFLOAT2 coord, double opacity) {
	rwss = new RWSpriteSystem(filename, gfx);
	rwss->draw(0, coord, opacity);
	delete rwss;
}

void RWSpriteSystemA::draw(LPCWSTR filename, RWGraphics* gfx, uint32_t index,
	XMFLOAT2 size, XMFLOAT2 coord, double opacity) {
	rwss = new RWSpriteSystem(filename, gfx, size.x, size.y);
	rwss->draw(index, coord, opacity);
	delete rwss;
}

void RWSpriteSystemA::texturize(LPCWSTR filename, RWGraphics* gfx,
	XMFLOAT4 rectangle, double opacity) {
	rwss = new RWSpriteSystem(filename, gfx);
	rwss->texturize(XMFLOAT2(rectangle.x, rectangle.y),
		XMFLOAT2(rectangle.z, rectangle.w), opacity);
	delete rwss;
}