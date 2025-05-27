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
#include "Numbers.h"
#include "GameState.h"
#include "GameMechanics.h"

using namespace std;





void UpdateGame(Graphics& graphics, GameTextures& gametextures, ObjectTextures& objecttextures, Bird& bird, vector <Pipe>& PipeArray, Numbers &numbers, vector <SDL_Texture*> &LoadedNumbersTexture, vector <Cloudsindex>& CloudsArray) {
    graphics.prepareScene(gametextures.myBackground);

    CheckCollision(graphics, bird, PipeArray, objecttextures);
    CloudUpdate(graphics, CloudsArray, objecttextures);
    PipeUpdate(graphics, PipeArray, objecttextures);

    BirdUpdate(graphics, bird, objecttextures);
    PrintingScore(graphics,LoadedNumbersTexture ,numbers);
    graphics.renderTexture(gametextures.QuitButton, 200, 120, 50, 50);

    graphics.presentScene();
    SDL_Delay(DelayValue);
}




int main(int argc, char* argv[]) {

    Graphics graphics;
    GameTextures gametextures;
    ObjectTextures objecttextures;
    Numbers numbers;
    ScoreBoardNumbers scoreboardnumbers;
    Bird bird;
    Pipe pipe;
    Cloudsindex cloud;

    SDL_Event event;
    graphics.init();
    srand(time(0));

    Mix_Music *ThemeSong = graphics.loadMusic("ThemeSong.mp3");
    graphics.play(ThemeSong);
    Mix_Chunk *Die = Mix_LoadWAV("die.wav");
    Mix_Chunk *Jump = Mix_LoadWAV("swoosh.wav");

    vector <SDL_Texture*> LoadedNumbersTexture = loadingNumbersTexture(graphics);
    vector <Pipe> PipeArray;
    PipeArray.push_back(pipe);
    vector <Cloudsindex> CloudsArray;
    CloudsArray.push_back(cloud);

    gametextures.myBackground = graphics.loadTexture("background_and_road.png");
    graphics.prepareScene(gametextures.myBackground);

    gametextures.Menu = graphics.loadTexture("Menu.png");
    gametextures.GameOver = graphics.loadTexture("Game_Over.png");
    gametextures.GetReady = graphics.loadTexture("GetReady.png");
    gametextures.PlayingButton = graphics.loadTexture("Playing_Button.png");
    gametextures.ReplayButton = graphics.loadTexture("Replay_Button.png");
    gametextures.QuitButton = graphics.loadTexture("Quit_Button.png");
    gametextures.ScoreBoard = graphics.loadTexture ("ScoreBoard.png");
    gametextures.GoldMedal = graphics.loadTexture ("GoldMedal.png");
    gametextures.SilverMedal = graphics.loadTexture ("SilverMedal.png");

    objecttextures.FlappyBird0 = graphics.loadTexture("FlappyBird0.png");
    objecttextures.FlappyBird1 = graphics.loadTexture("FlappyBird1.png");
    objecttextures.FlappyBird2 = graphics.loadTexture("FlappyBird2.png");

    objecttextures.FlappyBirdFrame.push_back(objecttextures.FlappyBird0);
    objecttextures.FlappyBirdFrame.push_back(objecttextures.FlappyBird1);
    objecttextures.FlappyBirdFrame.push_back(objecttextures.FlappyBird2);

    objecttextures.TopPipe = graphics.loadTexture("FlappyBird_Top_Pipe.png");
    objecttextures.BotPipe = graphics.loadTexture("FlappyBird_Bottom_Pipe.png");
    objecttextures.Clouds = graphics.loadTexture("Clouds.png");

    Running = true;
    SDL_Event MouseEvent;
    int x, y;

    while (Running) {
        if (HighestScore <Score){
            HighestScore=Score;
        }
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&MouseEvent);
        if (MouseEvent.type == SDL_MOUSEBUTTONDOWN) {
            if (x > 200 && x < 250 && y>120 && y < 170) {
                QuitGame = true;
                break;
            }if (Lobby) {
                if (x > 810 && x < 1110 && y>730 && y < 850) {
                    Lobby = false;
                    GameReset(bird, PipeArray, CloudsArray);
                    countdown(graphics, numbers, LoadedNumbersTexture, gametextures);
                }
            }if (Game_Over) {
                if (x > 910 && x < 1010 && y>640 && y < 740) {
                    Restart = true;
                }
            }
        }
        if (Lobby) {
            graphics.prepareScene(gametextures.myBackground);
            LobbyUpdate(graphics, gametextures, objecttextures, bird, CloudsArray);
        }
        else if (Game_Over) {
            if (Game_Overendered!=true){
                Mix_PauseMusic();
                Mix_PlayChannel(-1, Die, 0);
                PrintingScoreBoard (graphics,scoreboardnumbers,gametextures,LoadedNumbersTexture);
                graphics.renderTexture(gametextures.GameOver, SCREEN_WIDTH / 2 - 320, SCREEN_HEIGHT / 2 - 100, 1238 / 2, 340 / 2);
                graphics.renderTexture(gametextures.ReplayButton, (SCREEN_WIDTH - 100) / 2, (SCREEN_HEIGHT - 100) / 2 + 150, 100, 100);
                graphics.presentScene();
                Game_Overendered= true;
            }if (Restart) {
                    GameReset(bird, PipeArray, CloudsArray);
                    Mix_ResumeMusic();
                    countdown(graphics, numbers, LoadedNumbersTexture, gametextures);
                    Restart = false;
                }
        }
        else {
            while (Game_Over != true){
                UpdateGame(graphics, gametextures, objecttextures, bird, PipeArray, numbers,LoadedNumbersTexture, CloudsArray);
                while (SDL_PollEvent(&event) != 0) {
                    switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE) {
                            bird.Velocity = bird.Jump;
                            Mix_PlayChannel(-1, Jump, 0);

                        }
                    }
                }
            }
        }
        if (QuitGame) {
            graphics.quit();
            return 0;
        }
    }

}
