#include "pch.h"
#include "Food.h"


Food::Food(Game_setup *passed_game_setup)
{
	game_setup = passed_game_setup;
	book = new Book(game_setup, "image/book.png", 300, -10000, BRAIN_WIDTH, BRAIN_HEIGHT);
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		brain[i] = new Brain(game_setup, "image/brain.png", 300, -10000, BRAIN_WIDTH, BRAIN_HEIGHT);
	}
	int type = 0;
}


Food::~Food()
{
	delete game_setup;
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		delete brain[i];
	}
	delete book;
}

void Food::RandomSpawnFood(int i)
{
	spawnLocationY[i] = -(rand() % 3000);
	spawnLocationX[i] = rand() % (BORDER_RIGHT - BORDER_LEFT)  + BORDER_LEFT;
}

void Food::RandomBook()
{
	type = rand() % 3;
	if (type == 0)
	{
		book->SetType(SIZE);
	}
	else if (type == 1)
	{
		book->SetType(LIFE);
	}
	else if(type == 2)
	{
		book->SetType(DOUBLE_SCORE);
	}
}

void Food::SpawnBrain(int i)
{
	brain[i]->SetX(spawnLocationX[i]);
	brain[i]->SetY(spawnLocationY[i]);
}

void Food::SpawnBook()
{
	book->SetX(spawnLocationX[AMOUT_BRAIN]);
	book->SetY(spawnLocationY[AMOUT_BRAIN]);
}

void Food::Draw()
{
	for (int i = 0; i < 10; ++i)
	{
		brain[i]->Draw();
	}
	book->Draw();
}

void Food::Movement()
{
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		brain[i]->MoveDown();
	}
	book->MoveDown();
}

int Food::GetBrainX(int i)
{
	return brain[i]->GetX();
}

int Food::GetBrainY(int i)
{
	return brain[i]->GetY();
}

int Food::GetBookX()
{
	return book->GetX();
}

int Food::GetBookY()
{
	return book->GetY();
}

BookType Food::GetBookType()
{
	return book->GetBookType();
}

