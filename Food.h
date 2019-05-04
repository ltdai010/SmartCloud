#pragma once
class Food
{
public:
	Food(Game_setup *passed_game_setup);
	~Food();
	void RandomSpawnFood(int i);
	void RandomBook();
	void Movement();
	void SpawnBrain(int i);
	void SpawnBook();
	void Draw();
	int GetBrainX(int i);
	int GetBrainY(int i);
	BookType GetBookType();
	int GetBookX();
	int GetBookY();
private:
	Brain* brain[AMOUT_BRAIN];
	Book* book;
	Game_setup* game_setup;
	int spawnLocationY[AMOUT_BRAIN + 1];
	int spawnLocationX[AMOUT_BRAIN + 1];
	int type;
};

