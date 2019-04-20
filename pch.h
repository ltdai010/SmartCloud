// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#define SCREEN_WIDTH 1081
#define SCREEN_HEIGHT 600
#define AMOUT_BRAIN 10
#define AMOUT_THREAT 10
#define CLOUD_START_X 200
#define CLOUD_START_Y 450
#define CLOUD_WIDTH 100
#define CLOUD_HEIGHT 100
#define BRAIN_WIDTH 50
#define BRAIN_HEIGHT 50
#define THREAT_WIDTH 50
#define THREAT_HEIGHT 50
#define ClOUD_SPEED 3
#define BRAIN_SPEED 2
#define TIME_SPACE 10 
#define CLOUD_FRAME_X 2
#define CLOUD_FRAME_Y 2
#define BORDER_LEFT 100
#define BORDER_RIGHT 800
#define SPAWN_TIME_SPACE 1000
#define SCORE_PER_BRAIN 10
#define MENU_TEXT_X 850
#define START_TEXT_WIDTH 200
#define START_TEXT_HEIGHT 100
#define X_SIZE_WIDTH 40
#define X_SIZE_HEIGHT 40
#define X_LOCATION_X 1000
#define X_LOCATION_Y 20
#define HEALTH_POINT 3
#define HEART_WIDTH 40
#define HEART_HEIGHT 40
#define HEART_X 800
#define HEART_Y 20
#define SLOW_TIME 5000
enum BookType
{
	SIZE,
	MAGNET,
	DOUBLESCORE
};
enum Selection
{
	Uncommand,
	Start,
	Instruction,
	HighScore,
	Quit,
	Back,
	Game_Quit
};
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "Game_setup.h"
#include "Sprite.h"
#include "Game_Text.h"
#include "Cloud.h"
#include "Brain.h"
#include "Book.h"
#include "Food.h"
#include "Threat.h"
#include "Menu.h"
#include "Main.h"






// TODO: add headers that you want to pre-compile here

#endif //PCH_H
