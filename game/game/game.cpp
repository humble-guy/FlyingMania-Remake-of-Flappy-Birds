#include "stdafx.h"
#include"Main.h"


int main(int argc, char *argv[])               //main parameters needed for running SDL
{

	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	CMain *cmain = new CMain(800, 500);

	cmain->gameloop();

	delete cmain;

	TTF_Quit();

	return 0;
}
