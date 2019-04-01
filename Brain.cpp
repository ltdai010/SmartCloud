#include "pch.h"
#include "Brain.h"


Brain::Brain(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h)
{
	brain = new Sprite(passed_game_setup->GetRenderer(), path, x, y, w, h);
}


Brain::~Brain()
{
	delete brain;
}

void Brain::MoveDown()
{
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		brain->SetY(brain->GetY() + BRAIN_SPEED);
		timeCheck = SDL_GetTicks();
	}
}

void Brain::Draw()
{
	brain->Draw();
}

void Brain::SetX(int x)
{
	brain->SetX(x);
}

void Brain::SetY(int y)
{
	brain->SetY(y);
}

int Brain::GetX()
{
	return brain->GetX();
}

int Brain::GetY()
{
	return brain->GetY();
}
