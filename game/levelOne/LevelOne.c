#include "LevelOne.h"

SDL_FRect arrCollisionRects[COLLISION_RECT_COUNT];
SDL_FRect playerRect;

enum playerStates currentPlayerState;
int bIsJumping, iJumpTime;

int iPlayerXVel, iPlayerYVel;

void LevelOne_Init(SDL_Renderer *pGameRenderer)
{
    int iWindowWidth, iWindowHeight;
    int iWinPlatformWidth;
    int iPlatformHeight;
    int iBoxSize;

    // get screen size
    SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

    // level consts
    iWinPlatformWidth = 50;
    iPlatformHeight = 20;
    iBoxSize = 100;
    bIsJumping = 0;
    iPlayerXVel = 0;
    iPlayerYVel = 0;

    // other vars
    currentPlayerState = PLAYER_BLOB_STATE;

    // collision rects
    arrCollisionRects[PLATFORM_A].x = 50;
    arrCollisionRects[PLATFORM_A].y = 600;
    arrCollisionRects[PLATFORM_A].w = 1600;
    arrCollisionRects[PLATFORM_A].h = iPlatformHeight;

    arrCollisionRects[PLATFORM_B].x = 0;
    arrCollisionRects[PLATFORM_B].y = iWindowHeight - iPlatformHeight;
    arrCollisionRects[PLATFORM_B].w = iWindowWidth - iWinPlatformWidth;
    arrCollisionRects[PLATFORM_B].h = iPlatformHeight;

    arrCollisionRects[PLATFORM_WIN].x = iWindowWidth - iWinPlatformWidth;
    arrCollisionRects[PLATFORM_WIN].y = iWindowHeight - iPlatformHeight;
    arrCollisionRects[PLATFORM_WIN].w = iWinPlatformWidth;
    arrCollisionRects[PLATFORM_WIN].h = iPlatformHeight;

    arrCollisionRects[OBJECT_BOX].x = 200;
    arrCollisionRects[OBJECT_BOX].y = iWindowHeight - iPlatformHeight - iBoxSize;
    arrCollisionRects[OBJECT_BOX].w = iBoxSize;
    arrCollisionRects[OBJECT_BOX].h = iBoxSize;

    // player init
    playerRect.x = 745;
    playerRect.y = 569;
    playerRect.h = 30;
    playerRect.w = 30;
}

void LevelOne_Render(SDL_Renderer *pGameRenderer)
{
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[PLATFORM_A] );
    SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[PLATFORM_B] );

    SDL_SetRenderDrawColor( pGameRenderer, 80, 152, 255, 255 ); // light blue
    SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[PLATFORM_WIN] );

    SDL_SetRenderDrawColor( pGameRenderer, 84, 84, 84, 255 ); // grey
    SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[OBJECT_BOX] );


    // player here
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 255, 255 ); // pure blue
    switch(currentPlayerState)
    {
        case PLAYER_BLOB_STATE:
            SDL_RenderFillRect( pGameRenderer, &playerRect );
            break;
        
            default:
                break;
    };
}

void LevelOne_HandleInput(SDL_Event *pSDLEvent)
{
    if( pSDLEvent->type == SDL_EVENT_KEY_DOWN )
    {
        switch( pSDLEvent->key.key )
        {
            case SDLK_LEFT:
            case SDLK_A:
                iPlayerXVel = -1;
                break;

            case SDLK_RIGHT:
            case SDLK_D:
                iPlayerXVel = 1;
                break;

            case SDLK_SPACE:
                bIsJumping = 1;
                break;
        }
    } else if( pSDLEvent->type==SDL_EVENT_KEY_UP )
    {
        switch( pSDLEvent->key.key )
        {
            case SDLK_LEFT:
            case SDLK_A:
            case SDLK_RIGHT:
            case SDLK_D:
                iPlayerXVel = 0;
                break;
        }
    }
}

void Internal_MovePlayer()
{
    SDL_FRect rectMovingTo;
    int i;

    // move
    rectMovingTo = playerRect;
    rectMovingTo.x += iPlayerXVel;
    rectMovingTo.y += iPlayerYVel;

    // check for future collision
    for( i = 0; i < COLLISION_RECT_COUNT; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &rectMovingTo, &arrCollisionRects[i] ) )
        {
            // we can't move
            return;
        }
    }

    // if we made it out that for loop, we are good
    playerRect = rectMovingTo;
}

void LevelOne_Tick()
{
    // handle jump time
    if(bIsJumping)
    {
        if(iJumpTime == 0)
        { // first time jumping
            iPlayerYVel = -1;
            iJumpTime = GAME_JUMP_TIME;
        } else if( iJumpTime == 1 )
        { // this is our last jump frame
            iJumpTime = 0;
            bIsJumping = 0;
        } else
        {
            iJumpTime--;
        }
    } else
    {
        iPlayerYVel = 0;
    }

    // handle movement
    if( iPlayerXVel != 0 || iPlayerYVel != 0 )
        Internal_MovePlayer();
}