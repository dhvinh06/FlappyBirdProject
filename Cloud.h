#pragma once
#include <iostream>
#include <vector>
#include "graphics.h"
#include "Textures.h"
#include "GameState.h"

using namespace std;


struct Cloudsindex {
    int speed = 2;
    int width = 200;
    int height = 200;
    int Xposition = 1920 ;
    int Yposition = rand() % 300;
    int distance = 500;
};

void CloudUpdate(Graphics& graphics, vector <Cloudsindex>& CloudsArray, ObjectTextures& objecttextures) {
    if (CloudsArray.front().Xposition < 0) {
        CloudsArray.erase(CloudsArray.begin());
    }
    if (CloudsArray.back().Xposition < SCREEN_WIDTH - CloudsArray.back().distance) {
        Cloudsindex newcloud;
        CloudsArray.push_back(newcloud);
    }for (auto& cloud : CloudsArray) {
        cloud.Xposition -= cloud.speed;
        graphics.renderTexture(objecttextures.Clouds, cloud.Xposition, cloud.Yposition, cloud.width, cloud.width);
    }
}

