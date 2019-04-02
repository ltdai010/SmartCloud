#include "pch.h"
#include "Main.h"


Main::Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight)
{
	quit = false;
	game_setup = new Game_setup(&quit, screenWidth, screenHeight);
	background = new Sprite(game_setup->GetRenderer(), "background.bmp", 0, 0, screenWidth, screenHeight);
	cloud = new Cloud(game_setup, "cloud.png", 200, 450, cloudWidth, cloudHeight);
	food = new Food(game_setup);
	score_text = new Game_Text(game_setup, "FVF Fernando 08.ttf", 16);
	score_text->SetColor(0, 0, 0);
	score_text->SetSize(150, 50);
	score_text->SetLocation(650, 50);
	for (int i = 0; i < 10; ++i)
	{
		scoreStr[i] = '0';
	}
	timeCheck = SDL_GetTicks();
	score = 0;
}


Main::~Main()
{
	delete game_setup;
	delete background;
	delete cloud;
}

void Main::GameLoop()
{
	FirstSetup();
	while (!quit && game_setup->GetMainEvent()->type != SDL_QUIT)
	{
		game_setup->Begin();
		background->Draw();
		UpdateCondition();
		cloud->Draw();
		cloud->Movement();
		food->Draw();
		food->Movement();
		IntergerToString(score);
		score_text->LoadText(scoreStr);
		score_text->RenderText();

		game_setup->End();
	}
}

bool Main::EatenBrain(int i)
{
	if (cloud->GetX() + CLOUD_WIDTH >= food->GetBrainX(i) && cloud->GetX() <= food->GetBrainX(i) + BRAIN_WIDTH && cloud->GetY() + CLOUD_HEIGHT >= food->GetBrainY(i) && cloud->GetY() <= food->GetBrainY(i) + BRAIN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::MissedBrain(int i)
{
	if (food->GetBrainY(i) >= 600)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Main::FirstSetup()
{
	timeCheck = SDL_GetTicks();
	srand(time(NULL));
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		food->RandomSpawnFood(i);
		food->SpawnFood(i);
	}
}

bool Main::CloudTouchBorder()
{
	if (cloud->GetX() <= BORDER_LEFT || cloud->GetX() >= BORDER_RIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Main::UpdateCondition()
{
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		if (CloudTouchBorder()) //if cloud touch border, it stops
		{
			cloud->Stop(true);
		}
		if (EatenBrain(i)) //if brain is eaten, respawn, +10 score
		{
			food->RandomSpawnFood(i);
			food->SpawnFood(i);
			score += SCORE_PER_BRAIN;
		}
		else if (MissedBrain(i)) //if brain is missed, respawn
		{
			food->RandomSpawnFood(i);
			food->SpawnFood(i);
		}
	}
}

void Main::IntergerToString(int passed_score)
{
	int i = 9;
	while (passed_score > 0)
	{
		scoreStr[i] = passed_score % 10 + 48;
		passed_score = passed_score / 10;
		--i;
	}
}
