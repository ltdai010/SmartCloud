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
		cloud->Movement();
		cloud->Draw();
		food->Movement();
		food->Draw();
		score_text->LoadText("Smart Cloud");
		score_text->RenderText();

		game_setup->End();
	}
}

bool Main::EatenBrain(int i)
{
	if (cloud->GetX() + CLOUD_WIDTH >= food->GetBrainX(i) && cloud->GetX() <= food->GetBrainX(i) + BRAIN_WIDTH)
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
