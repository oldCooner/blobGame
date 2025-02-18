#include "BaseLevel.h"

// vars
SDL_FRect *arrCollisionRects;
int iCollisionRectCount;

SDL_FRect *arrMovableRects;
int iMovableRectCount;

SDL_FRect rectWinPlatform;

SDL_FRect rectPlayer;
int iHowLongIveBeenJumping;
int iPlayerXVel, iPlayerYVel;
enum PlayerStates currentPlayerState;

int BaseLevel_CheckColissions( SDL_FRect playerRect, SDL_FRect *arrCollisionBoxes, int iCollisionBoxCount, SDL_FRect *arrMovableRects, int iMovableRectCount )
{
    int i;

    for( i = 0; i < iCollisionBoxCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &playerRect, &arrCollisionBoxes[i] ) )
            return 1;
    }

    for( i = 0; i < iMovableRectCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &playerRect, &arrMovableRects[i] ) )
            return 1;
    }

    return 0;
}

void BaseLevel_EnactGravity( SDL_FRect *playerRect, SDL_FRect *arrCollisionBoxes, int iCollisionBoxCount, SDL_FRect *arrMovableRects, int iMovableRectCount )
{
    int i;
    SDL_FRect futureRect;

    futureRect.x = playerRect->x;
    futureRect.y = playerRect->y + 1;
    futureRect.w = playerRect->w;
    futureRect.h = playerRect->h;

    for( i = 0; i < iCollisionBoxCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &futureRect, &arrCollisionBoxes[i] ) )
        {
            return;
        }
    }

    for( i = 0; i < iMovableRectCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &futureRect, &arrMovableRects[i] ) )
        {
            return;
        }
    }

    playerRect->y++;
}

void BaseLevel_HandleUserInput( SDL_Event *pSDLEvent, int *iPlayerXVel, int *iPlayerYVel, enum PlayerStates *currentPlayerState)
{
    if( pSDLEvent->type == SDL_EVENT_KEY_DOWN )
    {
        switch( pSDLEvent->key.key )
        {
            case SDLK_LEFT:
            case SDLK_A:
                *iPlayerXVel = -1;
                break;

            case SDLK_RIGHT:
            case SDLK_D:
                *iPlayerXVel = 1;
                break;

            case SDLK_SPACE:
                if( *currentPlayerState == PLAYER_IDLE_OR_MOVING )
                    *currentPlayerState = PLAYER_JUMPING;
                break;
        }
    } else if( pSDLEvent->type == SDL_EVENT_KEY_UP )
    {
        switch( pSDLEvent->key.key )
        {
            case SDLK_LEFT:
            case SDLK_A:
            case SDLK_RIGHT:
            case SDLK_D:
                *iPlayerXVel = 0;
                break;
        }
    }
}

void BaseLevel_HandleJumping( SDL_FRect *pRectPlayer, SDL_FRect *arrCollisionRects, SDL_FRect *arrMovableRects, int iMovableRectCount, int iCollisionRectCount, enum PlayerStates *pCurrentPlayerState, int *iHowLongIveBeenJumping )
{
    if( *pCurrentPlayerState == PLAYER_JUMPING )
    { // we are jumping
        if( *iHowLongIveBeenJumping < GAME_JUMP_TIME )
        { // we are jumping
            pRectPlayer->y += -1;
            *iHowLongIveBeenJumping += 1;
            
            // check that our head doesn't hit
            if( BaseLevel_CheckColissions( *pRectPlayer, arrCollisionRects, iCollisionRectCount, arrMovableRects, iMovableRectCount ) )
            {
                pRectPlayer->y += 1; // knock back down
                *pCurrentPlayerState = PLAYER_FALLING;
            }

        } else 
        { // we are done jumping
            *iHowLongIveBeenJumping = 0;
            *pCurrentPlayerState = PLAYER_FALLING;
        }
    } else if( *pCurrentPlayerState == PLAYER_FALLING )
    { // we are falling
        pRectPlayer->y += 1; // move the player down one

        // check collisions
        if( BaseLevel_CheckColissions( *pRectPlayer, arrCollisionRects, iCollisionRectCount, arrMovableRects, iMovableRectCount ) )
        { // we will crash
            pRectPlayer->y += -1;
            *pCurrentPlayerState = PLAYER_IDLE_OR_MOVING;
        }
    }
}

void BaseLevel_HandleLeftRightMovement( SDL_FRect *pRectPlayer, SDL_FRect *arrCollisionRects, SDL_FRect *arrMovableRects, int iMovableRectCount, int iCollisionRectCount, int iPlayerXVel )
{
    pRectPlayer->x += iPlayerXVel;

    if( BaseLevel_CheckColissions( *pRectPlayer, arrCollisionRects, iCollisionRectCount, arrMovableRects, iMovableRectCount ) )
    { // crashy crash
        pRectPlayer->x -= iPlayerXVel;
    }
}

int BaseLevel_PushAroundBlocks( SDL_FRect *pRectPlayer, SDL_FRect *arrMovableRects, int iMovableRectCount, int iPlayerXVel )
{
    // tmp vars
    SDL_FRect rectMovingTo;
    int i;
    
    // where am I going
    rectMovingTo = *pRectPlayer;
    rectMovingTo.x += iPlayerXVel;

    for( i = 0; i < iMovableRectCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &rectMovingTo, &arrMovableRects[i] ) )
        {
            pRectPlayer->x += iPlayerXVel;
            arrMovableRects[i].x += iPlayerXVel;
            return 1;
        }
    }

    return 0;
}