#ifndef GAME_HEADER_
#define GAME_HEADER_

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <stdio.h>

#include "LevelOne.h"
#include "LTimer.h"

// defines
#define SCREEN_FPS 240
#define SCREEN_TICKS_PER_FRAME 1000/SCREEN_FPS

// enums
enum gameLevels
{
    LEVEL_ONE
};

extern SDL_Renderer *pGameRenderer;
extern SDL_Window *pGameWindow;
extern int iWindowWidth, iWindowHeight;

extern enum gameLevels currentLevel;

int Game_Init(); // initialize window and load headers
void Game_Run();
void Game_Close(); // close the game

void Game_Render();
void Game_EventHandling(SDL_Event *pSDLEvent);
void Game_Tick();

#endif