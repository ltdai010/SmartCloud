#pragma once
class Food
{
public:
	Food(Game_setup *passed_game_setup);
	~Food();
	void RandomSpawnFood();
	void Movement();
	void SpawnFood();
	void Draw();

private:
	Brain* brain[10];
	Game_setup* game_setup;
	bool touchCloud[10];
	bool touchGround[10];
	int spawnLocationY[10];
	int spawnLocationX[10];
};

