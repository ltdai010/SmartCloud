#pragma once
class Book
{
public:
	Book(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h);
	~Book();
	void MoveDown();
	void SetType(BookType type);
	int GetX();
	int GetY();
	BookType GetBookType();
	void SetX(int x);
	void SetY(int y);
	void Draw();
private:
	Sprite *book;
	long long int timeCheck;
	BookType bookType;
};

