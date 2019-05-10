#pragma once
class Cloud
{
public:
	Cloud(Game_setup *passed_game_setup, std::string path, int x, int y, int w, int h);
	~Cloud();
	void UpdateControl();
	void UpdateMovement();
	void Movement();
	void UpdateAnimation();
	void Draw();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	void SetSize(int w, int h);
	void StopInBorder(bool stop);
	void StopMoving();
	void SetCloudSpeed(double level);
	void EatBrainChunk();
private:
	Sprite* cloud;
	Game_setup* game_setup;
	Game_music* eatBrain;
	long long int timeCheck;
	bool moveLeft;
	bool moveRight;
	bool preLeft;
	bool preRight;
	bool stop;
	int cloudSpeed;
};
