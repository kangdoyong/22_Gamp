#include "MapTools.h"
#include "Bitmap.h"

void MapTools::Initialize()
{
	// 텍스쳐 로딩
	bmps.push_back((new Bitmap())->LoadBmp(L"BackBuffer.bmp"));
	bmps.push_back((new Bitmap())->LoadBmp(L"Tile.bmp"));

	selectedTile = 0;
	InitTile();

	scrollSpeed = 5.f;
	presetScrollX = 0;
	scrollX = 0;
	scrollY = 0;
}

void MapTools::Update()
{
	CheckKey();
	Scroll();
}

void MapTools::Render(HDC hdc)
{
	// 타일 맵 그리기
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			// 각각의 타일 원소에 순차적으로 접근하기 위해
			// 타일 인덱스를 연산
			int idx = i * TILE_CNT_X + j;

			BitBlt(bmps[0]->GetMemDC(), // 백버퍼에 그리게
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				bmps[1]->GetMemDC(), // 그릴 bmp를 가지고 있는 원본 dc 
				tiles[idx]->drawId * TILE_SIZE_X, 0, // 이미지 내에서 그리기 시작할 x, y 위치
				SRCCOPY);
		}
	}

	// 타일 프리셋 그리기
	for (int i = 0; i < TILE_PRESET_CNT; ++i)
	{
		BitBlt(bmps[0]->GetMemDC(),
			i * TILE_SIZE_X + presetScrollX, // posX
			WIN_SIZE_Y - TILE_SIZE_Y, // posY
			TILE_SIZE_X, TILE_SIZE_Y, // size
			bmps[1]->GetMemDC(),
			i * TILE_SIZE_X, 0, // 이미지 내 그리기 시작할 위치
			SRCCOPY);
	}

	// 백퍼버에 그리고자 하는 것을 모두 그렸다면
	// 실제 출력화면에 딱 한 번 적용 시킨다
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmps[0]->GetMemDC(), 0, 0, SRCCOPY);
}

void MapTools::Release()
{
	for (int i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i])
		{
			delete tiles[i];
			tiles[i] = nullptr;
		}
	}
	tiles.clear();

	for (int i = 0; i < bmps.size(); ++i)
	{
		if (bmps[i])
		{
			delete bmps[i];
			bmps[i] = nullptr;
		}
	}
	bmps.clear();
}

void MapTools::InitTile()
{
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			float x = (j * TILE_SIZE_X) + TILE_SIZE_X / 2;
			float y = (i * TILE_SIZE_Y) + TILE_SIZE_Y / 2;

			tiles.push_back(CreateTile(x, y));
		}
	}
}

TILE* MapTools::CreateTile(float x, float y)
{
	TILE* tile = new TILE();

	tile->posX = x;
	tile->posY = y;
	tile->sizeX = TILE_SIZE_X;
	tile->sizeY = TILE_SIZE_Y;
	tile->drawId = 0;
	tile->isColl = false;

	return tile;
}

void MapTools::Picking(POINT pt, int drawId)
{
	// 마우스 좌표 및 스크롤 값을 통해
	// 해당 위치에 있는 타일의 인덱스를 계산 후
	// 타일 인덱스를 통해 타일 객체에 접근하여
	// 현재 프리셋에 맞는 타일 정보로 수정

	// 현재 마우스가 위치한 좌표에 있는 타일이
	// x, y축에서 몇번 째에 위치하는지를 구한다.
	int x = (pt.x - scrollX) / TILE_SIZE_X;
	int y = (pt.y - scrollY) / TILE_SIZE_Y;

	// 타일의 현재 행, 열 정보를 통해 타일 인덱스를 구함
	int tileIdx = y * TILE_CNT_X + x;

	tiles[tileIdx]->drawId = drawId;
	tiles[tileIdx]->isColl = TILE_COLLISION_INFO[drawId];
}
void MapTools::SelectPreset(POINT pt)
{
	// 마우스 x 좌표를 타일 사이즈로 나누어, 현재 타일 인덱스를 구함
	selectedTile = (pt.x - presetScrollX) / TILE_SIZE_X;
}

void MapTools::CheckKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// 마우스 왼쪽 버튼 클릭 시
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		// 마우스가 프리셋 영역 안에 있다면
		if (pt.y >= WIN_SIZE_Y - TILE_SIZE_Y)
		{
			SelectPreset(pt);
		}
		// 아니라면, 타일 배치 영역에 있다는 뜻
		else
		{
			Picking(pt, selectedTile);
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
		scrollX += scrollSpeed;

	if (GetAsyncKeyState(VK_RIGHT))
		scrollX -= scrollSpeed;

	if (GetAsyncKeyState(VK_UP))
		scrollY += scrollSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		scrollY -= scrollSpeed;

	if (GetAsyncKeyState('A'))
	{
		presetScrollX += scrollSpeed;
	}

	if (GetAsyncKeyState('D'))
	{
		presetScrollX -= scrollSpeed;
	}

	if (GetAsyncKeyState('S'))
		SaveMap();

	if (GetAsyncKeyState('L'))
		LoadMap();


}

void MapTools::Scroll()
{
	if (scrollX > 0)
		scrollX = 0;

	if (scrollX < WIN_SIZE_X - (TILE_CNT_X * TILE_SIZE_X))
		scrollX = WIN_SIZE_X - (TILE_CNT_X * TILE_SIZE_X);

	if (scrollY > 0)
		scrollY = 0;

	if (scrollY < WIN_SIZE_Y - (TILE_CNT_Y * TILE_SIZE_Y))
		scrollY = WIN_SIZE_Y - (TILE_CNT_Y * TILE_SIZE_Y);

	if (presetScrollX > 0)
		presetScrollX = 0;

	if (presetScrollX < WIN_SIZE_X - (TILE_PRESET_CNT * TILE_SIZE_X))
		presetScrollX = WIN_SIZE_X - (TILE_PRESET_CNT * TILE_SIZE_X);
}

void MapTools::SaveMap()
{
	// 세이브 메세지 팝업
	if (MessageBox(g_hWnd, L"Save?", L"System Message", MB_OKCANCEL) == IDCANCEL)
		return;

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	for (int i = 0; i < tiles.size(); ++i)
	{
		WriteFile(handle, tiles[i], sizeof(TILE), &byte, NULL);
	}

	CloseHandle(handle);
}

void MapTools::LoadMap()
{
	// 로드 메세지 팝업
	if (MessageBox(g_hWnd, L"Save?", L"System Message", MB_OKCANCEL) == IDCANCEL)
		return;

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 타일 정보를 불러올 것이므로, 기존 타일 정보를 비운다.
	for (int i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i])
		{
			delete tiles[i];
			tiles[i] = nullptr;
		}
	}
	tiles.clear();

	while (true)
	{
		TILE* tile = new TILE();

		ReadFile(handle, tile, sizeof(TILE), &byte, NULL);

		// 더 이상 읽을 데이터가 없을 경우
		if (byte == 0)
		{
			delete tile;
			break;
		}

		tiles.push_back(tile);
	}

	CloseHandle(handle);


}

MapTools::MapTools()
{
}

MapTools::~MapTools()
{
	Release();
}
