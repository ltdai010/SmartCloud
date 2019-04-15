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
	void CheckQuit(Selection *select);
	void IntergerToString(int passed_score);
	bool CloudTouchBorder();
	void PlayMusic(Mix_Music* music);
	void PlayChunk(Mix_Chunk* chunk);
	void UpdateMusic();
	void StartMenu();
	void EatBook();
private:
	Game_setup *game_setup;
	Game_Text *score_text;
	Sprite *game_quit;
	Sprite *background;
	Cloud *cloud;
	Food *food;
	Menu *menu;
	Mix_Music *backgroundSound;
	bool quit;
	char scoreStr[10];
	Uint32 score;
	long long int timeCheck;
	bool playMusic;
	Selection select;
	int mousePointX;
	int mousePointY;
};

