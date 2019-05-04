#include "pch.h"
#include "SaveScore.h"


SaveScore::SaveScore(std::string saveFile)
{
	this->saveFile = saveFile;
	readScore = new std::fstream(saveFile);
	writeScore = new std::ofstream(saveFile, std::ios::in | std::ios::out);
}


SaveScore::~SaveScore()
{
	delete readScore;
	delete writeScore;
}

void SaveScore::WriteScore()
{
	writeScore = new std::ofstream(saveFile, std::ios::in | std::ios::out);
	*writeScore << score;
	std::cout << score;
	writeScore->close();
}

void SaveScore::ReadScore()
{
	readScore = new std::fstream(saveFile);
	*readScore >> score;
	readScore->close();
}

int SaveScore::GetScore()
{
	return score;
}

void SaveScore::SetScore(int path_score)
{
	score = path_score;
}