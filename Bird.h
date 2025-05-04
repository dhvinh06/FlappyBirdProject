#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "graphics.h"
#include "Textures.h"
#include "Pipe.h"
using namespace std;



struct Bird {
    int const BirdWidth = 126;
    int const BirdHeight = 90;
    int FlappyBirdX = 350;
    int FlappyBirdY = 350;
    int Right = FlappyBirdX + BirdWidth;
    int Bot = FlappyBirdY + BirdHeight;
    int Velocity = 0;
    const int Jump = -15;
    const int Gravity = 1;
};


void BirdUpdate(Graphics& graphics, Bird& bird, ObjectTextures& objecttextures) {
    bird.Right = bird.FlappyBirdX + bird.BirdWidth;
    bird.Bot = bird.FlappyBirdY + bird.BirdHeight;
    if (bird.FlappyBirdY < 100) {
                bird.FlappyBirdY = 100;
                bird.Velocity = 0;
                return;
            }
    bird.FlappyBirdY += bird.Velocity;
    bird.Velocity += bird.Gravity;
    graphics.renderTexture(objecttextures.FlappyBirdFrame[Frame % (objecttextures.FlappyBirdFrame.size())], bird.FlappyBirdX, bird.FlappyBirdY, bird.BirdWidth, bird.BirdHeight);
    Frame++;
}

