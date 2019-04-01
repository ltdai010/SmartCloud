#include "pch.h"
#include "Book.h"


Book::Book(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h, BookType type)
{
	book = new Sprite(passed_game_setup->GetRenderer(), path, x, y, w, h);
	bookType = type;
}


Book::~Book()
{
	delete book;
}

void Book::MoveDown()
{
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		book->SetX(book->GetX() - ClOUD_SPEED * 2);
		timeCheck = SDL_GetTicks();
	}
}

void Book::Draw()
{
	book->Draw();
}


