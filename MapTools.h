#pragma once
#include "Object.h"

class Bitmap;

class MapTools :
    public Object
{
private:
	// 배열 - 데이터 크기가 고정적인 경우, 원소 순회속도 빠름
	// 벡터 - 데이터 크기가 유동적이고, 원소의 추가/제거가 빈번하지 않을 경우
	// 리스트 - 데이터 크기가 유동적인 경우, 원소의 추가/제거가 빈번할 경우
	vector<TILE*> tiles;
	vector<Bitmap*> bmps;

	// 현재 선택한 타일 프리셋의 인덱스
	int selectedTile;
	// 인게임 화면 스크롤링에 사용할 x, y
	float scrollX;
	float scrollY;
	// 타일 프리셋 영역 x축 스크롤에 사용할 값
	float presetScrollX;
	// 스크롤 이동 시, 속력
	float scrollSpeed;

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void InitTile(); // 초기 타일 생성 기능
	TILE* CreateTile(float x, float y); // 타일 객체 하나 생성 기능
	void Picking(POINT pt, int drawId); // 맵 내에 특정 타일을 클릭 시, 현재 선택된 프리셋 타일로 설정하는 기능
	void SelectPreset(POINT pt); // 프리셋 영역에서 특정 프리셋 선택 시, 현재 프리셋 인덱스 변경 기능
	void CheckKey(); // 키 입력
	void Scroll(); // 화면 스크롤
	void SaveMap(); // 현재 타일맵 저장 기능
	void LoadMap(); // 타일맵 파일 로드 기능

	MapTools();
	~MapTools();
};

