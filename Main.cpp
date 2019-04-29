#include "pch.h"
#include "Main.h"


Main::Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight)
{
	quit = false;
	game_setup = new Game_setup(&quit, screenWidth, screenHeight);
	background = new Sprite(game_setup->GetRenderer(), "image/background4.png", 0, 0, screenWidth, screenHeight);
	cloud = new Cloud(game_setup, "image/cloud.png", CLOUD_START_X, CLOUD_START_Y, cloudWidth, cloudHeight);
	food = new Food(game_setup);
	threat = new Threat(game_setup);
	for (int i = 0; i < HEALTH_POINT; ++i)
	{
		heart[i] = new Sprite(game_setup->GetRenderer(), "image/heart.png", HEART_X + i * HEART_WIDTH, HEART_Y, HEART_WIDTH, HEART_HEIGHT);
		heart[i]->SetAmountFrame(2, 1);
		heart[i]->SetCurrentFrame(0);
		heart[i]->PlayAnimation(0, 0, 0, 0);
	}
	score_text = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	game_quit = new Sprite(game_setup->GetRenderer(), "image/X.png", X_LOCATION_X, X_LOCATION_Y, X_SIZE_WIDTH, X_SIZE_HEIGHT);
	game_over = new Sprite(game_setup->GetRenderer(), "image/game_over.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	back_menu = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	back_menu->SetColor(69, 29, 220);
	back_menu->SetSize(100, 100);
	back_menu->SetLocation(900, 500);
	menu = new Menu(game_setup, "image/menu.jpg");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to open sound device" << std::endl;
	}
	backgroundSound = Mix_LoadMUS("audio/background.mp3");
	if (backgroundSound == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		std::cout << "failed to load sound" << std::endl;
	}
	score_text->SetColor(0, 0, 0);
	score_text->SetSize(150, 50);
	score_text->SetLocation(800, 50);
	for (int i = 0; i < 10; ++i)
	{
		scoreStr[i] = '0';
	}
	timeCheck = SDL_GetTicks();
	slowTime = SDL_GetTicks();
	score = 0;
	playMusic = true;
	slowDown = false;
	select = Uncommand;
	healthPoint = 3;
}
Main::~Main()
{
	delete background;
	delete cloud;
	delete score_text;
	delete food;
	delete menu;
	for (int i = 0; i < HEALTH_POINT; ++i)
	{
		delete heart[i];
	}
	delete threat;
	delete game_quit;
	delete back_menu;
	delete game_over;
}

