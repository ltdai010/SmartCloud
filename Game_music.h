#pragma once
class Game_music
{
public:
	Game_music(std::string music_path, ModeMusic mode);
	~Game_music();
	void PlayMusic();
	void PlayAudio();
private:
	Mix_Chunk *sound_effect;
	Mix_Music *music;
};

