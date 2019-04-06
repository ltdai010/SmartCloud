#include "pch.h"
#include "Menu.h"


Menu::Menu(Game_setup *passed_game_setup, std::string path)
{
	game_setup = passed_game_setup;
	menu = new Sprite(game_setup->GetRenderer(), path.c_str(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	start = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instruction = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	highScore = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	quit = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	start->LoadText("Start game");
	instruction->LoadText("Instruction");
	highScore->LoadText("High score");
	quit->LoadText("Quit");
	start->SetSize(START_TEXT_WIDTH, START_TEXT_HEIGHT);
	instruction->SetSize(START_TEXT_WIDTH, START_TEXT_HEIGHT);
	highScore->SetSize(START_TEXT_WIDTH, START_TEXT_HEIGHT);
	quit->SetSize(START_TEXT_WIDTH/2, START_TEXT_HEIGHT);
	start->SetLocation(MENU_TEXT_X, 50);
	instruction->SetLocation(MENU_TEXT_X, 150);
	highScore->SetLocation(MENU_TEXT_X, 250);
	quit->SetLocation(MENU_TEXT_X, 350);
	mousePointX = 0;
	mousePointY = 0;
}


Menu::~Menu()
{
	delete menu;
	delete start;
	delete instruction;
	delete highScore;
	delete quit;
}

void Menu::Draw()
{
	menu->Draw();
	start->LoadText("Start game");
	instruction->LoadText("Instruction");
	highScore->LoadText("High score");
	quit->LoadText("Quit");
	start->RenderText();
	instruction->RenderText();
	highScore->RenderText();
	quit->RenderText();
}

void Menu::CheckCommand(Selection *select)
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX > MENU_TEXT_X && mousePointX < MENU_TEXT_X + START_TEXT_WIDTH && mousePointY > 50 && mousePointY < 150)
	{
		start->SetColor(255,0,0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				*select = Start;
			}
		}
	}
	else
	{
		start->SetColor(0, 0, 0);
	}
	if (mousePointX > MENU_TEXT_X && mousePointX < MENU_TEXT_X + START_TEXT_WIDTH && mousePointY > 150 && mousePointY < 250)
	{
		instruction->SetColor(255, 0, 0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				*select = Instruction;
			}
		}
	}
	else
	{
		instruction->SetColor(0, 0, 0);
	}
	if (mousePointX > MENU_TEXT_X && mousePointX < MENU_TEXT_X + START_TEXT_WIDTH && mousePointY > 250 && mousePointY < 350)
	{
		highScore->SetColor(255, 0, 0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				*select = HighScore;
			}
		}
	}
	else
	{
		highScore->SetColor(0, 0, 0);
	}
	if (mousePointX > MENU_TEXT_X && mousePointX < MENU_TEXT_X + START_TEXT_WIDTH && mousePointY > 350 && mousePointY < 450)
	{
		quit->SetColor(255, 0, 0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				*select = Quit;
			}
		}
	}
	else
	{
		quit->SetColor(0, 0, 0);
	}
}