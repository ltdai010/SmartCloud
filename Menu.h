#pragma once
class Menu
{
public:
	Menu(Game_setup *passed_game_setup, std::string path);
	void Draw();
	void DrawText();
	void PrintInstruction();
	void CheckCommand(Selection *select);
	void CheckInstructionCommand(Selection *select);
	~Menu();
private:
	Sprite *menu;
	Game_setup *game_setup;
	Game_Text *start;
	Game_Text *instruction;
	Game_Text *quit;
	Game_Text *next;
	Game_Text *back;
	Game_music *click;
	Sprite *instructionPage[4];
	int currentPage;
	int mousePointX;
	int mousePointY;
	bool nextPage;
	bool backPage;
};

