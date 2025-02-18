#include "LevelOne.h"

void LevelOne_Init( SDL_Renderer *pGameRenderer )
{
    // temp vars
    int iWindowWidth, iWindowHeight;

    // get Window size
    SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

    // construct walls for level
    iCollisionRectCount = 1;
    arrCollisionRects = malloc( sizeof(SDL_FRect) * iCollisionRectCount );

    // bottom wall
    arrCollisionRects[0].x = 0;
    arrCollisionRects[0].y = (iWindowHeight / 2) - TILE_SIZE;
    arrCollisionRects[0].w = iWindowWidth - WIN_PLATFORM_WIDTH;
    arrCollisionRects[0].h = TILE_SIZE;

    // winning platform
    rectWinPlatform.x = iWindowWidth - WIN_PLATFORM_WIDTH;
    rectWinPlatform.y = (iWindowHeight / 2) - TILE_SIZE;
    rectWinPlatform.w = WIN_PLATFORM_WIDTH;
    rectWinPlatform.h = TILE_SIZE;

    // player
    currentPlayerState = PLAYER_IDLE_OR_MOVING;
    iHowLongIveBeenJumping = 0;
    iPlayerXVel = 0;
    iPlayerYVel = 0;

    rectPlayer.x = 200;
    rectPlayer.y = arrCollisionRects[0].y - PLAYER_HEIGHT - 1;
    rectPlayer.w = PLAYER_WIDTH;
    rectPlayer.h = PLAYER_HEIGHT;
}

void LevelOne_Destroy()
{
    free(arrCollisionRects);
}

void LevelOne_Render( SDL_Renderer *pGameRenderer )
{
    // draw walls
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
    SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[0] );

    // draw winning platform
    SDL_SetRenderDrawColor( pGameRenderer, 0, 255, 0, 255 );
    SDL_RenderFillRect( pGameRenderer, &rectWinPlatform );;

    // draw Player
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( pGameRenderer, &rectPlayer );
}

void LevelOne_HandleInput( SDL_Event *pSDLEvent )
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
                if( currentPlayerState == PLAYER_IDLE_OR_MOVING )
                    currentPlayerState = PLAYER_JUMPING;
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
                iPlayerXVel = 0;
                break;
        }
    }
}

void LevelOne_Tick( int *bGoToNextLevel )
{
    // local vars
    SDL_FRect rectMovingTo;
    int i;

    // handle jumping v falling
    if( currentPlayerState == PLAYER_JUMPING )
    {
        if( iHowLongIveBeenJumping == 0 )
        { // first frame since I jumped
            iPlayerYVel = -1;
            iHowLongIveBeenJumping++;
        } else if ( iHowLongIveBeenJumping == GAME_JUMP_TIME )
        { // my last jump frame
            currentPlayerState = PLAYER_FALLING;
            iPlayerYVel = 0;
            iHowLongIveBeenJumping = 0;
        } else
        {
            iHowLongIveBeenJumping++;
        }
    } else if( currentPlayerState == PLAYER_FALLING )
    {
        iPlayerYVel = 1;
    }

    // moving here
    rectMovingTo = rectPlayer;

    // left/right
    rectMovingTo.x += iPlayerXVel;
    for( i = 0; i < iCollisionRectCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &rectPlayer, &arrCollisionRects[i] ) )
        {
            rectMovingTo.x = rectPlayer.x - 1; // move back
            break;
        }
    }
    rectPlayer = rectMovingTo;

    // up/down
    rectMovingTo.y += iPlayerYVel;
    for( i = 0; i < iCollisionRectCount; i++ )
    {
        if( SDL_HasRectIntersectionFloat( &rectPlayer, &arrCollisionRects[i] ) )
        {
            rectMovingTo.y = rectPlayer.y - 1; // move back
            iPlayerYVel = 0;
            currentPlayerState = PLAYER_IDLE_OR_MOVING;
            break;
        }
    }
    rectPlayer = rectMovingTo;

    // grab win platform
    rectMovingTo.y = rectPlayer.y + 1;
    rectMovingTo.w = 1; // the whole player should be over green
    if( SDL_HasRectIntersectionFloat( &rectMovingTo, &rectWinPlatform ) )
    { // we win
        *bGoToNextLevel = 1;
    }

}