#include "stdafx.h"
#include "Main.h"
#include "Sound.h"



CMain::CMain(int passed_width, int passed_height)
{
	s_width = passed_width;
	s_height = passed_height;

	camerax = 0;
	cameray = 0;

	
	
	quit = false;

	setup = new CInitialize(&quit, s_width, s_height);

	stage1 = new CStage1(s_width, s_height, &camerax, &cameray, setup);
	
	int i;
	
	mario = new CMainCharacter(setup,&camerax,&cameray,stage1);

	sound = new CSound();

	start = new CSprite(setup->GetRenderer(), "Data/display.png", 0, 0, s_width, s_height, &camerax, &cameray, CCollisionRectangle(0,0,0,0));

	playbackground = new CSprite(setup->GetRenderer(), "Data/stage1.png", 0, 0, s_width, s_height, &camerax, &cameray, CCollisionRectangle(0, 0, 0, 0));

	playimage = new CSprite(setup->GetRenderer(), "Data/playicon.png",  300, 150, s_width/5, s_height/7, &camerax, &cameray, CCollisionRectangle(0, 0, 0, 0));

	game_score = new CScore(setup,&camerax,&cameray);
	
}


CMain::~CMain()
{
	
	delete mario;
	delete setup;
	delete stage1;
}

void CMain::gameloop()
{


	sound->load_music("Data/sounds/music.wav");
	//end_sound->load_music("Data/sounds/score.wav");
    
    sound->start_game_sound();


	while (!quit && setup->Getmainevent()->type != SDL_QUIT)
	{
		
		setup->begin();	
		
		if (stage1->getmode() == 0)
		{
			start->Draw();
			stage1->Update();
		}
		else if (stage1->getmode() == 1)
		{

			playbackground->Draw();
			playimage->Draw();
			stage1->Update();
			
		}
		else if (stage1->getmode() == 2)
		{
			
		
			
			stage1->Draw();

			mario->Draw(mario->angle);

			// camerax -= 0.4f;
			//just for debug above is original
			//camerax -= 1.0f;
			mario->update();
			


		}
		else if (stage1->getmode() == 4)
		{
			stage1->Draw();

			mario->Draw(mario->angle);

			//cout << "in mode 4" << endl;

			mario->collided->Draw();

			mario->game_over->Draw();

			//SDL_Delay(5000);

			switch (setup->Getmainevent()->type)
			{
			case SDL_KEYDOWN:
				if(setup->Getmainevent()->key.keysym.sym==SDLK_RETURN)
				     stage1->setmode(5);
				break;
			case SDL_KEYUP:break;

			}
				
		}
		else if (stage1->getmode() == 5)
		{
            sound->stop_game_sound();
			/*if (check == 1)
			{
				cout << "Passed";
				end_sound->load_music("Data/sounds/score.wav");
				end_sound->start_game_sound();
				check = 0;
			}*/
			//end_sound->start_game_sound();
			game_score->set_score(mario->GetScore());
			game_score->DisplayScore();
			game_score->Draw();
		}

		setup->end();
	}
	
	//end_sound->stop_game_sound();
}
	
