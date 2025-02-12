#ifndef GAME_HEADER_
#define GAME_HEADER_

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <stdio.h>

extern SDL_Renderer *pGameRenderer;
extern SDL_Window *pGameWindow;
extern int iWindowWidth, iWindowHeight;

int Game_Init(); // initialize window and load headers
void Game_Run();
void Game_Close(); // close the game

void Game_Render();
void Game_EventHandling();

#endif