#include "stdafx.h"
#include "Pipe.h"



CPipe::CPipe(int passed_x,int passed_y, float *camerax, float *cameray, CInitialize *setup)
{
	x = passed_x;
	y = passed_y;
	//if(x==0)
	    green_pipe = new CSprite(setup->GetRenderer(), "Data/obstacles/pipe.png", x, y, 60,195, camerax, cameray, CCollisionRectangle(0, 0, 60, 195));
	//else 
	//	green_pipe = new CSprite(setup->GetRenderer(), "Data/obstacles/pipe.png", x + 300, y, 80, 200, camerax, cameray, CCollisionRectangle(0, 0, 80, 200));

}

void CPipe::Draw()
{
	green_pipe->Draw();
}

void CPipe::DrawFlipped()
{
	green_pipe->DrawFlipped();
}
CPipe::~CPipe()
{
	delete green_pipe;
}
int CPipe::getx()
{
	return x;
}
int CPipe::gety()
{
	return y;
}