#include "stdafx.h"
#include "Stage1.h"


CStage1::CStage1(int s_width, int s_height,float *passed_camerax,float *passed_cameray,CInitialize *passed_setup)
{
	setup = passed_setup;
	camerax = passed_camerax;
	cameray = passed_cameray;
	width = s_width;
	height = s_height;
	for (i = 0; i < 20; i++)
	{
		//background[i] = new CSprite(setup->GetRenderer(), "Data/background.png", s_width*i, 0, s_width, s_height, &camerax, &cameray);
		sky[i] = new CSprite(setup->GetRenderer(), "Data/stage1/sky.png", s_width*i, 0, s_width, s_height, camerax, cameray, CCollisionRectangle(0, 0, 0, 0));
		mountain[i] = new CSprite(setup->GetRenderer(), "Data/stage1/mountain.png", s_width*i, s_height / 2, s_width, 5 * s_height / 12, camerax, cameray,CCollisionRectangle(0,0,0,0));
		grass[i] = new CSprite(setup->GetRenderer(), "Data/stage1/grass.png", s_width*i, 11 * s_height / 12, s_width, s_height / 12, camerax, cameray, CCollisionRectangle(0, 0, 0, 0));
		clouds[i] = new CSprite(setup->GetRenderer(), "Data/stage1/Clouds1.png", s_width*i, 0, s_width, s_height / 12, camerax, cameray, CCollisionRectangle(0, 0, 0, 0));

	}

	flag[0] = new CSprite(setup->GetRenderer(), "Data/stage1/flag.gif", 300, 50, s_width/12, s_height / 6, camerax, cameray, CCollisionRectangle(0, 0, 0, 0));
	flag[1] = new CSprite(setup->GetRenderer(), "Data/stage1/flag.gif", 15200, 50, s_width / 12, s_height / 6, camerax, cameray, CCollisionRectangle(0, 0, 0, 0));

	flag[0]->setup_animation(9, 1);
	flag[1]->setup_animation(9, 1);
	flag[1]->currentframe = 0;
	flag[0]->currentframe = 0;


	//For placing the pipes in accordance with some loop
	/*for (i = 0; i < 100;i++)
	pipe.push_back(new CPipe(800+(200*i), 500, camerax, cameray, setup));
	*/
	onepressed = false;
	load_level();
	mode = start;
	MouseX = 0;
	MouseY = 0;
	
}

void CStage1::load_level()
{
	ifstream file("Data/stage1.txt");
	string line;
	
	enum object_type {
		type_none,
		type_pipe,
		type_flip_pipe
	};

	int current_type = type_none;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			if (line == "Pipes")
			{
				current_type = type_pipe;
			}
			else if (line == "End")
			{
				current_type = type_none;
			}
			else if (line == "FlippedPipes")
			{
				current_type = type_flip_pipe;
			}
			else
			{
				if (current_type == type_pipe)
				{
					istringstream iss(line);
					
					int tempx = 0;
					int tempy = 0;
					string prev_word;
					while (iss)
					{
						string word;
						iss >> word;
						if (prev_word == "x:")
						{
							tempx = atoi(word.c_str());
							
						}

						if (prev_word == "y:")
						{
							tempy = atoi(word.c_str());
							//cout << "X:" << tempx << "\tY:" << tempy << endl;
							//cout << "\nPushing back";
							pipe.push_back(new CPipe(tempx, tempy, camerax, cameray, setup));
						}
						prev_word = word;
					}
				}


				if (current_type == type_flip_pipe)
				{
					istringstream iss(line);

					int tempx = 0;
					int tempy = 0;
					string prev_word;
					while (iss)
					{
						string word;
						iss >> word;
						if (prev_word == "x:")
						{
							tempx = atoi(word.c_str());

						}

						if (prev_word == "y:")
						{
							tempy = atoi(word.c_str());
							//cout << "X:" << tempx << "\tY:" << tempy << endl;
							//cout << "\nPushing back";
							rev_pipe.push_back(new CPipe(tempx, tempy, camerax, cameray, setup));
						}
						prev_word = word;
					}
				}

			}
		}
	}

}

