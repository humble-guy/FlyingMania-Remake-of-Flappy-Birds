#pragma once
#include "Sprite.h"
#include "Initialize.h"
#include"Sound.h"
#include"CollisionRectangle.h"
#include"Stage1.h"
#include"Score.h"
class CMainCharacter
{
public:
	
	CMainCharacter(CInitialize *passed_setup,float *passed_camx,float *passed_camy,CStage1 *passed_stage1);
	
	~CMainCharacter();

	void update();
	
	void Draw(double angle);

   double angle;

   CSprite *collided;
   CSprite *game_over;
   
   bool colliding;

   int GetScore() { return score; }

private:

	CStage1 *stage1;
	int timecheck;

	CScore *game_score;

	CSound *fly;
	CSound *collide;
	CSound *pass;
	
	bool keyup;

	float *camerax;
	float *cameray;

	bool moveu;
	bool moved;

	CSprite *mario;

	

	void UpdateAnimation();
	void UpdateControls();

	CInitialize *setup;

	CCollisionRectangle collision_rect;

	int score;
	
};

