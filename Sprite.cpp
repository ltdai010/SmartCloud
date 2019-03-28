#include "pch.h"
#include "Sprite.h"


Sprite::Sprite(Game_setup *game_setup, std::string path, int x, int y, int w, int h)
{
	game_event = game_setup->GetMainEvent();
	this->renderer = game_setup->GetRenderer();
	image = NULL;
	image = IMG_LoadTexture(this->renderer, path.c_str());
	if (image == NULL)
	{
		std::cout << "Could not load image" << std::endl;
	}
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}


Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	SDL_RenderCopy(renderer, image, NULL, &rect);
}


int Sprite::GetX()
{
	return rect.x;
}

int Sprite::GetY()
{
	return rect.y;
}

void Sprite::SetX(int x)
{
	rect.x = x;
}

void Sprite::SetY(int y)
{
	rect.y = y;
}
