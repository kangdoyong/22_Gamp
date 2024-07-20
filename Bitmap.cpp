#include "Bitmap.h"

// �Ķ���ͷ� ���� ��ο� �̹��� ������ �а�
// �޸𸮿� �÷� �ؽ���ȭ���� �ش� �޼��带 ȣ����
// ��Ʈ�� ��ü�� �ʵ�� ���´�.
// ���� �ش� �ؽ��ĸ� ���� ��Ʈ�� ��ü �ڱ��ڽ��� ��ȯ�Ѵ�.
Bitmap* Bitmap::LoadBmp(const WCHAR* filePath)
{
	// ���� â���� ����ϰ� �ִ� �⺻ dc�� ������
	hdc = GetDC(g_hWnd);
	// �⺻ dc�� ���� ���ο� dc�� �ϳ� ����
	// memDC���� �ҷ��� �ؽ��ĸ� ��Ƶη��� �մϴ�.
	memDC = CreateCompatibleDC(hdc);

	// �Ķ���ͷ� ���� �̹��� ��θ� ���� ���� �ҷ���
	bitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// memDC�� �ҷ��� bitmap�� �����ϰ�,
	// memDC�� ������ ��� �ִ� bitmap�� oldBitmap�� ��Ƶ�
	// -> oldBitmap�� ��Ƶ־�, ���Ŀ� �ҷ��Դ� bitmap�� ������ Ǯ �� �ְ�
	//    ������ Ǯ���, �޸� ������ �����ϴϱ�
	oldBitmap = (HBITMAP)SelectObject(memDC, bitmap);

	// hdc�� dc�� ���� �����ϱ� ���� �뵵�� ��������..
	// ����� �������Ƿ� �ٽ� �ý��ۿ� ��ȯ
	ReleaseDC(g_hWnd, hdc);

	// ���� ������ ���� ������ ��,
	// �ش� �޼��带 ȣ���� ��Ʈ�� ��ü�� memDC �ʵ忡
	// ���� �θ� �ؽ��ĸ� ������ ����

	// �׷� �ܺο��� �ش� �ؽ��ĸ� ����� �� �ְԲ�
	// ��Ʈ�� ��ü �ڱ��ڽ��� ��ȯ
	return this;
}

void Bitmap::Release()
{
	// memDC�� oldBitmap(�⺻ �ڵ�)�� ���� ��Ŵ���ν�
	// ��ϵ� bitmap�� ������Ŵ
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
