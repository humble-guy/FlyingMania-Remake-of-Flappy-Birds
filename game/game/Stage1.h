#pragma once
#include"Sprite.h"
#include"stdafx.h"
#include"Initialize.h"
#include"Pipe.h"
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
class CStage1
{
public:
	CStage1(int passed_width, int passed_height, float *camerax, float *cameray, CInitialize *setup);
	~CStage1();
	void Draw();
	void Update();
	void save_level();
	void load_level();
	enum ModeType {
		start,
		Display,
		PlayGame,
		CreateLevel,
		end,
		display_score
	};
	vector<CPipe*> get_pipes() { return pipe; }
	vector<CPipe*> get_flipped_pipes() { return rev_pipe; }
	int getmode() { return mode; }
	void setmode(int x) { mode = x; }
	
private:
	int MouseX;
	int MouseY;
	int mode;
	CInitialize *setup;
	float *camerax;
	float *cameray;
	bool onepressed;
	int i;
	CSprite *sky[20];
	CSprite *mountain[20];
	CSprite *grass[20];
	CSprite *clouds[20];
	CSprite *flag[2];
	vector<CPipe*> pipe;
	vector<CPipe*> rev_pipe;
	int width;
	int height;
};

