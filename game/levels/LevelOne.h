#ifndef LEVEL_ONE_HEADER_
#define LEVEL_ONE_HEADER_

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GameConsts.h"
#include "BaseLevel.h"

// external functions
void LevelOne_Init( SDL_Renderer *pGameRenderer );
void LevelOne_Destroy();

void LevelOne_Render( SDL_Renderer *pGameRenderer );
void LevelOne_HandleInput( SDL_Event *pSDLEvent );
void LevelOne_Tick( int *bGoToNextLevel );

#endif //LEVEL_ONE_HEADER


/// PERSONAL NOTES
/*
    I want level one to be a basic level where the player moves from left to right
    To "win" level one, you have to get to the green platform
*/