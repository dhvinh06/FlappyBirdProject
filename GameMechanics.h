#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include <vector>
#include "graphics.h"
#include "Textures.h"
#include "Pipe.h"
#include "Bird.h"
#include "Cloud.h"
#include "GameState.h"
using namespace std;

void ZoomAnimation (Graphics &graphics,GameTextures & gametextures,SDL_Texture * Insert,int width,int height){
    int alpha = 255;
    int widthincrease = width/20;
    int heightincrease = height/20;
    while (alpha >0){
            SDL_SetTextureAlphaMod(Insert,alpha);
            graphics.prepareScene(gametextures.myBackground);
            graphics.renderTexture (Insert,(SCREEN_WIDTH-width)/2,(SCREEN_HEIGHT-height)/2,width,height);
            graphics.presentScene();
            width+=widthincrease;
            height+=heightincrease;
            alpha -=5;
      SDL_Delay(15);
    }SDL_SetTextureAlphaMod(Insert,255);

}
void LobbyUpdate(Graphics& graphics, GameTextures& gametextures, ObjectTextures& objecttextures, Bird& bird, vector <Cloudsindex>& CloudsArray) {
    if (bird.FlappyBirdY > SCREEN_HEIGHT / 2) {
        bird.Velocity = bird.Jump;
    }graphics.renderTexture(gametextures.Menu, (SCREEN_WIDTH - 1000) / 2, (SCREEN_HEIGHT - 333) / 2, 1000, 333);
    graphics.renderTexture(gametextures.PlayingButton, (SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 120) / 2 + 250, 300, 120);
    graphics.renderTexture(gametextures.QuitButton, 200, 120, 50, 50);

    CloudUpdate(graphics, CloudsArray, objecttextures);
    BirdUpdate(graphics, bird, objecttextures);

    graphics.presentScene();
    SDL_Delay(DelayValue * 2);
}
void CheckCollision(Graphics& graphics, Bird& bird, vector <Pipe>& PipeArray, ObjectTextures& objecttextures) {
    for (auto& pipe : PipeArray) {
        if (pipe.Right < bird.FlappyBirdX && pipe.pass != true) {
            Score++;
            pipe.pass = true;
        }
        if (bird.Bot > GroundLevel) {
            bird.Velocity=-1;
            Game_Over = true;
            return;
        }if (bird.Right >= pipe.x && bird.FlappyBirdX <= pipe.Right) {
            if (bird.FlappyBirdY<pipe.gapY || bird.Bot>pipe.Bot) {
                bird.Velocity=-1;
                Game_Over = true;
                return;
            }
        }
    }
}

void GameReset(Bird& bird, vector <Pipe>& PipeArray, vector <Cloudsindex>& CloudsArray) {
    Score = 0;
    Frame = 0;
    Game_Over = false;
    Game_Overendered=false;
    PipeArray.clear();
    Pipe NewPipe;
    PipeArray.push_back(NewPipe);
    Cloudsindex newcloud;
    CloudsArray.clear();
    CloudsArray.push_back(newcloud);
    bird.FlappyBirdY = 350;
    bird.Velocity = 0;
    bird.Right = bird.FlappyBirdX + bird.BirdWidth;
    bird.Bot = bird.FlappyBirdY + bird.BirdHeight;
}
