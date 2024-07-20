#include "Bitmap.h"

// 파라미터로 받은 경로에 이미지 파일을 읽고
// 메모리에 올려 텍스쳐화시켜 해당 메서드를 호출한
// 비트맵 객체의 필드로 갖는다.
// 이후 해당 텍스쳐를 갖는 비트맵 객체 자기자신을 반환한다.
Bitmap* Bitmap::LoadBmp(const WCHAR* filePath)
{
	// 현재 창에서 사용하고 있는 기본 dc를 가져옴
	hdc = GetDC(g_hWnd);
	// 기본 dc를 토대로 새로운 dc를 하나 생성
	// memDC에는 불러온 텍스쳐를 담아두려고 합니다.
	memDC = CreateCompatibleDC(hdc);

	// 파라미터로 받은 이미지 경로를 통해 파일 불러옴
	bitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// memDC에 불러온 bitmap을 설정하고,
	// memDC가 이전에 들고 있던 bitmap을 oldBitmap에 담아둠
	// -> oldBitmap에 담아둬야, 이후에 불러왔던 bitmap의 적용을 풀 수 있고
	//    적용을 풀어야, 메모리 해제가 가능하니까
	oldBitmap = (HBITMAP)SelectObject(memDC, bitmap);

	// hdc는 dc를 복제 생성하기 위한 용도로 가져왔음..
	// 사용이 끝났으므로 다시 시스템에 반환
	ReleaseDC(g_hWnd, hdc);

	// 위의 과정이 전부 끝났을 때,
	// 해당 메서드를 호출한 비트맵 객체는 memDC 필드에
	// 저희가 부른 텍스쳐를 가지고 있음

	// 그럼 외부에서 해당 텍스쳐를 사용할 수 있게끔
	// 비트맵 객체 자기자신을 반환
	return this;
}

void Bitmap::Release()
{
	// memDC에 oldBitmap(기본 핸들)을 적용 시킴으로써
	// 등록된 bitmap을 해제시킴
	SelectObject(memDC, oldBitmap);
	DeleteObject(bitmap);
	DeleteDC(memDC);
}

Bitmap::Bitmap()
{
}

Bitmap::~Bitmap()
{
	Release();
}
