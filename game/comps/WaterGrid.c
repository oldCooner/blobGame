#include "WaterGrid.h"

enum GridCellTypes *WaterGrid_CreateGrid( int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize, SDL_FRect *arrCollisionRects, int iCollisionRectCount, SDL_FRect *arrMovableRects, int iMovableRectCount )
{
    // tmp vars
    enum GridCellTypes *arrWaterGrid;
    SDL_FRect recTempCell;
    int iTotalGridSize;
    int i, x, y;

    // init vars
    iTotalGridSize = ( iWaterGridHeight * iWaterGridWidth ) + 1;
    arrWaterGrid = malloc( sizeof(enum GridCellTypes) * iTotalGridSize );

    recTempCell.x = 0;
    recTempCell.y = 0;
    recTempCell.w = iWaterCellSize;
    recTempCell.h = iWaterCellSize;

    // init cells to empty
    for( i = 0; i < iTotalGridSize; i++ )
    {
        arrWaterGrid[i] = EMPTY_GRID_CELL;
    }

    // setup grid collision
    for( y = 0; y < iWaterGridHeight; y++ )
    {
        for( x = 0; x < iWaterGridWidth; x++ )
        {
            for (i = 0; i < iCollisionRectCount; i++ )
            {
                if( SDL_HasRectIntersectionFloat( &recTempCell, &arrCollisionRects[i] ) )
                {
                    arrWaterGrid[ y * iWaterGridWidth + x ] = SOLID_GRID_CELL;
                    break;
                }
            }

            if( arrWaterGrid[ y * iWaterGridWidth + x ] == 0 )
            { // we don't already have collision, so we still have to check movable objects
                for( i = 0; i < iMovableRectCount; i++ )
                {
                    if( SDL_HasRectIntersectionFloat( &recTempCell, &arrCollisionRects[i] ) )
                    {
                        arrWaterGrid[ y * iWaterGridWidth + x ] = SOLID_GRID_CELL;
                        break;
                    }
                }
            }

            recTempCell.x += iWaterCellSize;
        }

        recTempCell.x = 0;
        recTempCell.y += iWaterCellSize;
    }



    // return
    return arrWaterGrid;
}

void WaterGrid_ConvertPlayer( enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize, SDL_FRect playerRect )
{
    // tmp vars
    SDL_FRect recTempCell;
    int x, y;

    // init vars
    recTempCell.x = 0;
    recTempCell.y = 0;
    recTempCell.w = iWaterCellSize;
    recTempCell.h = iWaterCellSize;

    for( y = 0; y < iWaterGridHeight; y++ )
    {
        for( x = 0; x < iWaterGridWidth; x++ )
        {
            if( SDL_HasRectIntersectionFloat( &playerRect, &recTempCell ) )
            {
                switch( arrWaterGrid[ y * iWaterGridWidth + x ] ) // the cell that is occupied
                {
                    case EMPTY_GRID_CELL:
                        arrWaterGrid[ y * iWaterGridWidth + x ] = MAJOR_WATER_CELL;
                        break;
                    
                    default:
                        fprintf( stderr, "Tried to init a water cell on an occupied grid. How did you get here?!" );
                        break;
                }
            }
            
            recTempCell.x += iWaterCellSize;
        }

        recTempCell.x = 0;
        recTempCell.y += iWaterCellSize;
    }
}

void WaterGrid_Tick( enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight )
{
    // tmp vars
    int x, y;

    // setup vars
    y = iWaterGridHeight - 2; // skip bottom row

    while( y >= 0)
    {
        for( x = iWaterGridWidth - 1; x >= 0; x-- )
        { // first I will look down
            if( arrWaterGrid[ y * iWaterGridWidth + x ] == MAJOR_WATER_CELL )
            { // we are looking at an actual water cell

                if( arrWaterGrid[ (y + 1) * iWaterGridWidth + x ] == EMPTY_GRID_CELL )
                { // the spot right below is free
                    arrWaterGrid[ (y + 1) * iWaterGridWidth + x ] = MAJOR_WATER_CELL;
                    arrWaterGrid[ y * iWaterGridWidth + x ] = EMPTY_GRID_CELL;
                } else if( x < (iWaterGridWidth - 2) && arrWaterGrid[ (y + 1) * iWaterGridWidth + ( x + 1) ] == EMPTY_GRID_CELL )
                { // bottom right is free
                    arrWaterGrid[ (y + 1) * iWaterGridWidth + ( x + 1) ] = MAJOR_WATER_CELL;
                    arrWaterGrid[ y * iWaterGridWidth + x ] = EMPTY_GRID_CELL;
                } else if( x > 1 && arrWaterGrid[ (y + 1) * iWaterGridWidth + ( x - 1) ] == EMPTY_GRID_CELL )
                { // bottom left is free
                    arrWaterGrid[ (y + 1) * iWaterGridWidth + ( x - 1) ] = MAJOR_WATER_CELL;
                    arrWaterGrid[ y * iWaterGridWidth + x ] = EMPTY_GRID_CELL;
                } else if( y > 1 && x > 0 && x < (iWaterGridWidth - 2) && arrWaterGrid[ (y - 1) * iWaterGridWidth + ( x - 1) ] == MAJOR_WATER_CELL && arrWaterGrid[ y * iWaterGridWidth + (x + 1) ] == EMPTY_GRID_CELL)
                { // something is up and to the left, so I will be pushed right
                    arrWaterGrid[ y * iWaterGridWidth + ( x + 1) ] = MAJOR_WATER_CELL;
                    arrWaterGrid[ y * iWaterGridWidth + x ] = EMPTY_GRID_CELL;
                } else if( y > 1 && x > 0 && x < (iWaterGridWidth - 2) && arrWaterGrid[ (y - 1) * iWaterGridWidth + ( x + 1) ] == MAJOR_WATER_CELL && arrWaterGrid[ y * iWaterGridWidth + (x - 1) ] == EMPTY_GRID_CELL)
                { // something is up and to the right, so I will be pushed left
                    arrWaterGrid[ y * iWaterGridWidth + ( x - 1) ] = MAJOR_WATER_CELL;
                    arrWaterGrid[ y * iWaterGridWidth + x ] = EMPTY_GRID_CELL;
                }

            }
        }

        y--;
    }
}

void WaterGrid_Render( SDL_Renderer *pGameRenderer, enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize )
{
    // tmp vars
    SDL_FRect recTempCell;
    int x, y;

    // init vars
    recTempCell.x = 0;
    recTempCell.y = 0;
    recTempCell.w = iWaterCellSize;
    recTempCell.h = iWaterCellSize;

    // loop
    for( y = 0; y < iWaterGridHeight; y++ )
    {
        for( x = 0; x < iWaterGridWidth; x++ )
        {
            if( arrWaterGrid[ y * iWaterGridWidth + x ] == MAJOR_WATER_CELL )
            {
                SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 255, 255 );
                SDL_RenderFillRect( pGameRenderer, &recTempCell );
            }

            recTempCell.x += iWaterCellSize;
        }

        recTempCell.y += iWaterCellSize;
        recTempCell.x = 0;
    }
}