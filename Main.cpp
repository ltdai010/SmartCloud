#include "pch.h"
#include "Main.h"


Main::Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight)
{
	quit = false;
	game_setup = new Game_setup(&quit, screenWidth, screenHeight);
	background = new Sprite(game_setup->GetRenderer(), "image/background.bmp", 0, 0, screenWidth, screenHeight);
	cloud = new Cloud(game_setup, "image/cloud.png", 200, 450, cloudWidth, cloudHeight);
	food = new Food(game_setup);
	score_text = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	menu = new Menu(game_setup, "image/menu.jpg");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to open sound device" << std::endl;
	}
	backgroundSound = Mix_LoadMUS("audio/background.mp3");
	eatBrain = Mix_LoadWAV("audio/EatBrain.wav");
	if (backgroundSound == NULL || eatBrain == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to load sound" << std::endl;
	}
	score_text->SetColor(0, 0, 0);
	score_text->SetSize(150, 50);
	score_text->SetLocation(650, 50);
	for (int i = 0; i < 10; ++i)
	{
		scoreStr[i] = '0';
	}
	timeCheck = SDL_GetTicks();
	score = 0;
	playMusic = true;
	select = Uncommand;
}


Main::~Main()
{
	delete game_setup;
	delete background;
	delete cloud;
	delete score_text;
	delete food;
	delete menu;
}

void Main::GameLoop()
{
	FirstSetup();
	PlayMusic(backgroundSound);
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_Volume(-1, MIX_MAX_VOLUME);
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
	if (cloud->GetX() + CLOUD_WIDTH >= food->GetBrainX(i) && cloud->GetX() <= food->GetBrainX(i) + BRAIN_WIDTH && 
		cloud->GetY() + CLOUD_HEIGHT  >= food->GetBrainY(i) && cloud->GetY() + 20 <= food->GetBrainY(i) + BRAIN_HEIGHT)
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
	if (CloudTouchBorder()) //if cloud touch border, it stops
	{
		cloud->Stop(true);
	}
	else
	{
		cloud->Stop(false);
	}
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		if (EatenBrain(i)) //if brain is eaten, respawn, +10 score
		{
			food->RandomSpawnFood(i);
			food->SpawnFood(i);
			PlayChunk(eatBrain);
			score += SCORE_PER_BRAIN;
		}
		else if (MissedBrain(i)) //if brain is missed, respawn
		{
			food->RandomSpawnFood(i);
			food->SpawnFood(i);
		}
	}
	UpdateMusic();
	if (playMusic)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
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

void Main::PlayMusic(Mix_Music* music)
{
	if (Mix_PlayMusic(music, -1) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to play sound" << std::endl;
	}
}

void Main::PlayChunk(Mix_Chunk* chunk)
{
	if (Mix_PlayChannel(-1, chunk, 0) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to play treasure sound" << std::endl;
	}
}

void Main::UpdateMusic()
{
	switch (game_setup->GetMainEvent()->type)
	{
	case SDL_KEYDOWN:
		switch (game_setup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_p:
			playMusic = false;
			break;
		case SDLK_o:
			playMusic = true;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void Main::StartMenu()
{
	while (select == Uncommand && game_setup->GetMainEvent()->type != SDL_QUIT)
	{
		game_setup->Begin();
		menu->CheckCommand(&select);
		menu->Draw();
		game_setup->End();
	}
	if (select == Start)
	{
		GameLoop();	
	}
	else if (select == Quit)
	{
		quit = true;
	}
}
