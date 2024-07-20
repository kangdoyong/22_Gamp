#pragma once
#include "Define.h"

// 비트맵 이미지를 필드로 갖고,
// 비트맵 텍스쳐 제어에 사용할 클래스
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

