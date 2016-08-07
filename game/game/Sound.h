#pragma once
#include "stdafx.h"
class CSound
{
public:
	CSound();
	~CSound();
	enum sound_type {
		SOUND_MUSIC=0,
		SOUND_SFX=1
	};

	
	void start_game_sound();
	void stop_game_sound();
	void load_music(std::string FileName);
	void load_sfx(std::string Filename);
	void start_sfx_sound();

private:
	std::string music_id;
	Mix_Music *music1;
	Mix_Chunk *sfx;

};

