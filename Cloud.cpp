#include "pch.h"
#include "Cloud.h"


Cloud::Cloud(Game_setup *game_setup, std::string path, int x, int y, int w, int h)
{
	game_event = game_setup->GetMainEvent();
	cloud = new Sprite(game_setup, path, x, y, w, h);
	moveLeft = false;
	moveRight = false;
	timeCheck = SDL_GetTicks();
}


Cloud::~Cloud()
{
	delete cloud;
}

void Cloud::Movement()
{
	UpdateControl();
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		UpdateMovement();
		timeCheck = SDL_GetTicks();
	}
}

void Cloud::UpdateControl()
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

void Cloud::UpdateMovement()
{
	if (moveLeft)
	{
		cloud->SetX(cloud->GetX() - ClOUD_SPEED);
		std::cout << "moving left" << std::endl;
	}
	if (moveRight)
	{
		cloud->SetX(cloud->GetX() + ClOUD_SPEED);
		std::cout << "moving right" << std::endl;
	}
}

void Cloud::Draw()
{
	cloud->Draw();
}