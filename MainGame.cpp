#include "MainGame.h"
#include "MapTools.h"

void MainGame::Initialize()
{
	hdc = GetDC(g_hWnd);

	mapTools = new MapTools();
	mapTools->Initialize();
}

void MainGame::Update()
{
	mapTools->Update();
}

void MainGame::Render()
{
	mapTools->Render(hdc);
}

void MainGame::Release()
{
	if (mapTools)
	{
		delete mapTools;
		mapTools = nullptr;
	}
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
