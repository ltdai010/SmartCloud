#include "pch.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
	}
	Main *main = new Main(SCREEN_WIDTH, SCREEN_HEIGHT, CLOUD_WIDTH, CLOUD_HEIGHT);
	main->GameLoop();
	delete main;
	TTF_Quit();
	SDL_Quit();
	return 0;
}
