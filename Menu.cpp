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
	instructionText1 = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instructionText2 = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instructionText3 = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	back = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instructionBackground = new Sprite(game_setup->GetRenderer(), "image/instructor_background-06.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
	instructionText1->SetSize(600, 100);
	instructionText2->SetSize(400, 100);
	instructionText3->SetSize(600, 100);
	instructionText1->SetColor(0, 255, 255);
	instructionText2->SetColor(0, 255, 255);
	instructionText3->SetColor(0, 255, 255);
	instructionText1->SetLocation(100, 100);
	instructionText2->SetLocation(100, 200);
	instructionText3->SetLocation(100, 300);
	back->SetSize(100, 100);
	back->SetLocation(800, 400);
}


Menu::~Menu()
{
	delete menu;
	delete start;
	delete instruction;
	delete highScore;
	delete quit;
	delete instructionText1;
	delete instructionText2;
	delete instructionText3;
}

void Menu::Draw()
{
	menu->Draw();
}

void Menu::DrawText()
{
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

void Menu::CheckBack(Selection* select)
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX >= 800 && mousePointX <= 900 && mousePointY >= 400 && mousePointY <= 500)
	{
		back->SetColor(255, 0, 0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				*select = Back;
			}
		}
	}
	else
	{
		back->SetColor(0, 0, 0);
	}
}

void Menu::PrintInstruction()
{
	instructionBackground->Draw();
	instructionText1->LoadText("- Press A to move left, D to move right");
	instructionText2->LoadText("- Each Brain gains 10 score");
	instructionText3->LoadText("- If you hit the rotten brain 3 times, Game over!");
	instructionText1->RenderText();
	instructionText2->RenderText();
	instructionText3->RenderText();
	back->LoadText("Back");
	back->RenderText();
}
