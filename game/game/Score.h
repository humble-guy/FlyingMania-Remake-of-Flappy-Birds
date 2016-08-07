#pragma once
#include"Initialize.h"
#include"Sprite.h"
class CScore
{
public:
	CScore(CInitialize *passed_setup, float *passed_camx, float *passed_camy);
	~CScore();
	void DrawText();
	void set_score(int s) { game_score = s; }
	void DisplayScore();
	void RenderScoreBox(int num,int i);
	void Draw();
private:
	int x;
	int game_score;
	CInitialize *setup;
	SDL_Window *window;
	SDL_Surface *screen;
	CSprite *scorebox[3];
	CSprite *end_display;
	CSprite *final_score;
	int h, t, o;
	
};

