#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


struct GameTextures {
    SDL_Texture* myBackground;
    SDL_Texture* Menu;
    SDL_Texture* GetReady;
    SDL_Texture* PlayingButton;
    SDL_Texture* HelloText;
    SDL_Texture* GameOver;
    SDL_Texture* ReplayButton;
    SDL_Texture* QuitButton;
    SDL_Texture* ScoreBoard;
    SDL_Texture* GoldMedal;
    SDL_Texture* SilverMedal;

};

struct ObjectTextures {
    SDL_Texture* FlappyBird0;
    SDL_Texture* FlappyBird1;
    SDL_Texture* FlappyBird2;
    vector <SDL_Texture*> FlappyBirdFrame;
    SDL_Texture* TopPipe;
    SDL_Texture* BotPipe;
    SDL_Texture* Clouds;
};







