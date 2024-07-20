#pragma once
#include "framework.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

#define PI 3.141592f

extern HWND g_hWnd;

// Ư�� ��ü�� �׸� ��, ��ġ�� ����� �ʿ�
// �׷� �� ������, ��ġ�� ����� ���õ� ������
// ���� �����ϱ� ���ŷο�Ƿ� ���� ���Ǵ� �����͸� ����üȭ
typedef struct tagInfo
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
}INFO;

// Ÿ�� ������ ��
const int TILE_PRESET_CNT = 24;

// Ÿ�� �ϳ��� ������
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt x * cnt y �� ���� ũ�⸦ ����
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;

const bool TILE_COLLISION_INFO[] =
{
	false, false, false, false, false,
	false, false, false, false, true,
	true, true, false, false, false,
	false, false, false, false, false,
	false, false, false, false
};

// Ÿ�� ��ü �ϳ��� ���� ������ ����
typedef struct tagTile
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	int drawId;
	bool isColl;
}TILE;
