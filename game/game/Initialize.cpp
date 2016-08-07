#include "stdafx.h"
#include "Initialize.h"


CInitialize::CInitialize(bool *quit, int swidth, int sheight)
{
	window = NULL;
	window = SDL_CreateWindow("Mario Bros::Redefined >>>Prakhar Agarwal 141112023<<<", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, swidth, sheight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		cout << "Window cannot be created";
		*quit = true;
	}

	renderer = NULL;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainevent = new SDL_Event();

}


CInitialize::~CInitialize()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainevent;
}

SDL_Renderer* CInitialize::GetRenderer()
{
	return renderer;
}

SDL_Event* CInitialize::Getmainevent()
{
	return mainevent;
}
void CInitialize::begin()
{
	SDL_PollEvent(mainevent);

	SDL_RenderClear(renderer);
}

void CInitialize::end()
{
	SDL_RenderPresent(renderer);
}