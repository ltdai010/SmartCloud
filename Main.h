#pragma once
class Main
{
public:
	Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight);
	~Main();
	void GameLoop();
	void FirstSetup();
	bool EatenBrain(int i);
	bool EatenRottenBrain(int i);
	bool EatenVirus(int i);
	bool Missed(int x);
	void DrawHeart();
	void BreakHeart(int i);
	void UpdateCondition();
	void CheckQuit();
	void IntergerToString(int passed_score);
	bool CloudTouchBorder();
	void PlayMusic(Mix_Music* music);
	void UpdateMusic();
	void StartMenu();
	void EatBook();
private:
	Game_setup *game_setup;
	Game_Text *score_text;
	Sprite *game_quit;
	Sprite *background;
	Sprite *heart[HEALTH_POINT];
	Cloud *cloud;
	Food *food;
	Menu *menu;
	Threat *threat;
	Mix_Music *backgroundSound;
	bool quit;
	char scoreStr[10];
	Uint32 score;
	long long int timeCheck;
	bool playMusic;
	bool slowDown;
	Selection select;
	long long int slowTime;
	int mousePointX;
	int mousePointY;
	int healthPoint;
};

