#include "pch.h"
#include "Threat.h"


Threat::Threat(Game_setup *passed_game_setup)
{
	game_setup = passed_game_setup;
	for (int i = 0; i < AMOUT_THREAT / 2; ++i)
	{
		virus[i] = new Sprite(game_setup->GetRenderer(), "image/virut-08.png", -1000, -1000, THREAT_WIDTH, THREAT_HEIGHT);
		rottenBrain[i] = new Sprite(game_setup->GetRenderer(), "image/bad_brain-07.png", -1000, -1000, THREAT_WIDTH, THREAT_HEIGHT);
	}
	timeCheck = SDL_GetTicks();
}


Threat::~Threat()
{
	for (int i = 0; i < AMOUT_THREAT / 2; ++i)
	{
		delete rottenBrain[i];
		delete virus[i];
	}
}

void Threat::RandomSpawnThreat(int i)
{
	spawnLocationY[i] = -(rand() % 3000);
	spawnLocationX[i] = rand() % (BORDER_RIGHT - BORDER_LEFT) + BORDER_LEFT;
}

void Threat::SpawnRottenBrain(int i)
{
	rottenBrain[i]->SetX(spawnLocationX[i]);
	rottenBrain[i]->SetY(spawnLocationY[i]);
}

void Threat::SpawnVirus(int i)
{
	virus[i]->SetX(spawnLocationX[i + AMOUT_THREAT / 2]);
	virus[i]->SetY(spawnLocationY[i + AMOUT_THREAT / 2]);
}

int Threat::GetRottenBrainX(int i)
{
	return rottenBrain[i]->GetX();
}

int Threat::GetRottenBrainY(int i)
{
	return rottenBrain[i]->GetY();
}

int Threat::GetVirusX(int i)
{
	return virus[i]->GetX();
}

int Threat::GetVirusY(int i)
{
	return virus[i]->GetY();
}

void Threat::Draw()
{
	for (int i = 0; i < AMOUT_THREAT / 2; ++i)
	{
		virus[i]->Draw();
		rottenBrain[i]->Draw();
	}
}

void Threat::Movement()
{
	if (timeCheck + TIME_SPACE < SDL_GetTicks())
	{
		for (int i = 0; i < AMOUT_THREAT / 2; ++i)
		{
			virus[i]->SetY(virus[i]->GetY() + BRAIN_SPEED);
			rottenBrain[i]->SetY(rottenBrain[i]->GetY() + BRAIN_SPEED);
		}
		timeCheck = SDL_GetTicks();
	}
}

