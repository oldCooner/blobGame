#ifndef LEVEL_THREE_HEADER_
#define LEVEL_THREE_HEADER_

// includes
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GameConsts.h"
#include "BaseLevel.h"

void LevelThree_Init( SDL_Renderer *pGameRenderer );
void LevelThree_Destroy();

void LevelThree_Render( SDL_Renderer *pGameRenderer );
void LevelThree_HandleInput( SDL_Event *pSDLEvent );
void LevelThree_Tick( int *bGoToNextLevel );

#endif