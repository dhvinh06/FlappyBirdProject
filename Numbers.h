#pragma once
#include <vector>
#include "graphics.h"
#include "GameMechanics.h"
#include "Textures.h"
#include "GameState.h"
using namespace std;


struct Numbers {
    int width = 50;
    int height = 75;
};

struct ScoreBoardNumbers {
    int width =18;
    int height =27;

};

vector <SDL_Texture*> loadingNumbersTexture(Graphics& graphics) {
    vector <SDL_Texture*>numbers;
    for (int i = 0;i < 10;i++) {
        string name = to_string(i) + ".png";
        SDL_Texture* numberstexture = graphics.loadTexture(name.c_str());
        numbers.push_back(numberstexture);
    }
    return numbers;
}

void PrintingScore(Graphics& graphics, vector <SDL_Texture*> loadingNumbersTexture, Numbers &numbers) {
    string convert = to_string(Score);
    int totalwidth = numbers.width * convert.size();
    int XofNumbers = SCREEN_WIDTH / 2 - totalwidth / 2;

    for (int i = 0;i < convert.size();i++) {
        int ChuSo = convert[i] - '0';
        int XofNumbers = SCREEN_WIDTH / 2 - totalwidth / 2 + i * numbers.width;
        graphics.renderTexture(loadingNumbersTexture[ChuSo], XofNumbers, SCREEN_HEIGHT / 2 - 200, numbers.width, numbers.height);
    }
}

void countdown(Graphics& graphics, Numbers& numbers, vector <SDL_Texture*>loadingNumbersTexture, GameTextures & gametextures) {
    int count = 5;
    while (count >= 0) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {

        }
        graphics.prepareScene(gametextures.myBackground);
        if (count==5){
            if (Restart){
                ZoomAnimation(graphics,gametextures,gametextures.GameOver,619,170);
            }else {
                ZoomAnimation(graphics,gametextures,gametextures.Menu,1000,333);
            }
        }
        else if (count == 4) {
            graphics.renderTexture(gametextures.GetReady, (SCREEN_WIDTH - 572) / 2, (SCREEN_HEIGHT - 184) / 2, 572, 184);
            ZoomAnimation (graphics,gametextures,gametextures.GetReady,572,184);
        }
        else {
            graphics.renderTexture(loadingNumbersTexture[count], (SCREEN_WIDTH - numbers.width) / 2, (SCREEN_HEIGHT - numbers.height) / 2, numbers.width, numbers.height);
            ZoomAnimation (graphics,gametextures,loadingNumbersTexture[count],numbers.width,numbers.height);
        }graphics.presentScene();
        count--;
        SDL_Delay(235);
    }
}

void PrintingScoreBoard (Graphics &graphics,ScoreBoardNumbers & scoreboardnumbers,GameTextures & gametextures,vector<SDL_Texture*> &loadingNumbersTexture){
    if (Score>9&& Score <20){
            graphics.renderTexture (gametextures.SilverMedal,(SCREEN_WIDTH-269)/2,(SCREEN_HEIGHT-139)/2-180,269,139);
    }else if (Score>19){
            graphics.renderTexture (gametextures.GoldMedal,(SCREEN_WIDTH-269)/2,(SCREEN_HEIGHT-139)/2-180,269,139);
    }else {
            graphics.renderTexture (gametextures.ScoreBoard,(SCREEN_WIDTH-269)/2,(SCREEN_HEIGHT-139)/2-180,269,139);
    }

    string convert1 = to_string(Score);
    string convert2 = to_string (HighestScore);
    int totalwidth1 = scoreboardnumbers.width * convert1.size();
    int totalwidth2 = scoreboardnumbers.width * convert2.size();


    for (int i = 0;i < convert1.size();i++) {
        int ChuSo = convert1[i] - '0';
        int XofNumbers =1045 - totalwidth1 / 2 + i * scoreboardnumbers.width;
        graphics.renderTexture(loadingNumbersTexture[ChuSo], XofNumbers, SCREEN_HEIGHT / 2 - 210, scoreboardnumbers.width, scoreboardnumbers.height);
    }for (int i = 0;i < convert2.size();i++) {
        int ChuSo = convert2[i] - '0';
        int XofNumbers =1045 - totalwidth2 / 2 + i * scoreboardnumbers.width;
        graphics.renderTexture(loadingNumbersTexture[ChuSo], XofNumbers, SCREEN_HEIGHT / 2 - 160, scoreboardnumbers.width, scoreboardnumbers.height);
    }


}








