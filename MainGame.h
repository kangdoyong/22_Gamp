#pragma once
#include "Define.h"

class MapTools;

class MainGame
{
private:
	HDC hdc; // 게임 내 객체를 그릴 때 사용할 hdc
	MapTools* mapTools;

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

	MainGame();
	~MainGame();
};

