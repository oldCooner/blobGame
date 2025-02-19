#ifndef WATER_GRID_HEADER_
#define WATER_GRID_HEADER_

// includes
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>

// enums
enum GridCellTypes
{
    EMPTY_GRID_CELL,
    MAJOR_WATER_CELL,
    MINOR_WATER_CELL,
    SOLID_GRID_CELL
};

// vars
extern int iWaterCellCount;

// extern funcs
enum GridCellTypes *WaterGrid_CreateGrid( int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize, SDL_FRect *arrCollisionRects, int iCollisionRectCount, SDL_FRect *arrMovableRects, int iMovableRectCount );
void WaterGrid_ConvertPlayer( enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize, SDL_FRect playerRect );

void WaterGrid_Tick( enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight );
void WaterGrid_Render( SDL_Renderer *pGameRenderer, enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize );

SDL_FRect *WaterGrid_GetBodyLocations( int *iOutputSize, enum GridCellTypes *arrWaterGrid, int iWaterGridWidth, int iWaterGridHeight, int iWaterCellSize );


#endif //WATER_GRID_HEADER_