#pragma once
class SaveScore
{
public:
	SaveScore(std::string saveFile);
	~SaveScore();
	void WriteScore();
	void ReadScore();
	int GetScore();
	void SetScore(int path_score);
private:
	std::ofstream *writeScore;
	std::fstream *readScore;
	std::string saveFile;
	int score;
};

