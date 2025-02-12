#ifndef LEVEL_ONE_HEADER_
#define LEVEL_ONE_HEADER_

#include <SDL3/SDL.h>
#include <stdio.h>

// enums
enum collisionRects
{
    PLATFORM_A,
    PLATFORM_B,
    PLATFORM_WIN,
    OBJECT_BOX,
    PLAYER_BLOB,
    COLLISION_RECT_COUNT
};

enum playerStates
{
    PLAYER_BLOB_STATE,
    PLAYER_LIQUID_STATE
};

// vars
extern SDL_FRect arrCollisionRects[COLLISION_RECT_COUNT];

extern enum playerStates currentPlayerState;

// external funcs
void LevelOne_Init(SDL_Renderer *pGameRenderer);
void LevelOne_Render(SDL_Renderer *pGameRenderer);
void LevelOne_HandleInput(SDL_Event *pSDLEvent);

// internal funcs
void Internal_MovePlayer(int iXOffset, int iYOffset);

#endif