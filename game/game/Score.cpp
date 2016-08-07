#include "stdafx.h"
#include "Score.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


CScore::CScore(CInitialize *passed_setup, float *passed_camx, float *passed_camy)
{
	setup = passed_setup;

	x = 0;
	for (int i = 0; i < 3; i++)
	{
		scorebox[i] = new CSprite(setup->GetRenderer(), "Data/game_scores.gif", 450 + i * 90, 150, 80, 150, passed_camx, passed_camy, CCollisionRectangle(0, 0, 0, 0));
		scorebox[i]->setup_animation(5, 2);
	}
	end_display = new CSprite(setup->GetRenderer(), "Data/game_over.jpg", 0, 0, 800, 500, passed_camx, passed_camy, CCollisionRectangle(0, 0, 0, 0));

	final_score = new CSprite(setup->GetRenderer(), "Data/final_score.png", 100, 110, 300, 290, passed_camx, passed_camy, CCollisionRectangle(0, 0, 0, 0));

}


CScore::~CScore()
{
	delete setup;
	delete window;
	delete screen;
	for (int i = 0; i < 3; i++)
		delete scorebox[i];
}

void CScore::DrawText()
{
	window = setup->GetWindow();
	
	char buffer[30];
	string msg;
	
    msg = itoa(game_score, buffer, 10);
	//cout << msg.c_str()<< endl;
	TTF_Font *font;
	SDL_Color color;
	color.r = 255;
	color.g = 0;
	color.b = 255;
	screen = SDL_GetWindowSurface(window);
	font = TTF_OpenFont("Data/ARIAL.ttf", 60);
	SDL_Color foregroundcolor={ 255,255,255 };
	SDL_Color backgroundcolor = { 0,0,255 };
	if (!font)
		cout << "Error loading font" << endl;
	SDL_Rect coordinates;
	coordinates.x = 100;
	coordinates.y = 100;
	coordinates.h = 0;
	coordinates.w = 0;


	SDL_Surface *message = TTF_RenderText_Solid(font,"Hello World",foregroundcolor);
	message = TTF_RenderText_Solid(font, msg.c_str(), color);
	SDL_FillRect(screen, NULL, 0);
	SDL_BlitSurface(message, NULL,screen , NULL);
	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	TTF_CloseFont(font);
	SDL_FreeSurface(message);
	SDL_RenderPresent(setup->GetRenderer());
}

void CScore::DisplayScore()
{
	
	int temp = game_score;
	o = temp % 10;
	temp = temp / 10;
	RenderScoreBox(o, 2);

	t = temp % 10;
	x = 540;
	RenderScoreBox(t, 1);

	temp = temp / 10;
	h = temp % 10;
	x = 630;
	RenderScoreBox(h, 0);

}

void CScore::RenderScoreBox(int num,int i)
{
	
	if (num < 5)
	{
		scorebox[i]->currentframe = num;
		scorebox[i]->playanimation(num, num, 0, 500);

	}

	else if (num >= 5)
	{
		scorebox[i]->currentframe = num - 5;
		scorebox[i]->playanimation(num - 5, num - 5, 1, 500);
	}



}

void CScore::Draw()
{
	 end_display->DrawSteady();
	 for (int i = 0; i < 3;i++)
        scorebox[i]->DrawSteady();
	 final_score->DrawSteady();
}