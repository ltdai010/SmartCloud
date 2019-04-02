#include "pch.h"
#include "Food.h"


Food::Food(Game_setup *passed_game_setup)
{
	game_setup = passed_game_setup;
	for (int i = 0; i < 10; ++i)
	{
		brain[i] = new Brain(game_setup, "brain.png", 300, -10000, BRAIN_WIDTH, BRAIN_HEIGHT);
	}
}


Food::~Food()
{
	delete game_setup;
	for (int i = 0; i < 10; ++i)
	{
		delete brain[i];
	}
}

void Food::RandomSpawnFood(int i)
{
	spawnLocationY[i] = -(rand() % 3000);
	spawnLocationX[i] = rand() % (BORDER_RIGHT - BORDER_LEFT)  + BORDER_LEFT;
}

void Food::SpawnFood(int i)
{
	brain[i]->SetX(spawnLocationX[i]);
	brain[i]->SetY(spawnLocationY[i]);
}

void Food::Draw()
{
	for (int i = 0; i < 10; ++i)
	{
		brain[i]->Draw();
	}
}

void Food::Movement()
{
	for (int i = 0; i < 10; ++i)
	{
		brain[i]->MoveDown();
	}
}

int Food::GetBrainX(int i)
{
	return brain[i]->GetX();
}

int Food::GetBrainY(int i)
{
	return brain[i]->GetY();
}

