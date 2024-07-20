#include "MapTools.h"
#include "Bitmap.h"

void MapTools::Initialize()
{
	// �ؽ��� �ε�
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
	// Ÿ�� �� �׸���
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			// ������ Ÿ�� ���ҿ� ���������� �����ϱ� ����
			// Ÿ�� �ε����� ����
			int idx = i * TILE_CNT_X + j;

			BitBlt(bmps[0]->GetMemDC(), // ����ۿ� �׸���
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				bmps[1]->GetMemDC(), // �׸� bmp�� ������ �ִ� ���� dc 
				tiles[idx]->drawId * TILE_SIZE_X, 0, // �̹��� ������ �׸��� ������ x, y ��ġ
				SRCCOPY);
		}
	}

	// Ÿ�� ������ �׸���
	for (int i = 0; i < TILE_PRESET_CNT; ++i)
	{
		BitBlt(bmps[0]->GetMemDC(),
			i * TILE_SIZE_X + presetScrollX, // posX
			WIN_SIZE_Y - TILE_SIZE_Y, // posY
			TILE_SIZE_X, TILE_SIZE_Y, // size
			bmps[1]->GetMemDC(),
			i * TILE_SIZE_X, 0, // �̹��� �� �׸��� ������ ��ġ
			SRCCOPY);
	}

	// ���۹��� �׸����� �ϴ� ���� ��� �׷ȴٸ�
	// ���� ���ȭ�鿡 �� �� �� ���� ��Ų��
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
	// ���콺 ��ǥ �� ��ũ�� ���� ����
	// �ش� ��ġ�� �ִ� Ÿ���� �ε����� ��� ��
	// Ÿ�� �ε����� ���� Ÿ�� ��ü�� �����Ͽ�
	// ���� �����¿� �´� Ÿ�� ������ ����

	// ���� ���콺�� ��ġ�� ��ǥ�� �ִ� Ÿ����
	// x, y�࿡�� ��� °�� ��ġ�ϴ����� ���Ѵ�.
	int x = (pt.x - scrollX) / TILE_SIZE_X;
	int y = (pt.y - scrollY) / TILE_SIZE_Y;

	// Ÿ���� ���� ��, �� ������ ���� Ÿ�� �ε����� ����
	int tileIdx = y * TILE_CNT_X + x;

	tiles[tileIdx]->drawId = drawId;
	tiles[tileIdx]->isColl = TILE_COLLISION_INFO[drawId];
}
void MapTools::SelectPreset(POINT pt)
{
	// ���콺 x ��ǥ�� Ÿ�� ������� ������, ���� Ÿ�� �ε����� ����
	selectedTile = (pt.x - presetScrollX) / TILE_SIZE_X;
}

void MapTools::CheckKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// ���콺 ���� ��ư Ŭ�� ��
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		// ���콺�� ������ ���� �ȿ� �ִٸ�
		if (pt.y >= WIN_SIZE_Y - TILE_SIZE_Y)
		{
			SelectPreset(pt);
		}
		// �ƴ϶��, Ÿ�� ��ġ ������ �ִٴ� ��
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
	// ���̺� �޼��� �˾�
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
	// �ε� �޼��� �˾�
	if (MessageBox(g_hWnd, L"Save?", L"System Message", MB_OKCANCEL) == IDCANCEL)
		return;

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Ÿ�� ������ �ҷ��� ���̹Ƿ�, ���� Ÿ�� ������ ����.
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

		// �� �̻� ���� �����Ͱ� ���� ���
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
