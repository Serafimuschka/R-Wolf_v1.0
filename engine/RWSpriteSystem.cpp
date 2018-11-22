#include "RWSpriteSystem.h"

RWSpriteSystem::RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx) {
	// �������������:
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;
	// �������� ������� WIC:
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// �������� ��������:
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	// ������ �����������:
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// �������� ���������:
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// ��������� ���������:
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	// ����������� � ������ ID2D1Bitmap:
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	// ������� ������� WIC:
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame)wicFrame->Release();
	// �������������� �������������� ����������:
	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAcross = 1;
}
RWSpriteSystem::RWSpriteSystem(LPCWSTR filename, RWGraphics* gfx, int spriteWidth, int spriteHeight):
	RWSpriteSystem::RWSpriteSystem(filename, gfx)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spritesAcross = (int)bmp->GetSize().width / spriteWidth;
}
RWSpriteSystem::~RWSpriteSystem() {
	if (bmp) bmp->Release();
}
// ������� Draw(FLOAT X, Y): ������ �������� ����������� �� ����� � �������� �����������
void RWSpriteSystem::Draw(float x, float y) {
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(x, y, x + bmp->GetSize().width, y + bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(x, y, x + bmp->GetSize().width, y + bmp->GetSize().height)
	);
}
// ������� Draw(INT INDEX, X, Y): ������������� ������ Draw(). �������� � ���������� ���������
void RWSpriteSystem::Draw(int index, XMFLOAT2 coord, double opacity) {
	opacity /= 255.0f;
	D2D_RECT_F src = D2D1::RectF(
			(index % spritesAcross) * spriteWidth,
			(index / spritesAcross) * spriteHeight,
			(index % spritesAcross) * spriteWidth + spriteWidth,
			(index / spritesAcross) * spriteHeight + spriteHeight
	);
	D2D_RECT_F dest = D2D1::RectF(
		coord.x, coord.y, coord.x + spriteWidth, coord.y + spriteHeight);
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src
	);
}

void RWSpriteSystem::Texturize(XMFLOAT2 coord, XMFLOAT2 mapsize, double opacity) {
	int indexA = mapsize.x / spriteWidth;
	int indexB = mapsize.y / spriteHeight;

	for (int it = 0; it < indexB; it++) {
		for (int i = 0; i < indexA; i++) {
			Draw(0, XMFLOAT2(coord.x + i * spriteWidth, coord.y + it * spriteHeight), opacity);
		}
	}
}

void RWSpriteAlternative::Draw(LPCWSTR filename, RWGraphics* gfx, XMFLOAT2 coord, double opacity) {
	syst->Draw(0, coord, opacity);
}

void RWSpriteAlternative::Draw(LPCWSTR filename, RWGraphics* gfx, uint32_t index, XMFLOAT2 size, XMFLOAT2 coord, double opacity) {
	syst->Draw(index, coord, opacity);
}

void RWSpriteAlternative::Texturize(LPCWSTR filename, RWGraphics* gfx, XMFLOAT4 rect, double opacity) {
	syst = new RWSpriteSystem(filename, gfx);
	syst->Texturize(XMFLOAT2(rect.x, rect.y), XMFLOAT2(rect.z, rect.w), opacity);
	delete syst;
}