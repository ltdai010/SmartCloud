#include "pch.h"
#include "Menu.h"


Menu::Menu(Game_setup *passed_game_setup, std::string path)
{
	game_setup = passed_game_setup;
	menu = new Sprite(game_setup->GetRenderer(), path.c_str(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	start = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instruction = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	quit = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	instructionPage[0] = new Sprite(game_setup->GetRenderer(), "image/instruction-06.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	instructionPage[1] = new Sprite(game_setup->GetRenderer(), "image/instruction-09.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	instructionPage[2] = new Sprite(game_setup->GetRenderer(), "image/instruction-11.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	instructionPage[3] = new Sprite(game_setup->GetRenderer(), "image/instruction-10.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	back = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	next = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	click = new Game_music("audio/Click.wav", AUDIO);
	start->LoadText("Start game");
	instruction->LoadText("Instruction");
	quit->LoadText("Quit");
	back->LoadText("Back");
	next->LoadText("Next");
	start->SetSize(START_TEXT_WIDTH, START_TEXT_HEIGHT);
	instruction->SetSize(START_TEXT_WIDTH, START_TEXT_HEIGHT);
	quit->SetSize(START_TEXT_WIDTH/2, START_TEXT_HEIGHT);
	start->SetLocation(MENU_TEXT_X, 50);
	instruction->SetLocation(MENU_TEXT_X, 150);
	quit->SetLocation(MENU_TEXT_X, 250);
	mousePointX = 0;
	mousePointY = 0;
	back->SetColor(69, 29, 220);
	next->SetColor(69, 29, 220);
	back->SetSize(100, 100);
	back->SetLocation(750, 500);
	next->SetSize(100, 100);
	next->SetLocation(900, 500);
	currentPage = 0;
	nextPage = false;
	backPage = false;
}


Menu::~Menu()
{
	delete menu;
	delete start;
	delete instruction;
	delete quit;
	delete back;
	delete next;
	delete instructionPage[0];
	delete instructionPage[1];
	delete instructionPage[2];
	delete instructionPage[3];
}

void Menu::Draw()
{
	menu->Draw();
}

void Menu::DrawText()
{
	start->LoadText("Start game");
	instruction->LoadText("Instruction");
	quit->LoadText("Quit");
	start->RenderText();
	instruction->RenderText();
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
				click->PlayAudio();
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
				click->PlayAudio();
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
		quit->SetColor(255, 0, 0);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				click->PlayAudio();
				*select = Quit;
			}
		}
	}
	else
	{
		quit->SetColor(0, 0, 0);
	}
}

void Menu::CheckInstructionCommand(Selection* select)
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX >= 750 && mousePointX <= 850 && mousePointY >= 500 && mousePointY <= 600)
	{
		back->SetColor(140, 120, 226);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT && !backPage)
			{
				if (currentPage == 0)
				{
					click->PlayAudio();
					*select = Back;
				}
				else
				{
					click->PlayAudio();
					backPage = true;
					currentPage--;
				}
			}
		}
	}
	else
	{
		back->SetColor(69, 29, 220);
	}
	if (mousePointX >= 900 && mousePointX <= 1000 && mousePointY >= 500 && mousePointY <= 600)
	{
		next->SetColor(140, 120, 226);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT && currentPage < 3 && !nextPage)
			{
				click->PlayAudio();
				nextPage = true;
				++currentPage;
			}
		}
	}
	else
	{
		next->SetColor(69, 29, 220);
	}
	if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP)
	{
		if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			nextPage = false;
			backPage = false;
		}
	}
}

void Menu::PrintInstruction()
{
	instructionPage[currentPage]->Draw();
	back->LoadText("Back");
	next->LoadText("Next");
	back->RenderText();
	next->RenderText();
}
