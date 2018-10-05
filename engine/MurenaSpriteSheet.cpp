#include "MurenaSpriteSheet.h"

//--------------------------------------------------
//	�����:			MurenaSpriteSheet
//	��������:		MurenaSpriteSheet
//	��������� ������ �������������� ����������� �
//	���������� ��������
//	����� ������:	Einhorn32 [������� �����]
//					2018, Einhorn32(c)
//--------------------------------------------------
MurenaSpriteSheet::MurenaSpriteSheet(LPCWSTR filename, Graphics* gfx) {
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
// ������� Draw(FLOAT X, Y): ������ �������� ����������� �� ����� � �������� �����������
void MurenaSpriteSheet::Draw(float x, float y) {
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(x, y, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(x, y, bmp->GetSize().width, bmp->GetSize().height));
}
// ������� Draw(INT INDEX, X, Y): ������������� ������ Draw(). �������� � ���������� ���������
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