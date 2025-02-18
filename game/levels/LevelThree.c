#include "LevelThree.h"

void LevelThree_Init( SDL_Renderer *pGameRenderer )
{
    // temp vars
    int iWindowWidth, iWindowHeight;
    int iGrateWidth;
    int i;
    
    // get window size
    SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

    // vars
    currentPlayerState = PLAYER_IDLE_OR_MOVING;
    iPlayerXVel = 0;
    iPlayerYVel = 0;

    // setup collision rects
    iCollisionRectCount = 7;
    arrCollisionRects = malloc( sizeof(SDL_FRect) * iCollisionRectCount );

    // collision vars
    iGrateWidth = (PLAYER_WIDTH / 2) * 8;

    // upper two platforms
    arrCollisionRects[0].x = 0;
    arrCollisionRects[0].y = iWindowHeight / 2;
    arrCollisionRects[0].w = (iWindowWidth / 2) - iGrateWidth;
    arrCollisionRects[0].h = TILE_SIZE;

    arrCollisionRects[1].x = arrCollisionRects[0].x + arrCollisionRects[0].w + iGrateWidth;
    arrCollisionRects[1].y = arrCollisionRects[0].y;
    arrCollisionRects[1].w = iWindowWidth - arrCollisionRects[1].x;
    arrCollisionRects[1].h = arrCollisionRects[0].h;

    // walls
    arrCollisionRects[2].x = arrCollisionRects[0].x + arrCollisionRects[0].w;
    arrCollisionRects[2].y = arrCollisionRects[0].y;
    arrCollisionRects[2].w = TILE_SIZE;
    arrCollisionRects[2].h = PLAYER_HEIGHT * 3;

    arrCollisionRects[3].x = arrCollisionRects[1].x;
    arrCollisionRects[3].y = arrCollisionRects[0].y;
    arrCollisionRects[3].w = TILE_SIZE;
    arrCollisionRects[3].h = PLAYER_HEIGHT * 3;

    // grates
    arrCollisionRects[4].x = arrCollisionRects[2].x + TILE_SIZE + (PLAYER_WIDTH / 2);
    arrCollisionRects[4].y = arrCollisionRects[2].y + arrCollisionRects[2].h - TILE_SIZE;
    arrCollisionRects[4].w = PLAYER_WIDTH / 2;
    arrCollisionRects[4].h = TILE_SIZE;

    arrCollisionRects[5].x = arrCollisionRects[4].x + PLAYER_WIDTH;
    arrCollisionRects[5].y = arrCollisionRects[4].y;
    arrCollisionRects[5].w = PLAYER_WIDTH / 2;
    arrCollisionRects[5].h = TILE_SIZE;

    arrCollisionRects[6].x = arrCollisionRects[5].x + PLAYER_WIDTH;
    arrCollisionRects[6].y = arrCollisionRects[5].y;
    arrCollisionRects[6].w = PLAYER_WIDTH / 2;
    arrCollisionRects[6].h = TILE_SIZE;

    // player
    rectPlayer.x = 100;
    rectPlayer.y = arrCollisionRects[0].y - PLAYER_HEIGHT - 1;
    rectPlayer.w = PLAYER_WIDTH;
    rectPlayer.h = PLAYER_HEIGHT;

    // setup water grid
    iWaterGridWidth = ceil(iWindowWidth / GRID_CELL_SIZE );
    iWaterGridHeight = ceil(iWindowHeight / GRID_CELL_SIZE );
    iWaterGridTotalSize = ( iWaterGridWidth * iWaterGridHeight ) + 1; 
    arrWaterGrid = malloc( sizeof(enum GridCellTypes) * iWaterGridTotalSize );

    // init water grid to 0
    for( i = 0; i < iWaterGridTotalSize; i++ )
    {
        arrWaterGrid[i] = EMPTY_GRID_CELL;
    }
}

void LevelThree_Destroy()
{
    free(arrCollisionRects);
    free(arrWaterGrid);
}

void LevelThree_Render( SDL_Renderer *pGameRenderer )
{
    //tmp vars
    int i;

    // render walls
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
    for( i = 0; i < iCollisionRectCount; i++ )
    {
        SDL_RenderFillRect( pGameRenderer, &arrCollisionRects[i] );
    }

    // render player
    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( pGameRenderer, &rectPlayer );
}

void LevelThree_HandleInput( SDL_Event *pSDLEvent )
{
    BaseLevel_HandleUserInput( pSDLEvent, &iPlayerXVel, &iPlayerYVel, &currentPlayerState );
}

void LevelThree_Tick( int *bGoToNextLevel )
{
    BaseLevel_HandleLeftRightMovement( &rectPlayer, arrCollisionRects, NULL, 0, iCollisionRectCount, iPlayerXVel );
    BaseLevel_HandleJumping( &rectPlayer, arrCollisionRects, NULL, 0, iCollisionRectCount, &currentPlayerState, &iHowLongIveBeenJumping );

    if(currentPlayerState == PLAYER_IDLE_OR_MOVING)
        BaseLevel_EnactGravity( &rectPlayer, arrCollisionRects, iCollisionRectCount, arrMovableRects, iMovableRectCount );
}