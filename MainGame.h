#pragma once
#include "Define.h"

class MapTools;

class MainGame
{
private:
	HDC hdc; // ���� �� ��ü�� �׸� �� ����� hdc
	MapTools* mapTools;

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

	MainGame();
	~MainGame();
};

