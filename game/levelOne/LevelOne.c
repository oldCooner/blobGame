#include "LevelOne.h"

SDL_FRect arrCollisionRects[COLLISION_RECT_COUNT];

enum playerStates currentPlayerState;

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
    arrCollisionRects[PLAYER_BLOB].x = 745;
    arrCollisionRects[PLAYER_BLOB].y = 569;
    arrCollisionRects[PLAYER_BLOB].h = 30;
    arrCollisionRects[PLAYER_BLOB].w = 30;
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
            SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[PLAYER_BLOB] );
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
                Internal_MovePlayer( -1, 0 );
                break;

            case SDLK_RIGHT:
            case SDLK_D:
                Internal_MovePlayer( 1, 0 );
                break;

            case SDLK_SPACE:
                Internal_MovePlayer( 0, 1 );
                break;
        }
    }
}

void Internal_MovePlayer(int iXOffset, int iYOffset)
{
    SDL_FRect rectMovingTo;
    int i;

    rectMovingTo = arrCollisionRects[PLAYER_BLOB];

    // generate rect we would be moving too
    if( iYOffset == 0 )
    { // we are moving left or right

        if( iXOffset > 0 )
        { // we are moving right
            rectMovingTo.x++;
        } else
        { // we are moving left
            rectMovingTo.x--;
        }

    } else if ( iXOffset == 0 )
    { // we are moving up down

        if( iYOffset < 0 )
        { // we are moving up
            rectMovingTo.y++;
        } else
        { // we are moving down
            rectMovingTo.y--;
        }

    }

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
    arrCollisionRects[PLAYER_BLOB] = rectMovingTo;
}