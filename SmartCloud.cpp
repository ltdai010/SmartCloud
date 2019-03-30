#include "pch.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	Main *main = new Main(SCREEN_WIDTH, SCREEN_HEIGHT, CLOUD_WIDTH, CLOUD_HEIGHT);
	main->GameLoop();
	delete main;
	return 0;
}
