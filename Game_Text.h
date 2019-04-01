#pragma once
class Game_Text
{
public:
	Game_Text(Game_setup *game_setup, std::string path, int textSize);
	~Game_Text();
	void RenderText();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetSize(int width, int height);
	void SetLocation(int x, int y);
	void LoadText(std::string path);
private:
	TTF_Font *font;
	SDL_Color color;
	SDL_Surface *text_surface;
	SDL_Texture *text;
	SDL_Rect rect;
	Game_setup *game_setup;
};

