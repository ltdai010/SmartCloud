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
	void EatBook();
private:
	Game_setup *game_setup;
	Game_Text *score_text;
	Sprite *background;
	Cloud *cloud;
	Food *food;
	bool quit;
	Uint32 score;
	long long int timeCheck;
};

