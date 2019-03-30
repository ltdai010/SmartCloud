#pragma once
class Main
{
public:
	Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight);
	~Main();
	void GameLoop();
private:
	Game_setup *game_setup;
	Sprite *background;
	Cloud *cloud;
	Food *food;
	bool quit;
	long long int timeCheck;
};

