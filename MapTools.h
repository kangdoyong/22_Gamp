#pragma once
#include "Object.h"

class Bitmap;

class MapTools :
    public Object
{
private:
	// �迭 - ������ ũ�Ⱑ �������� ���, ���� ��ȸ�ӵ� ����
	// ���� - ������ ũ�Ⱑ �������̰�, ������ �߰�/���Ű� ������� ���� ���
	// ����Ʈ - ������ ũ�Ⱑ �������� ���, ������ �߰�/���Ű� ����� ���
	vector<TILE*> tiles;
	vector<Bitmap*> bmps;

	// ���� ������ Ÿ�� �������� �ε���
	int selectedTile;
	// �ΰ��� ȭ�� ��ũ�Ѹ��� ����� x, y
	float scrollX;
	float scrollY;
	// Ÿ�� ������ ���� x�� ��ũ�ѿ� ����� ��
	float presetScrollX;
	// ��ũ�� �̵� ��, �ӷ�
	float scrollSpeed;

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void InitTile(); // �ʱ� Ÿ�� ���� ���
	TILE* CreateTile(float x, float y); // Ÿ�� ��ü �ϳ� ���� ���
	void Picking(POINT pt, int drawId); // �� ���� Ư�� Ÿ���� Ŭ�� ��, ���� ���õ� ������ Ÿ�Ϸ� �����ϴ� ���
	void SelectPreset(POINT pt); // ������ �������� Ư�� ������ ���� ��, ���� ������ �ε��� ���� ���
	void CheckKey(); // Ű �Է�
	void Scroll(); // ȭ�� ��ũ��
	void SaveMap(); // ���� Ÿ�ϸ� ���� ���
	void LoadMap(); // Ÿ�ϸ� ���� �ε� ���

	MapTools();
	~MapTools();
};

