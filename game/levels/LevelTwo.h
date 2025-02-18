#ifndef LEVEL_TWO_HEADER_
#define LEVEL_TWO_HEADER_

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GameConsts.h"
#include "BaseLevel.h"

// external functions
void LevelTwo_Init( SDL_Renderer *pGameRenderer );
void LevelTwo_Destroy();

void LevelTwo_Render( SDL_Renderer *pGameRenderer );
void LevelTwo_HandleInput( SDL_Event *pSDLEvent );
void LevelTwo_Tick( int *bGoToNextLevel );

#endif //LEVEL_TWO_HEADER


/// PERSONAL NOTES
/*
    Level Two will introduce movable objects
    To "win" level one, you have to get to the green platform
*/