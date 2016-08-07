#pragma once
#include"Initialize.h"
#include"Sprite.h"
#include "MainCharacter.h"
#include"Sound.h"
#include"Stage1.h"
#include"Score.h"


class CMain
{
public:
	CMain(int passsed_width, int passed_height);
	~CMain();

	void gameloop();

	void UpdateBackground();
private:

	float camerax;
	float cameray;
	
	int s_width;
	int s_height;
	bool quit;
	
	CSprite *playbackground;
	CSprite *playimage;
	
	CScore *game_score;

	CSprite *start;

	CMainCharacter *mario;
	CStage1 *stage1;
	
	CSound *sound;

	CSound *end_sound;
	int check = 1;

	CInitialize *setup;

};

