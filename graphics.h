#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "GameState.h"

struct Graphics {
	SDL_Renderer* renderer;
	SDL_Window* window;


void logErrorAndExit(const char* msg, const char* error){
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
			"%s: %s", msg, error);
		SDL_Quit();
	}

void init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			logErrorAndExit("SDL_Init", SDL_GetError());
		window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr)
			logErrorAndExit("CreateWindow", SDL_GetError());
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
			logErrorAndExit("SDL_image error:", IMG_GetError());
		renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
		if (renderer == nullptr)
			logErrorAndExit("CreateRenderer", SDL_GetError());
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError() );
        }
	}
	void prepareScene(SDL_Texture* background)
	{
		SDL_RenderClear(renderer);
		int ImgW,ImgH;
		SDL_QueryTexture(background,NULL,NULL,&ImgW,&ImgH);
		ImgH=SCREEN_HEIGHT;
		ImgW=SCREEN_WIDTH;
		int x = (SCREEN_WIDTH-ImgW)/2;
		int y=0;
		SDL_Rect Rect = {x,y,ImgW,ImgH};
		SDL_RenderCopy(renderer, background, NULL, &Rect);
	}
	void presentScene()
	{
		SDL_RenderPresent(renderer);
	}
	SDL_Texture* loadTexture(const char* filename) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
			"Loading %s", filename);
		SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
		if (texture == NULL)
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
				SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

		return texture;
	}
	void renderTexture(SDL_Texture* texture, int x, int y,int width,int height)
	{
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = width;
		dest.h = height;
		SDL_RenderCopy(renderer, texture, NULL, &dest);
	}
    Mix_Music *loadMusic(const char* path){
         Mix_Music *gMusic = Mix_LoadMUS(path);
         if (gMusic == nullptr) {
             SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
             SDL_LOG_PRIORITY_ERROR,
             "Could not load music! SDL_mixer Error: %s", Mix_GetError());
         }
         return gMusic;
         }
    void play(Mix_Music *gMusic){
         if (gMusic == nullptr) {
                return;
         }
         if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
         }
         else if( Mix_PausedMusic() == 1 ) {
                Mix_ResumeMusic();
         }
    }

	void quit()
	{
	    Mix_Quit();
		IMG_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

};

#endif // _GRAPHICS__H

