#pragma once
class Menu
{
public:
	Menu(Game_setup *passed_game_setup, std::string path);
	void Draw();
	void CheckCommand(Selection *select);
	~Menu();
private:
	Sprite *menu;
	Game_setup *game_setup;
	Game_Text *start;
	Game_Text *instruction;
	Game_Text *highScore;
	Game_Text *quit;
	int mousePointX;
	int mousePointY;
};

