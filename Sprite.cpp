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
	moveLeft = false;
	moveRight = false;
	timeCheck = SDL_GetTicks();
}


Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	SDL_RenderCopy(renderer, image, NULL, &rect);
}

void Sprite::Movement()
{
	UpdateControl();
	if (timeCheck + TIME_SPACE < SDL_GetTicks()) //make the game slower. 1 frame per 0.01s
	{
		UpdateMovement();
		timeCheck = SDL_GetTicks();
	}
}

void Sprite::UpdateControl() //a button: turn left, d button: turn right
{
	switch (game_event->type)
	{
	case SDL_KEYDOWN:
		switch (game_event->key.keysym.sym)
		{
		case SDLK_a:
			moveLeft = true;
			std::cout << "a was pressed" << std::endl;
			break;
		case SDLK_d:
			moveRight = true;
			std::cout << "d was pressed" << std::endl;
			break;
		default:
			break;
		}
	default:
		break;
	}
	switch (game_event->type)
	{
	case SDL_KEYUP:
		switch (game_event->key.keysym.sym)
		{
		case SDLK_a:
			moveLeft = false;
			break;
		case SDLK_d:
			moveRight = false;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void Sprite::UpdateMovement() //change position of the cloud base on moving command
{
	if (moveLeft)
	{
		SetX(GetX() - ClOUD_SPEED);
		std::cout << "moving left" << std::endl;
	}
	if (moveRight)
	{
		SetX(GetX() + ClOUD_SPEED);
		std::cout << "moving right" << std::endl;
	}
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
