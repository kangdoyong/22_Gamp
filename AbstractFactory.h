#pragma once

class Object;

// 객체 생성 시, 생성하고자 하는 객체의 타입만 다를 뿐
// 매번 동일한 로직을 사용함 -> (new, Initialize)
// 그럼 매번 달라지는 타입만을 일반화하여, 위의 반복되는 문제를
// 좀 더 편리하게 해결할 수 있음
// 디자인 패턴 중에 생성 기법
// 추상 팩토리 패턴
template<typename T>
class AbstractFactory
{
public:
	static Object* CreateObject()
	{
		Object* obj = new T();
		obj->Initialize();

		return obj;
	}

	static Object* CreateObject(int x, int y)
	{
		Object* obj = new T();
		obj->Initialize();
		obj->SetPos(x, y);

		return obj;
	}
};