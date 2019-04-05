#pragma once
class Main
{
public:
	Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight);
	~Main();
	void GameLoop();
	void FirstSetup();
	bool EatenBrain(int i);
	bool MissedBrain(int i);
	void UpdateCondition();
	void IntergerToString(int passed_score);
	bool CloudTouchBorder();
	void PlayMusic(Mix_Music* music);
	void PlayChunk(Mix_Chunk* chunk);
	void UpdateMusic();
	void EatBook();
private:
	Game_setup *game_setup;
	Game_Text *score_text;
	Sprite *background;
	Cloud *cloud;
	Food *food;
	Mix_Music *backgroundSound;
	Mix_Chunk *eatBrain;
	bool quit;
	char scoreStr[10];
	Uint32 score;
	long long int timeCheck;
	bool playMusic;
};