void CStage1::save_level()
{
	ofstream file;
	file.open("Data/stage1.txt",ios::app);
	file << "Pipes"<<endl;
	for (vector<CPipe*>::iterator i = pipe.begin(); i != pipe.end(); ++i)
	{
		file << "x: "<<(*i)->getx()<<"\ty: "<<(*i)->gety()<<endl;
	}
	file << "End"<<endl;
	file << "FlippedPipes" << endl;
	for (vector<CPipe*>::iterator i = rev_pipe.begin(); i != rev_pipe.end(); ++i)
	{
		file << "x: " << (*i)->getx() << "\ty: " << (*i)->gety() << endl;
	}
	file << "End" << endl;
	file.close();
	cout << "Level Saved";
}
void CStage1::Update()
{
	if (mode == CreateLevel)
	{

		if (setup->Getmainevent()->type == SDL_KEYDOWN)
		{
			if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_9)
			{
				save_level();
				onepressed = true;
			}
		}
		if (setup->Getmainevent()->type == SDL_KEYUP)
		{
			if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_9)
			{
				onepressed = false;

			}
		}


		if (setup->Getmainevent()->type == SDL_KEYDOWN)
		{
			if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_2)
			{
				if (pipe.size() > 0)
				{
					pipe.pop_back();
				}
				onepressed = true;
				cout << "One Pressed!\n";
			}
		}
		if (setup->Getmainevent()->type == SDL_KEYUP)
		{
			if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_2)
			{
				onepressed = false;

			}
		}



		if (setup->Getmainevent()->type == SDL_KEYDOWN)
		{
			if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_1)
			{
				pipe.push_back(new CPipe(-*camerax+300, -*cameray+300, camerax, cameray, setup));
				onepressed = true;
				cout << "One Pressed!\n";
			}
		}
		if (setup->Getmainevent()->type == SDL_KEYUP)
		{
			if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_1)
			{
				onepressed = false;

			}
		}
       


		if (setup->Getmainevent()->type == SDL_KEYDOWN)
		{
			if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_8)
			{
				rev_pipe.push_back(new CPipe(-*camerax+300 , -*cameray , camerax, cameray, setup));
				onepressed = true;
				cout << "Eight Pressed!\n";
			}
		}
		if (setup->Getmainevent()->type == SDL_KEYUP)
		{
			if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_8)
			{
				onepressed = false;

			}
		}
	}

	if (setup->Getmainevent()->type == SDL_KEYDOWN)
	{
		if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_0)
		{
			if (mode == CreateLevel)
			{
				cout << "Level creation off!\n";
				mode = PlayGame;
			}
			else if (mode == PlayGame)
			{
				cout << "Create level time\n";
				mode = CreateLevel;
			}
			onepressed = true;
		}
	}

///////////////////////////////////////////

	if (setup->Getmainevent()->type == SDL_KEYDOWN)
	{
		if (!onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_RETURN)
		{
			if (mode ==start )
			{
				cout << "Hover over play to start the game!\n";
				mode = Display;
			}
			onepressed = true;
		}
	}
////////////////////////////////////////////

	if (setup->Getmainevent()->type == SDL_KEYUP)
	{
		if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_RETURN)
		{
			onepressed = false;

		}
	}
//////////////////////////////////////////////


///////////////////////////////////////////

	if (mode == Display)
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				if (MouseX>=300 && MouseX<=460 && MouseY>=150 && MouseY<=221)
				{
					cout << "Game Begins!\n";
					mode = PlayGame;
				}
			}
		
	

	//////////////////////////////////////////////



	if (setup->Getmainevent()->type == SDL_KEYUP)
	{
		if (onepressed && setup->Getmainevent()->key.keysym.sym == SDLK_0)
		{
			onepressed = false;

		}
	}



}

CStage1::~CStage1()
{
	for (int i = 0; i < 20; i++)
	{
		delete mountain[i];
		delete grass[i];
		delete sky[i];
		delete clouds[i];
	}
	for (vector<CPipe*>::iterator i = pipe.begin(); i != pipe.end(); ++i)
	{
		delete(*i);
	}

	for (vector<CPipe*>::iterator i = rev_pipe.begin(); i != rev_pipe.end(); ++i)
	{
		delete(*i);
	}
	rev_pipe.clear(); 
	delete flag[0];
	delete flag[1];

}

void CStage1::Draw()
{
	for (int i = 0; i < 20; i++)
	{
		sky[i]->Draw();
		mountain[i]->Draw();
		grass[i]->Draw();
		clouds[i]->Draw();
	}
	for (vector<CPipe*>::iterator i = pipe.begin(); i != pipe.end(); ++i)
	{
		(*i)->Draw();
	}
	for (vector<CPipe*>::iterator i = rev_pipe.begin(); i != rev_pipe.end(); ++i)
	{
		(*i)->DrawFlipped();
	}
	flag[0]->Draw();
	flag[0]->playanimation(0, 8, 0, 100);
	flag[1]->Draw();
	flag[1]->playanimation(0, 8, 0, 100);
	Update();
}