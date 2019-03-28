#pragma once
class Sprite
{
public:
	Sprite(Game_setup *game_setup, std::string path, int x, int y, int w, int h);
	~Sprite();
	void Draw();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
private:
	SDL_Event *game_event;
	SDL_Renderer *renderer;
	SDL_Texture* image;
	SDL_Rect rect;
};

