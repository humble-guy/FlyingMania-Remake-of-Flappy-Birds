#pragma once
#include"Initialize.h"
#include"Sprite.h"
class CPipe
{
public:
	CPipe(int x,int y, float *camerax, float *cameray, CInitialize *setup);
	~CPipe();
	void Draw();
	void DrawFlipped();
	
	int getx();
	int gety();
	CSprite* get_green_pipe() { return green_pipe; }
private:
	int x, y;
	CSprite *green_pipe;
};

