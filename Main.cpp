#include "pch.h"
#include "Main.h"


Main::Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight)
{
	quit = false;
	game_setup = new Game_setup(&quit, screenWidth, screenHeight);
	background = new Sprite(game_setup->GetRenderer(), "background.bmp", 0, 0, screenWidth, screenHeight);
	cloud = new Cloud(game_setup, "cloud.png", 200, 450, cloudWidth, cloudHeight);
	food = new Food(game_setup);
	timeCheck = SDL_GetTicks();
}


Main::~Main()
{
	delete game_setup;
	delete background;
	delete cloud;
}

void Main::GameLoop()
{
	timeCheck = SDL_GetTicks();
	food->RandomSpawnFood();
	food->SpawnFood();
	while (!quit && game_setup->GetMainEvent()->type != SDL_QUIT)
	{
		game_setup->Begin();

		background->Draw();
		cloud->Movement();
		cloud->Draw();
		food->Movement();
		food->Draw();

		game_setup->End();
	}
}
