#include "pch.h"
#include "Game_setup.h"


Game_setup::Game_setup(bool* quit, int passed_ScreenWidth, int passed_ScreenHeight)
{
	window = NULL;
	window = SDL_CreateWindow("SDL Game!",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		passed_ScreenWidth,
		passed_ScreenHeight,
		SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == NULL)
	{
		std::cout << "There was ERROR" << std::endl << SDL_GetError();
		*quit = true;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
}

Game_setup::~Game_setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* Game_setup::GetRenderer()
{
	return renderer;
}

SDL_Event* Game_setup::GetMainEvent()
{
	return mainEvent;
}

void Game_setup::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void Game_setup::End()
{
	SDL_RenderPresent(renderer);
}
//test 2
