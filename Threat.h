#pragma once
class Threat
{
public:
	Threat(Game_setup *passed_game_setup);
	~Threat();
	void RandomSpawnThreat(int i);
	void SpawnRottenBrain(int i);
	void SpawnVirus(int i);
	int GetRottenBrainX(int i);
	int GetRottenBrainY(int i);
	int GetVirusX(int i);
	int GetVirusY(int i);
	void Movement();
	void Draw();
private:
	Game_setup* game_setup;
	Sprite *virus[AMOUT_THREAT/2];
	Sprite *rottenBrain[AMOUT_THREAT/2];
	int spawnLocationY[AMOUT_THREAT];
	int spawnLocationX[AMOUT_THREAT];
	long long int timeCheck;
};

