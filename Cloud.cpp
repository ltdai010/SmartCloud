#include "pch.h"
#include "Cloud.h"


Cloud::Cloud(Game_setup *game_setup, std::string path, int x, int y, int w, int h)
{
	game_event = game_setup->GetMainEvent();
	cloud = new Sprite(game_setup, path, x, y, w, h);
	cloud->SetAmountFrame(CLOUD_FRAME_X, CLOUD_FRAME_Y);
	timeCheck = SDL_GetTicks();
	moveLeft = false;
	moveRight = false;
	preLeft = true;
	preRight = false;
}


Cloud::~Cloud()
{
	delete cloud;
	delete game_event;
}

void Cloud::Movement()
{
	UpdateControl();
	UpdateAnimation();
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		UpdateMovement();
		timeCheck = SDL_GetTicks();
	}
}

void Cloud::UpdateAnimation()
{
	if (moveLeft)
	{
		cloud->PlayAnimation(1, 1, 0, 0);
	}
	else if (moveRight)
	{
		cloud->PlayAnimation(1, 1, 1, 0);
	}
	else if(preLeft)
	{
		cloud->SetCurrentFrame(0);
		cloud->PlayAnimation(0, 0, 0, 0);
	}
	else if (preRight)
	{
		cloud->SetCurrentFrame(0);
		cloud->PlayAnimation(0, 0, 1, 0);
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
			preLeft = false;
			preRight = false;
			std::cout << "a was pressed" << std::endl;
			break;
		case SDLK_d:
			moveRight = true;
			preLeft = false;
			preRight = false;
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
			preLeft = true;
			break;
		case SDLK_d:
			moveRight = false;
			preRight = true;
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