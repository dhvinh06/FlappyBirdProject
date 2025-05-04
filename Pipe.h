#pragma once
#include <vector>
#include "GameState.h"
#include "Textures.h"
#include "graphics.h"

using namespace std;


struct Pipe {
    int x = SCREEN_WIDTH - 200;
    int width = 100;
    int speed = 10;
    int Pipe_Distance = 700;
    int GapHeight = 350;
    int gapY = rand() % (SCREEN_HEIGHT - GapHeight - 300) + 150;
    bool pass = false;
    int Right = x + width;
    int Bot = gapY + GapHeight;
};

void PipeUpdate(Graphics& graphics, vector <Pipe>& PipeArray, ObjectTextures& objecttextures) {
    for (auto& pipe : PipeArray) {
        pipe.Right = pipe.x + pipe.width;
        pipe.Bot = pipe.gapY + pipe.GapHeight;
        pipe.x -= pipe.speed + Score / 5;
        graphics.renderTexture(objecttextures.TopPipe, pipe.x, pipe.gapY - 800, pipe.width, 800);
        graphics.renderTexture(objecttextures.BotPipe, pipe.x, pipe.gapY + pipe.GapHeight, pipe.width, 800);
    }
    if (PipeArray.back().x < SCREEN_WIDTH - PipeArray.back().Pipe_Distance) {
        Pipe NewPipe;
        PipeArray.push_back(NewPipe);
    }
    if (PipeArray.front().x < 0) {
        PipeArray.erase(PipeArray.begin());
    }
}
