#pragma once

#include"stdafx.h"
#include"CollisionRectangle.h"

class CSprite
{
public:
	CSprite(SDL_Renderer * passed_renderer, string file_path, int x, int y, int w, int h, float *passed_camx, float *passed_camy,CCollisionRectangle passed_collision_rect);
	void Draw();
	~CSprite();

	bool is_colliding(CCollisionRectangle colrect);
	int if_passed_pipe();
	void Draw_parameters(double angle);
	void DrawFlipped();
	void setx(int x);
	void sety(int y);
	void setposition(int x, int y);
	void playanimation(int beginframe, int endframe, int row, float speed);
	int getx();
	int gety();
	void DrawSteady();
	void setup_animation(int passed_framex, int passed_framey);
    int currentframe;
	CCollisionRectangle get_colrect() { return collision_rect; }
private:
	CCollisionRectangle collision_rect;
	CCollisionRectangle *colrect;
	float *camerax;
	float *cameray;

	int framex;
	int framey;

	SDL_Rect camera;
	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;

	SDL_Rect debug_mainchar;

	SDL_Texture* collision_image;

	int image_width;
	int image_height;

	int delay;

	

	SDL_Renderer * renderer;

	
};

