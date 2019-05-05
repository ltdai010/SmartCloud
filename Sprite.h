#pragma once
class Sprite
{
public:
	Sprite(SDL_Renderer *passed_renderer, std::string path, int x, int y, int w, int h);
	~Sprite();
	void Draw();
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int w);
	void SetHeight(int h);
	void SetAmountFrame(int x, int y);
	void SetCurrentFrame(int x);
	void PlayAnimation(int beginFrame, int endFrame, int row, float speed);
	int GetX();
	int GetY();
private:
	SDL_Renderer *renderer;
	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;
	int img_width;
	int img_height;
	int amount_Frame_X;
	int amount_Frame_Y;
	long long int animationDelay;
	int currentFrame;
};
