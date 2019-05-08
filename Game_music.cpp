#include "pch.h"
#include "Game_music.h"

// Load nhạc: Nếu tham số truyền vào là music_path, 0 thì load nhạc, còn không thì load audio
Game_music::Game_music(std::string music_path, ModeMusic mode)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to open sound device" << std::endl;
	}
	if (mode == MUSIC)
	{
		music = Mix_LoadMUS(music_path.c_str());
		if (music == NULL)
		{
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
	else
	{
		sound_effect = Mix_LoadWAV(music_path.c_str());
		if (sound_effect == NULL)
		{
			printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
}

Game_music::~Game_music()
{
	Mix_FreeChunk(sound_effect);
	sound_effect = NULL;
	Mix_FreeMusic(music);
	music = NULL;
}
void Game_music::PlayMusic()
{
	if (Mix_PlayMusic(music, -1) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to play sound" << std::endl;
	}
}
void Game_music::PlayAudio()
{
	if (Mix_PlayChannel(-1, sound_effect, 0) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to play treasure sound" << std::endl;
	}
}
