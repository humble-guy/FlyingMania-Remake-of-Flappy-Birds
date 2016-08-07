#pragma once
class CInitialize
{
public:
	CInitialize(bool *quit, int s_width, int  s_height);
	~CInitialize();

	SDL_Renderer* GetRenderer();

	SDL_Event* Getmainevent();

	void begin();
	void end();
	SDL_Window* GetWindow() { return window; }


private:
	SDL_Window* window;

	SDL_Renderer *renderer;

	SDL_Event* mainevent;
};

