#include "pch.h"
#include "Book.h"


Book::Book(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h)
{
	book = new Sprite(passed_game_setup->GetRenderer(), path, x, y, w, h);
	book->SetAmountFrame(3, 1);
}


Book::~Book()
{
	delete book;
}

void Book::MoveDown()
{
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		book->SetY(book->GetY() + BRAIN_SPEED);
		timeCheck = SDL_GetTicks();
	}
}

void Book::SetType(BookType type)
{
	bookType = type;
	if (type == SIZE)
	{
		book->SetCurrentFrame(2);
		book->PlayAnimation(2, 2, 0, 0);
	}
	else if (type == LIFE)
	{
		book->SetCurrentFrame(1);
		book->PlayAnimation(1, 1, 0, 0);
	}
	else if (type == DOUBLE_SCORE)
	{
		book->SetCurrentFrame(0);
		book->PlayAnimation(0, 0, 0, 0);
	}
}

BookType Book::GetBookType()
{
	return bookType;
}

void Book::Draw()
{
	book->Draw();
}

void Book::SetX(int x)
{
	book->SetX(x);
}

void Book::SetY(int y)
{
	book->SetY(y);
}

int Book::GetX()
{
	return book->GetX();
}

int Book::GetY()
{
	return book->GetY();
}
