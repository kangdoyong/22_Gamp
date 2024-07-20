#pragma once
#include "Object.h"

class MathUtil
{
public:
	// 파라미터로 받은 두 객체 사이의 거리를 구한 후,
	// 반환하는 정적 메서드
	static float GetDistance(Object* a, Object* b)
	{
		int distanceX = a->GetInfo().posX - b->GetInfo().posX;
		int distanceY = a->GetInfo().posY - b->GetInfo().posY;

		float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		return distance;
	}

	// 파라미터로 받은 두 객체 사이의 각도를 구한 후, 반환하는 정적 메서드
	static float GetAngle(Object* a, Object* b)
	{
		int distanceX = a->GetInfo().posX - b->GetInfo().posX;
		int distanceY = a->GetInfo().posY - b->GetInfo().posY;

		float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		// 아크코사인 (밑변 / 빗변) -> 끼인 각 세타를 구함
		float angle = acosf(distanceX / distance) * 180.f / PI;

		// 아크 코사인 통해 구한 각도가 180도의 범위까지 밖에 표현이 안됨
		if (a->GetInfo().posY > b->GetInfo().posY)
		{
			angle = 360.f - angle;
		}

		return angle;
	}

	// 파라미터로 받은 두 객체의 충돌을 감지하는 기능
	static bool OnCollision(Object* a, Object* b)
	{
		// 충돌 체크하고자 하는 두 원의 반지름을 더 함
		// -> 두 원 사이의 직선 거리가 두 원의 반지름의 합보다
		// 작다면 충돌했다고 처리
		// 충돌했으면 true, 아니라면 false 반환

		// 충돌을 감지하고자 하는 두 객체 사이의 거리를 구한다
		// x축 거리
		int distanceX = a->GetInfo().posX - b->GetInfo().posX;
		// y축 거리
		int distanceY = a->GetInfo().posY - b->GetInfo().posY;

		// 구한 x, y축의 거리를 하나의 데이터로 표현 (직선거리를 구함)
		float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		// 두 원의 반지름의 합이 직선 거리보다 크다면 충돌
		if (a->GetInfo().sizeX + b->GetInfo().sizeY > distance)
			return true;

		return false;
	}

};