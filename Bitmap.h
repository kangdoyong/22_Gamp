#pragma once
#include "Define.h"

// ��Ʈ�� �̹����� �ʵ�� ����,
// ��Ʈ�� �ؽ��� ��� ����� Ŭ����
class Bitmap
{
private:
	HDC hdc, memDC;
	HBITMAP bitmap, oldBitmap;

public:
	HDC GetMemDC() { return memDC; }
	Bitmap* LoadBmp(const WCHAR* filePath);
	void Release();

	Bitmap();
	~Bitmap();
};

