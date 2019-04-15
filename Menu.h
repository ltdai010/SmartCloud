#pragma once
class Menu
{
public:
	Menu(Game_setup *passed_game_setup, std::string path);
	void Draw();
	void DrawText();
	void PrintInstruction();
	void CheckCommand(Selection *select);
	void CheckBack(Selection *select);
	~Menu();
private:
	Sprite *menu;
	Game_setup *game_setup;
	Game_Text *start;
	Game_Text *instruction;
	Game_Text *highScore;
	Game_Text *quit;
	Game_Text *instructionText1;
	Game_Text *instructionText2;
	Game_Text *instructionText3;
	Game_Text *back;
	Sprite *instructionBackground;
	int mousePointX;
	int mousePointY;
};

