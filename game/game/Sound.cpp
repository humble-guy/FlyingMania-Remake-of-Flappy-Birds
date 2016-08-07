#include "stdafx.h"
#include "Sound.h"


CSound::CSound()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	music1 = NULL;
	sfx = NULL;
}


CSound::~CSound()
{
	delete music1;
	delete sfx;
}


void CSound::load_music(std::string FileName)
{
	music1 = Mix_LoadMUS(FileName.c_str());
}

void CSound::load_sfx(std::string Filename)
{
	sfx = Mix_LoadWAV(Filename.c_str());
}
void CSound::start_sfx_sound()
{
	Mix_PlayChannel(-1, sfx, 0);
}

void CSound::start_game_sound()
{
	Mix_PlayMusic(music1, -1);
}
void CSound::stop_game_sound()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music1);
	music1 = NULL;
	Mix_CloseAudio();
}