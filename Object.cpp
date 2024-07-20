#include "Object.h"

RECT Object::GetRect()
{
	RECT rc =
	{
		info.posX - info.sizeX,
		info.posY - info.sizeY,
		info.posX + info.sizeX,
		info.posY + info.sizeY
	};

    return rc;
}

Object::Object()
{
}

Object::~Object()
{
}
