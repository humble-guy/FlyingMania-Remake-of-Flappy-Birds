#pragma once
#include "stdafx.h"
class CCollisionRectangle
{
public:
	CCollisionRectangle();
	CCollisionRectangle(int x,int y,int w,int h);
	~CCollisionRectangle();
	void set_rectangle(int x, int y, int w, int h);
	SDL_Rect getrect() { return collision_rect; }
	void setx(int x) { collision_rect.x = x + offsetx; }
	void sety(int y) { collision_rect.y = y + offsety; }
	int getx() { return collision_rect.x; }
	int gety() { return collision_rect.y; }
private:
	int offsetx;
	int offsety;
	SDL_Rect collision_rect;
};

