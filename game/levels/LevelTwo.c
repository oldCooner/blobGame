#include "LevelTwo.h"

void LevelTwo_Init( SDL_Renderer *pGameRenderer )
{
    // temp vars
    int iWindowWidth, iWindowHeight;
    int iSecondPlatformWidth;
    int iBlockSize;
    
    // get window size
    SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

    // vars
    currentPlayerState = PLAYER_IDLE_OR_MOVING;
    iPlayerXVel = 0;
    iPlayerYVel = 0;

    // setup collision rects
    iCollisionRectCount = 2;
    arrCollisionRects = malloc( sizeof(SDL_FRect) * iCollisionRectCount );

    iMovableRectCount = 1;
    arrMovableRects = malloc( sizeof(SDL_FRect) * iMovableRectCount );

    // setup platforms
    iSecondPlatformWidth = 200;
    iBlockSize = 60;

    //bottom platform
    arrCollisionRects[0].x = 0;
    arrCollisionRects[0].y = iWindowHeight / 2 - TILE_SIZE;
    arrCollisionRects[0].w = iWindowWidth;
    arrCollisionRects[0].h = TILE_SIZE;

    // upper platform
    arrCollisionRects[1].x = iWindowWidth - iSecondPlatformWidth;
    arrCollisionRects[1].y = (iWindowHeight / 2 - TILE_SIZE) - (PLAYER_HEIGHT * 4);
    arrCollisionRects[1].w = iSecondPlatformWidth - WIN_PLATFORM_WIDTH;
    arrCollisionRects[1].h = TILE_SIZE;

    // win platform
    rectWinPlatform.x = iWindowWidth - WIN_PLATFORM_WIDTH;
    rectWinPlatform.y = arrCollisionRects[1].y;
    rectWinPlatform.w = WIN_PLATFORM_WIDTH;
    rectWinPlatform.h = TILE_SIZE;

    // where to start player
    rectPlayer.x = 200;
    rectPlayer.y = arrCollisionRects[0].y - PLAYER_HEIGHT - 1;
    rectPlayer.w = PLAYER_WIDTH;
    rectPlayer.h = PLAYER_HEIGHT;

    // movable block
    arrMovableRects[0].x = iWindowWidth / 2 - iBlockSize;
    arrMovableRects[0].y = arrCollisionRects[0].y - iBlockSize;
    arrMovableRects[0].w = iBlockSize;
    arrMovableRects[0].h = iBlockSize;
}

void LevelTwo_Destroy()
{
    free(arrCollisionRects);
    free(arrMovableRects);
}

void LevelTwo_Render( SDL_Renderer *pGameRenderer )
{
    // temp vars
    int i;

    // first draw walls
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
    for( i = 0; i < iCollisionRectCount; i++ )
    {
        SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[i] );
    }

    // now movable blocks
    SDL_SetRenderDrawColor( pGameRenderer, 127, 127, 127, 255 );
    for( i = 0; i < iMovableRectCount; i++ )
    {
        SDL_RenderFillRect( pGameRenderer, &arrMovableRects[i] );
    }

    // now draw player
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( pGameRenderer, &rectPlayer );

    // now draw win platform
    SDL_SetRenderDrawColor( pGameRenderer, 0, 255, 0, 255 );
    SDL_RenderFillRect( pGameRenderer, &rectWinPlatform );
}

void LevelTwo_HandleInput( SDL_Event *pSDLEvent )
{
    BaseLevel_HandleUserInput( pSDLEvent, &iPlayerXVel, &iPlayerYVel, &currentPlayerState );
}

void LevelTwo_Tick( int *bGoToNextLevel )
{
    // tmp vars
    int bPushedABlock;

    // when moving, check to push blocks first
    bPushedABlock = 0;

    if( currentPlayerState == PLAYER_IDLE_OR_MOVING )
        bPushedABlock = BaseLevel_PushAroundBlocks( &rectPlayer, arrMovableRects, iMovableRectCount, iPlayerXVel ); 

    if( bPushedABlock == 0 )
    { // we can push a block or move
        BaseLevel_HandleLeftRightMovement( &rectPlayer, arrCollisionRects, arrMovableRects, iMovableRectCount, iCollisionRectCount, iPlayerXVel );
    }

    BaseLevel_HandleJumping( &rectPlayer, arrCollisionRects, arrMovableRects, iMovableRectCount, iCollisionRectCount, &currentPlayerState, &iHowLongIveBeenJumping );


    if(currentPlayerState == PLAYER_IDLE_OR_MOVING)
    {
        BaseLevel_EnactGravity( &rectPlayer, arrCollisionRects, iCollisionRectCount, arrMovableRects, iMovableRectCount );
    }

    // check for win
    if( SDL_HasRectIntersectionFloat( &rectPlayer, &rectWinPlatform ) )
        *bGoToNextLevel = 1;
}