#include "pch.h"
#include "Main.h"


Main::Main(int screenWidth, int screenHeight, int cloudWidth, int cloudHeight)
{
	quit = false;
	game_setup = new Game_setup(&quit, screenWidth, screenHeight);
	background = new Sprite(game_setup->GetRenderer(), "image/background4.png", 0, 0, screenWidth, screenHeight);
	game_over_texture = new Sprite(game_setup->GetRenderer(), "image/game_over_board.jpg", 240, 125, 500, 350);
	game_over_sound = new Game_music("audio/game_over.wav", AUDIO);
	cloud = new Cloud(game_setup, "image/cloud.png", CLOUD_START_X, CLOUD_START_Y, cloudWidth, cloudHeight);
	food = new Food(game_setup);
	threat = new Threat(game_setup);
	saveScore = new SaveScore("save/save_game.txt");
	eat_rotten_brain_sound = new Game_music("audio/RottenBrain.wav", AUDIO);
	eat_virut_sound = new Game_music("audio/Virut.wav", AUDIO);
	scorePerBrain = SCORE_PER_BRAIN;
	for (int i = 0; i < HEALTH_POINT; ++i)
	{
		heart[i] = new Sprite(game_setup->GetRenderer(), "image/heart.png", HEART_X + i * HEART_WIDTH, HEART_Y, HEART_WIDTH, HEART_HEIGHT);
		heart[i]->SetAmountFrame(2, 1);
		heart[i]->SetCurrentFrame(0);
		heart[i]->PlayAnimation(0, 0, 0, 0);
	}
	score_text = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	high_score_text = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	score_tittle = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	high_score_tittle = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	game_quit = new Sprite(game_setup->GetRenderer(), "image/X.png", X_LOCATION_X, X_LOCATION_Y, X_SIZE_WIDTH, X_SIZE_HEIGHT);
	game_over = new Sprite(game_setup->GetRenderer(), "image/game_over.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	back_menu = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	back_menu->SetColor(69, 29, 220);
	back_menu->SetSize(100, 100);
	back_menu->SetLocation(900, 500);
	count_down = new Game_Text(game_setup, "font/FVF Fernando 08.ttf", 16);
	count_down->SetColor(244, 179, 66);
	count_down->SetSize(300, 150);
	count_down->SetLocation(465, 225);
	count_down->LoadText("READY");
	menu = new Menu(game_setup, "image/menu.jpg");
	black_background = new Sprite(game_setup->GetRenderer(), "image/black.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	backgroundSound = new Game_music("Audio/background.mp3", MUSIC);
	black_background->SetBlendMode(SDL_BLENDMODE_BLEND);
	black_background->SetAlpha(0);
	click_sound = new Game_music("Audio/Click.wav", AUDIO);
	score_text->SetColor(0, 0, 0);
	score_text->SetSize(150, 50);
	score_text->SetLocation(800, 50);
	high_score_text->SetColor(0, 0, 0);
	high_score_text->SetSize(150, 50);
	high_score_text->SetLocation(800, 100);
	score_tittle->SetColor(0, 0, 0);
	score_tittle->SetSize(80, 50);
	score_tittle->SetLocation(650, 50);
	high_score_tittle->SetColor(0, 0, 0);
	high_score_tittle->SetSize(75, 50);
	high_score_tittle->SetLocation(650, 100);
	for (int i = 0; i < 9; ++i)
	{
		hiScoreStr[i] = '0';
		scoreStr[i] = '0';
	}
	scoreStr[9] = '\0';
	hiScoreStr[9] = '\0';
	timeCheck = SDL_GetTicks();
	slowTime = SDL_GetTicks();
	score = 0;
	playMusic = true;
	slowDown = false;
	select = Uncommand;
	healthPoint = HEALTH_POINT;
	score_tittle->LoadText("Score:");
	high_score_tittle->LoadText("Best:");
	saveScore->ReadScore();
	bigger_sound = new Game_music("Audio/bigger.wav", AUDIO);
	revive_sound = new Game_music("Audio/Revive.wav", AUDIO);
	double_score_sound = new Game_music("Audio/Double Score.wav", AUDIO);
	countDown = 3;
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
	delete score_tittle;
	delete high_score_tittle;
	delete saveScore;
	delete game_over_texture;
	delete game_over_sound;
	delete click_sound;
	delete bigger_sound;
	delete revive_sound;
	delete double_score_sound;
}

void Main::GameLoop()
{
	FirstSetup();
	backgroundSound->PlayMusic();
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
		score_tittle->RenderText();
		high_score_tittle->RenderText();
		IntergerToString(score, scoreStr);
		IntergerToString(saveScore->GetScore(), hiScoreStr);
		score_text->LoadText(scoreStr);
		score_text->RenderText();
		high_score_text->LoadText(hiScoreStr);
		high_score_text->RenderText();
		game_setup->End();
	}
}

bool Main::EatenBrain(int i)
{
	if (cloud->GetX() + hitboxW >= food->GetBrainX(i) && cloud->GetX() <= food->GetBrainX(i) + BRAIN_WIDTH &&
		cloud->GetY() + hitboxH >= food->GetBrainY(i) && cloud->GetY() + 20 <= food->GetBrainY(i) + BRAIN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::EatenBook()
{
	if (cloud->GetX() + hitboxW >= food->GetBookX() && cloud->GetX() <= food->GetBookX() + BRAIN_WIDTH &&
		cloud->GetY() + hitboxH >= food->GetBookY() && cloud->GetY() + 20 <= food->GetBookY() + BRAIN_HEIGHT)
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
	if (cloud->GetX() + hitboxW >= threat->GetRottenBrainX(i) && cloud->GetX() <= threat->GetRottenBrainX(i) + BRAIN_WIDTH &&
		cloud->GetY() + hitboxH >= threat->GetRottenBrainY(i) && cloud->GetY() + 20 <= threat->GetRottenBrainY(i) + BRAIN_HEIGHT)
	{
		eat_rotten_brain_sound->PlayAudio();
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::EatenVirus(int i)
{
	if (cloud->GetX() + hitboxW >= threat->GetVirusX(i) && cloud->GetX() <= threat->GetVirusX(i) + BRAIN_WIDTH &&
		cloud->GetY() + hitboxH >= threat->GetVirusY(i) && cloud->GetY() + 20 <= threat->GetVirusY(i) + BRAIN_HEIGHT && !invincible)
	{
		slowDown = true;
		slowTime = SDL_GetTicks();
		eat_virut_sound->PlayAudio();
		return true;
	}
	else
	{
		return false;
	}
}

bool Main::Missed(int y)
{
	if (y >= 600)
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
	for (int i = 0; i < AMOUT_BRAIN + 1; ++i)
	{
		if (i < AMOUT_THREAT)
		{
			threat->RandomSpawnThreat(i);
		}
		food->RandomSpawnFood(i);
		if (i < AMOUT_BRAIN)
		{
			food->SpawnBrain(i);
		}
	}
	food->RandomBook();
	food->SpawnBook();
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
	cloud->SetSize(CLOUD_WIDTH, CLOUD_HEIGHT);
	cloud->SetCloudSpeed(1);
	hitboxW = CLOUD_WIDTH;
	hitboxH = CLOUD_HEIGHT;
	scorePerBrain = SCORE_PER_BRAIN;
	invincible = false;
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
		cloud->StopInBorder(true);
	}
	else
	{
		cloud->StopInBorder(false);
	}
	if (EatenBook())
	{
		SetCloudCondition();
		food->RandomSpawnFood(AMOUT_BRAIN);
		food->SpawnBook();
		food->RandomBook();
	}
	else if (Missed(food->GetBookY()))
	{
		food->RandomSpawnFood(AMOUT_BRAIN);
		food->RandomBook();
		food->SpawnBook();
	}
	for (int i = 0; i < AMOUT_BRAIN; ++i)
	{
		if (EatenBrain(i)) //if brain is eaten, respawn, +10 score
		{
			food->RandomSpawnFood(i);
			food->SpawnBrain(i);
			cloud->EatBrainChunk();
			score += scorePerBrain;
		}
		else if (Missed(food->GetBrainY(i)))//if brain is missed, respawn
		{
			food->RandomSpawnFood(i);
			food->SpawnBrain(i);
		}
		else if (i < AMOUT_THREAT / 2 && EatenRottenBrain(i) && !invincible)
		{
			BreakHeart(HEALTH_POINT - healthPoint);
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
		else if (i < AMOUT_THREAT / 2 && EatenVirus(i) && !invincible)
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
		if (doubleScoreCoolDown + SLOW_TIME <= SDL_GetTicks())
		{
			scorePerBrain = SCORE_PER_BRAIN;
		}
		if (bigSizeCoolDown + SLOW_TIME <= SDL_GetTicks())
		{
			cloud->SetSize(CLOUD_WIDTH, CLOUD_HEIGHT);
			hitboxH = CLOUD_WIDTH;
			hitboxW = CLOUD_HEIGHT;
			invincible = false;
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

void Main::SetCloudCondition()
{
	bookType = food->GetBookType();
	if (bookType == SIZE)
	{
		bigger_sound->PlayAudio();
		cloud->SetSize(CLOUD_WIDTH * 1.5, CLOUD_HEIGHT * 1.5);
		hitboxH = CLOUD_WIDTH * 1.5;
		hitboxW = CLOUD_HEIGHT * 1.5;
		invincible = true;
		bigSizeCoolDown = SDL_GetTicks();
	}
	else if (bookType == LIFE)
	{
		revive_sound->PlayAudio();
		if (healthPoint < 3)
		{
			++healthPoint;
			ReviveHeart(HEALTH_POINT - healthPoint);
		}
	}
	else if (bookType == DOUBLE_SCORE)
	{
		double_score_sound->PlayAudio();
		doubleScoreCoolDown = SDL_GetTicks();
		scorePerBrain = SCORE_PER_BRAIN * 2;
	}
}

void Main::IntergerToString(int passed_score, char string[])
{
	int i = 8;
	string[9] = '\0';
	while (passed_score > 0)
	{
		string[i] = passed_score % 10 + 48;
		passed_score = passed_score / 10;
		--i;
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
				click_sound->PlayAudio();
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
		DrawGameStartScreen();
		GameLoop();
		if (select == Game_Quit)
		{
			cloud->StopMoving();
			Mix_HaltMusic();
			DrawGameOverScreen();
			if (HighScore())
			{
				saveScore->SetScore(score);
				saveScore->WriteScore();
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

void Main::ReviveHeart(int i)
{
	heart[i]->SetCurrentFrame(0);
	heart[i]->PlayAnimation(0, 0, 0, 0);
}

void Main::CheckGameOverCommand()
{
	SDL_GetMouseState(&mousePointX, &mousePointY);
	if (mousePointX >= 900 && mousePointX <= 1000 && mousePointY >= 500 && mousePointY <= 600)
	{
		back_menu->SetColor(140, 120, 226);
		if (game_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_HaltChannel(-1);
			click_sound->PlayAudio();
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
	for (int i = 0; i < 9; ++i)
	{
		if (scoreStr[i] != '0')
		{
			length = 9 - i;
			break;
		}
	}
	for (int i = 9 - length; i < 9; ++i)
	{
		temp = temp + scoreStr[i];
	}
	score_text->SetSize(20 * length, 50);
	score_text->SetLocation(500, 300);
	score_text->LoadText(temp);
}

bool Main::HighScore()
{
	saveScore->ReadScore();
	if (score > saveScore->GetScore())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Main::DrawGameOverScreen()
{
	fadeOutTime = SDL_GetTicks();
	int alpha = 0;
	while (game_setup->GetMainEvent()->type != SDL_QUIT && select != Back)
	{
		game_setup->Begin();
		background->Draw();
		game_quit->Draw();
		DrawHeart();
		cloud->Draw();
		threat->Draw();
		food->Draw();
		score_tittle->RenderText();
		high_score_tittle->RenderText();
		score_text->LoadText(scoreStr);
		score_text->RenderText();
		high_score_text->LoadText(hiScoreStr);
		high_score_text->RenderText();
		black_background->SetAlpha(alpha);
		black_background->Draw();
		if (fadeOutTime + 10 < SDL_GetTicks() && alpha < 192)
		{
			alpha += 1;
			fadeOutTime = SDL_GetTicks();
			if (alpha == 192)
			{
				game_over_sound->PlayAudio();
			}
		}
		if(alpha > 191)
		{
			game_over_texture->Draw();
			CheckGameOverCommand();
			back_menu->LoadText("Back");
			CustomizeScoreStr();
			score_text->RenderText();
			back_menu->RenderText();
		}
		game_setup->End();
	}
}

void Main::DrawGameStartScreen()
{
	countDown = 3 + 1;
	count_down->LoadText("READY");
	count_down->SetSize(400, 150);
	count_down->SetLocation(340, 225);
	black_background->SetBlendMode(SDL_BLENDMODE_BLEND);
	black_background->SetAlpha(191);
	countDownTime = SDL_GetTicks();
	while (game_setup->GetMainEvent()->type != SDL_QUIT && countDown > 0)
	{
		game_setup->Begin();
		background->Draw();
		black_background->Draw();
		count_down->RenderText();
		game_setup->End();
		if (countDownTime + 1000 < SDL_GetTicks())
		{
			count_down->SetSize(75, 150);
			count_down->SetLocation(502, 225);
			char temp_count[2];
			temp_count[0] = countDown + 48 - 1;
			temp_count[1] = '\0';
			count_down->LoadText(temp_count);
			countDown--;
			countDownTime = SDL_GetTicks();
		}
	}
}