void Main::GameLoop()
{
	FirstSetup();
	PlayMusic(backgroundSound);
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_Volume(-1, MIX_MAX_VOLUME);
	while (!quit && game_setup->GetMainEvent()->type != SDL_QUIT && select != Game_Quit)
	{
		game_setup->Begin();
		background->Draw();
		game_quit->Draw();
		CheckQuit();
		UpdateCondition();
		DrawHeart();
		cloud->Draw();
		cloud->Movement();
		threat->Draw();
		threat->Movement();
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
		cloud->GetY() + CLOUD_HEIGHT >= food->GetBrainY(i) && cloud->GetY() + 20 <= food->GetBrainY(i) + BRAIN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::EatenRottenBrain(int i)
{
	if (cloud->GetX() + CLOUD_WIDTH >= threat->GetRottenBrainX(i) && cloud->GetX() <= threat->GetRottenBrainX(i) + BRAIN_WIDTH &&
		cloud->GetY() + CLOUD_HEIGHT >= threat->GetRottenBrainY(i) && cloud->GetY() + 20 <= threat->GetRottenBrainY(i) + BRAIN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::EatenVirus(int i)
{
	if (cloud->GetX() + CLOUD_WIDTH >= threat->GetVirusX(i) && cloud->GetX() <= threat->GetVirusX(i) + BRAIN_WIDTH &&
		cloud->GetY() + CLOUD_HEIGHT >= threat->GetVirusY(i) && cloud->GetY() + 20 <= threat->GetVirusY(i) + BRAIN_HEIGHT)
	{
		slowDown = true;
		slowTime = SDL_GetTicks();
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::Missed(int x)
{
	if (x >= 600)
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
		threat->RandomSpawnThreat(i);
		food->RandomSpawnFood(i);
		food->SpawnFood(i);
	}
	for (int i = 0; i < AMOUT_THREAT / 2; ++i)
	{
		threat->SpawnRottenBrain(i);
	}
	for (int i = 0; i < AMOUT_THREAT / 2; ++i)
	{
		threat->SpawnVirus(i);
	}
	for (int i = 0; i < HEALTH_POINT; ++i)
	{
		heart[i]->SetCurrentFrame(0);
		heart[i]->PlayAnimation(0, 0, 0, 0);
	}
	cloud->SetX(CLOUD_START_X);
	cloud->SetY(CLOUD_START_Y);
	healthPoint = HEALTH_POINT;
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
	for (int i = 0; i < HEALTH_POINT - healthPoint; ++i)
	{
		BreakHeart(i);
	}
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
			cloud->EatBrainChunk();
			score += SCORE_PER_BRAIN;
		}
		else if (Missed(food->GetBrainY(i)))//if brain is missed, respawn
		{
			food->RandomSpawnFood(i);
			food->SpawnFood(i);
		}
		else if (i < AMOUT_THREAT / 2 && EatenRottenBrain(i))
		{
			healthPoint--;
			if (healthPoint == 0)
			{
				select = Game_Quit;
			}
			threat->RandomSpawnThreat(i);
			threat->SpawnRottenBrain(i);
		}
		else if (i < AMOUT_THREAT / 2 && Missed(threat->GetRottenBrainY(i))) //if brain is missed, respawn
		{
			threat->RandomSpawnThreat(i);
			threat->SpawnRottenBrain(i);
		}
		else if (i < AMOUT_THREAT / 2 && EatenVirus(i))
		{
			threat->RandomSpawnThreat(i);
			threat->SpawnVirus(i);
		}
		else if (i < AMOUT_THREAT / 2 && Missed(threat->GetVirusY(i))) //if brain is missed, respawn
		{
			threat->RandomSpawnThreat(i);
			threat->SpawnVirus(i);
		}
		if (slowDown == true)
		{
			if (slowTime + SLOW_TIME >= SDL_GetTicks())
			{
				cloud->SetCloudSpeed(0.75);
			}
			else
			{
				cloud->SetCloudSpeed(1);
			}
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

void Main::CheckQuit()
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX >= X_LOCATION_X && mousePointX <= X_LOCATION_X + X_SIZE_WIDTH && mousePointY >= X_LOCATION_Y && mousePointY <= X_LOCATION_Y + X_SIZE_HEIGHT)
	{
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			if (game_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
			{
				select = Game_Quit;
			}
		}
	}
}

void Main::StartMenu()
{
	select = Uncommand;
	while (select == Uncommand && game_setup->GetMainEvent()->type != SDL_QUIT)
	{
		game_setup->Begin();
		menu->CheckCommand(&select);
		menu->Draw();
		menu->DrawText();
		game_setup->End();
	}
	if (select == Start)
	{
		GameLoop();
		if (select == Game_Quit)
		{
			Mix_PauseMusic();
			CustomizeScoreStr();
			while (game_setup->GetMainEvent()->type != SDL_QUIT && select != Back)
			{
				game_setup->Begin();
				game_over->Draw();
				CheckGameOverCommand();
				back_menu->LoadText("Back");
				score_text->RenderText();
				back_menu->RenderText();
				game_setup->End();
			}
			score = 0;
			for (int i = 0; i < 10; ++i)
			{
				scoreStr[i] = '0';
			}
			score_text->SetSize(150, 50);
			score_text->SetLocation(800, 50);
			StartMenu();
		}
	}
	else if (select == Instruction)
	{
		while (game_setup->GetMainEvent()->type != SDL_QUIT && select != Back)
		{
			game_setup->Begin();
			menu->CheckInstructionCommand(&select);
			menu->PrintInstruction();
			game_setup->End();
		}
		if (select == Back)
		{
			StartMenu();
		}
	}
	else if (select == Quit)
	{
		quit = true;
	}
}

void Main::DrawHeart()
{
	for (int i = 0; i < HEALTH_POINT; ++i)
	{
		heart[i]->Draw();
	}
}

void Main::BreakHeart(int i)
{
	heart[i]->SetCurrentFrame(1);
	heart[i]->PlayAnimation(1, 1, 0, 0);
}
void Main::CheckGameOverCommand()
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX >= 900 && mousePointX <= 1000 && mousePointY >= 500 && mousePointY <= 600)
	{
		back_menu->SetColor(140, 120, 226);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			select = Back;
		}
	}
	else
	{
		back_menu->SetColor(69, 29, 220);
	}
}

void Main::CustomizeScoreStr()
{
	int length = 1;
	std::string temp;
	for (int i = 0; i < 10; ++i)
	{
		if (scoreStr[i] != '0')
		{
			length = 10 - i;
			break;
		}
	}
	for (int i = 10 - length; i < 10; ++i)
	{
		temp = temp + scoreStr[i];
	}
	std::cout << "Score:" << temp << std::endl;
	score_text->SetSize(30 * length, 100);
	score_text->SetLocation(700, 270);
	score_text->LoadText(temp);
}
