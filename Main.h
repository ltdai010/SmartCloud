#pragma once
class Main
{
public:
	Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight);
	~Main();
	void GameLoop();
	void FirstSetup();
	bool EatenBrain(int i);
	bool EatenBook();
	bool EatenRottenBrain(int i);
	bool EatenVirus(int i);
	bool Missed(int y);
	bool HighScore();
	void DrawHeart();
	void BreakHeart(int i);
	void ReviveHeart(int i);
	void UpdateCondition();
	void SetCloudCondition();
	void CheckQuit();
	void IntergerToString(int passed_score, char string[]);
	bool CloudTouchBorder();
	void PlayMusic(Mix_Music* music);
	void UpdateMusic();
	void StartMenu();
	void CheckGameOverCommand();
	void CustomizeScoreStr();
private:
	Game_setup *game_setup;
	Game_Text *score_text;
	Game_Text *high_score_text;
	Game_Text *high_score_tittle;
	Game_Text *score_tittle;
	Sprite *game_quit;
	Sprite *background;
	Sprite *heart[HEALTH_POINT];
	Cloud *cloud;
	Food *food;
	Menu *menu;
	Threat *threat;
	Mix_Music *backgroundSound;
	Sprite *game_over;
	Game_Text *back_menu;
	SaveScore *saveScore;
	bool quit;
	bool invincible;
	char scoreStr[10];
	char hiScoreStr[10];
	Uint32 score;
	int scorePerBrain;
	BookType bookType;
	long long int timeCheck;
	bool playMusic;
	bool slowDown;
	Selection select;
	long long int slowTime;
	long long int bigSizeCoolDown;
	long long int doubleScoreCoolDown;
	int hitboxW;
	int hitboxH;
	int mousePointX;
	int mousePointY;
	int healthPoint;
};

