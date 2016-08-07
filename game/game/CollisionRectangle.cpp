#include"stdafx.h"
#include "CollisionRectangle.h"


CCollisionRectangle::CCollisionRectangle()
{
	set_rectangle(0, 0, 0, 0);
}

CCollisionRectangle::CCollisionRectangle(int x, int y, int w, int h)
{
	offsetx = x;
	offsety = y;
	set_rectangle(0, 0, w, h);
}

CCollisionRectangle::~CCollisionRectangle()
{
}

void CCollisionRectangle::set_rectangle(int x, int y, int w, int h)
{
    collision_rect.x = x+offsetx;
	collision_rect.y = y+offsety;
	collision_rect.w = w;
	collision_rect.h = h;
}