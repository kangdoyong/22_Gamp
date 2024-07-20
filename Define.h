#pragma once
#include "framework.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

#define PI 3.141592f

extern HWND g_hWnd;

// 특정 객체를 그릴 때, 위치와 사이즈가 필요
// 그럼 그 때마다, 위치와 사이즈에 관련된 변수를
// 새로 선언하기 번거로우므로 자주 사용되는 데이터를 구조체화
typedef struct tagInfo
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
}INFO;

// 타일 프리셋 수
const int TILE_PRESET_CNT = 24;

// 타일 하나의 사이즈
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt x * cnt y 로 맵의 크기를 결정
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

// 타일 객체 하나가 갖는 데이터 집합
typedef struct tagTile
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	int drawId;
	bool isColl;
}TILE;
