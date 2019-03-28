#include "pch.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	bool* quit = false;
	Game_setup* game_setup = new Game_setup(quit, SCREEN_WIDTH, SCREEN_HEIGHT);
	Sprite* background = new Sprite(game_setup, "background.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Cloud* cloud = new Cloud(game_setup, "cloud.png", 200, 400, CLOUD_WIDTH, CLOUD_HEIGHT);
	while (!quit && game_setup->GetMainEvent()->type != SDL_QUIT)
	{
		game_setup->Begin();
		background->Draw();
		cloud->Movement();
		cloud->Draw();
		game_setup->End();
	}
	delete game_setup;
	return 0;
}
