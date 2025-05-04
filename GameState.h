#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const char* WINDOW_TITLE = "Flappy Bird";
const int DelayValue = 20;
const int GroundLevel = 860;
int Score = 0;
int HighestScore =0;
int Frame =0;


bool Running = false;
bool Game_Over = false;
bool Lobby = true;
bool QuitGame = false;
bool Restart = false;
bool Game_Overendered = false;




