#include "stdafx.h"
#include "MainCharacter.h"



CMainCharacter::CMainCharacter(CInitialize *passed_setup, float *passed_camx, float *passed_camy, CStage1 *passed_stage1)
{
	stage1 = passed_stage1;
	setup = passed_setup;

	camerax = passed_camx;
	cameray = passed_camy;

	timecheck = SDL_GetTicks();

	fly = new CSound();

	collide = new CSound();

	//mario = new CSprite(setup->GetRenderer(), "Data/mario.png", 320, 200 40, 60,camerax,cameray);

	//collision_rect = { 320, 200, 50, 50 };

	collision_rect = { 322, 202, 48, 48 };

	mario = new CSprite(setup->GetRenderer(), "Data/BlueBirdFrames.png", 320, 200, 50, 50, camerax, cameray,collision_rect);

	collided = new CSprite(setup->GetRenderer(), "Data/Crash.png", 350, 200, 48, 48, camerax, cameray, CCollisionRectangle(0,0,0,0));

	//mario->setup_animation(10, 1);

	mario->setup_animation(8, 1);
	mario->currentframe = 0;

	colliding = false;

	keyup = true;

	moveu = false;

	moved = true;

	fly->load_sfx("Data/sounds/fly.wav");

	collide->load_sfx("Data/sounds/collision.wav");

	score = 0;
	
	angle = 0;

	game_over = new CSprite(setup->GetRenderer(), "Data/end_mode.gif",300 , 0, 350, 160 , camerax, cameray, CCollisionRectangle(0, 0, 0, 0));

	
	
}



CMainCharacter::~CMainCharacter()
{
    delete mario;
}

void CMainCharacter::Draw(double angle)
{
	mario->Draw_parameters(angle);
	//mario->Draw_parameters(-20.0);
    //	mario->DrawSteady();
}

void CMainCharacter::update()
{
	colliding = false;
	
	int pipes_score=0, rev_pipes_score=0;
	UpdateAnimation();
	UpdateControls();
	for (int i = 0; i < stage1->get_pipes().size(); i++)
	{
		if (mario->is_colliding(stage1->get_pipes()[i]->get_green_pipe()->get_colrect()))
		{
			colliding = true;
			//exit(1);
			cout << "Colliding with pipe\n";
			collide->start_sfx_sound();
			collided->setx(mario->getx());
			collided->sety(mario->gety() - 50);

	
		}
	
	}

	for (int i = 0; i < stage1->get_flipped_pipes().size(); i++)
	{
		if (mario->is_colliding(stage1->get_flipped_pipes()[i]->get_green_pipe()->get_colrect()))
		{
			colliding = true;
			//exit(1);
			cout << "Colliding with flipped pipe\n";
			collide->start_sfx_sound();
			collided->setx(mario->getx());
			collided->sety(mario->gety() - 50);

			
		}
	}

	
	if (mario->gety() >= 460)
	{
		colliding = true;
		cout << "Colliding with ground" << endl;
		collide->start_sfx_sound();
		collided->setx(mario->getx());
		collided->sety(mario->gety() - 50);

	
	}



/////////////////////////////////////////////////////////
	//SCORE UPDATION//
////////////////////////////////////////////////////////
	for (int i = 0; i < stage1->get_flipped_pipes().size(); i++)
	{
		if ((-*camerax+300)>=(stage1->get_flipped_pipes()[i]->getx()+30))
		{
			rev_pipes_score++;
		}
	}


	for (int i = 0; i < stage1->get_pipes().size(); i++)
	{
		if ((-*camerax+300)>=(stage1->get_pipes()[i]->getx()+30))
		{
			pipes_score++;
		}

	}

	score = rev_pipes_score + pipes_score;
	//cout << "Camerax:" << *camerax << endl;
//////////////////////////////////////////////////////////////////////////////////////
		 
if (colliding == true)
	{
		collide->start_sfx_sound();
		collided->setx(-*camerax+320);
		collided->sety(mario->gety() - 50);
		game_over->setx(-*camerax + 200);
		
		
		collided->Draw();
		
		
		cout << "Score:" << score;
		//if (stage1->getmode() == 2)
		//	stage1->setmode(4);
		//system("PAUSE");
		bool fivepressed = false;
		
		if (stage1->getmode() == 2)
			stage1->setmode(4);
		

	}
}

void CMainCharacter::UpdateAnimation()
{
	
	mario->playanimation(0, 7, 0, 250);
	
	switch (setup->Getmainevent()->type)
	{
	case SDL_KEYDOWN:
		
		
		if (setup->Getmainevent()->key.keysym.sym == SDLK_UP && keyup)
		{
			moveu = true;
		}
		 //mario->playanimation(4, 7, 0, 500);
		break;


	case SDL_KEYUP:
		
	
		
		switch (setup->Getmainevent()->key.keysym.sym)
		{
		case SDLK_UP:
			keyup = true;
			moveu = false;
			
			break;

        default:
			break;
		}
		break;
		
	default:
       // mario->playanimation(4, 7, 0, 500);
		break; 
		
	}

	
}
void CMainCharacter::UpdateControls()
{
	//*camerax -= 0.5f;
	*camerax -= 2.0f;

	if ((timecheck + 80) < SDL_GetTicks())     //This loop will run one time in each 1/2 second
	{
		timecheck = SDL_GetTicks();

		if (moveu && keyup)
		{

			angle = -20;
			fly->start_sfx_sound();
			if (mario->gety() <= 0)
				mario->sety(0);
			mario->sety(mario->gety() - 50);
			//*camerax -= 0.5f;
			keyup = false;
		}
		
		
			mario->sety(mario->gety() + 9);

			if (mario->gety() >= 460)
				mario->sety(460);
			angle = angle + 3;
			if (angle > 80)
				angle = 80;


	}

	

	
}

