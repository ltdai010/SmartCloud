#include "pch.h"
#include "Sprite.h"


Sprite::Sprite(SDL_Renderer *passed_renderer, std::string path, int x, int y, int w, int h)
{
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, path.c_str());
	if (image == NULL)
	{
		std::cout << "Could not load image" << std::endl;
	}
	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;
	currentFrame = 0;
}


Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::SetAmountFrame(int x, int y)
{
	amount_Frame_X = x;
	amount_Frame_Y = y;
}

void Sprite::SetCurrentFrame(int x)
{
	currentFrame = x;
}

void Sprite::PlayAnimation(int beginFrame, int endFrame, int row, float speed)
{
	if (animationDelay + speed < SDL_GetTicks())
	{
		if (endFrame <= currentFrame)
		{
			currentFrame = beginFrame;
		}
		else
		{
			++currentFrame;
		}
		crop.x = currentFrame * (img_width / amount_Frame_X);
		crop.y = row * (img_height / amount_Frame_Y);
		crop.w = img_width / amount_Frame_X;
		crop.h = img_height / amount_Frame_Y;
		animationDelay = SDL_GetTicks();
	}
}

void Sprite::Draw()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
}


int Sprite::GetX()
{
	return rect.x;
}

int Sprite::GetY()
{
	return rect.y;
}

void Sprite::SetX(int x)
{
	rect.x = x;
}

void Sprite::SetY(int y)
{
	rect.y = y;
}

void Sprite::SetWidth(int w)
{
	rect.w = w;
}

void Sprite::SetHeight(int h)
{
	rect.h = h;
}
