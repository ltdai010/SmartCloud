#pragma once
class Book
{
public:
	Book(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h, BookType type);
	~Book();
	void MoveDown();
	void Draw();
private:
	Sprite *book;
	long long int timeCheck;
	BookType bookType;
};

