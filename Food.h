#pragma once
class Food
{
public:
	Food(Game_setup *passed_game_setup);
	~Food();
	void RandomSpawnFood(int i);
	void Movement();
	void SpawnFood(int i);
	void Draw();
	int GetBrainX(int i);
	int GetBrainY(int i);

private:
	Brain* brain[AMOUT_BRAIN];
	Game_setup* game_setup;
	int spawnLocationY[AMOUT_BRAIN];
	int spawnLocationX[AMOUT_BRAIN];
};

