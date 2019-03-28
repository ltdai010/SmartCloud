#pragma once
class Cloud
{
public:
	Cloud(Game_setup *game_setup, std::string path, int x, int y, int w, int h);
	~Cloud();
	void UpdateControl();
	void UpdateMovement();
	void Movement();
	void UpdateAnimation();
	void Draw();
private:
	Sprite* cloud;
	SDL_Event* game_event;
	long long int timeCheck;
	bool moveLeft;
	bool moveRight;
	bool preLeft;
	bool preRight;
};

