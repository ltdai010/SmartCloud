#pragma once
class Brain
{
public:
	Brain(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h);
	~Brain();
	void MoveDown();
	void Draw();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
private:
	Sprite *brain;
	long long int timeCheck;
};

