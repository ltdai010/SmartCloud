#include "pch.h"
#include "Game_Text.h"


Game_Text::Game_Text(Game_setup *game_setup, std::string path, int textSize)
{
	this->game_setup = game_setup;
	font = TTF_OpenFont(path.c_str(), textSize);
	if (font == NULL)
	{
		std::cout << "Failed to initialize font" << std::endl << TTF_GetError();
	}
	color = { 0,0,0 };
	rect.x = 0;
	rect.y = 0;
	rect.w = 300;
	rect.h = 100;
}


Game_Text::~Game_Text()
{
	TTF_CloseFont(font);
}

void Game_Text::LoadText(std::string path)
{
	SDL_DestroyTexture(text);
	if (!(text_surface = TTF_RenderText_Solid(font, path.c_str(), color)))
	{
		std::cout << "Failed to load text" << std::endl << TTF_GetError();
	}
	text = SDL_CreateTextureFromSurface(game_setup->GetRenderer(), text_surface);
	SDL_FreeSurface(text_surface);
}

void Game_Text::RenderText()
{
	if (text == NULL)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_RenderCopy(game_setup->GetRenderer(), text, NULL, &rect);
	}
}

void Game_Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	color = { red, green, blue };
}

void Game_Text::SetSize(int width, int height)
{
	rect.w = width;
	rect.h = height;
}

void Game_Text::SetLocation(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
