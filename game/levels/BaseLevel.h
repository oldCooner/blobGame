#ifndef BASE_LEVEL_HEADER_
#define BASE_LEVEL_HEADER_

#include <SDL3/SDL.h>

#include "GameConsts.h"

// defines
#define WIN_PLATFORM_WIDTH 100

// enums
enum PlayerStates
{
    PLAYER_JUMPING,
    PLAYER_FALLING,
    PLAYER_IDLE_OR_MOVING,
    PLAYER_WATER_STATE
};

// vars
extern SDL_FRect *arrCollisionRects;
extern int iCollisionRectCount;

extern SDL_FRect *arrMovableRects;
extern int iMovableRectCount;

extern SDL_FRect rectWinPlatform;

extern SDL_FRect rectPlayer;
extern int iHowLongIveBeenJumping;
extern int iPlayerXVel, iPlayerYVel;
extern enum PlayerStates currentPlayerState;

extern enum GridCellTypes *arrWaterGrid;
extern int iWaterGridWidth, iWaterGridHeight, iWaterGridTotalSize;

int BaseLevel_CheckColissions( SDL_FRect playerRect, SDL_FRect *arrCollisionBoxes, int iCollisionBoxCount, SDL_FRect *arrMovableRects, int iMovableRectCount );
void BaseLevel_EnactGravity( SDL_FRect *playerRect, SDL_FRect *arrCollisionBoxes, int iCollisionBoxCount, SDL_FRect *arrMovableRects, int iMovableRectCount );

void BaseLevel_HandleUserInput( SDL_Event *pSDLEvent, int *iPlayerXVel, int *iPlayerYVel, enum PlayerStates *currentPlayerState);

void BaseLevel_HandleJumping( SDL_FRect *pRectPlayer, SDL_FRect *arrCollisionRects, SDL_FRect *arrMovableRects, int iMovableRectCount, int iCollisionRectCount, enum PlayerStates *pCurrentPlayerState, int *iHowLongIveBeenJumping );
void BaseLevel_HandleLeftRightMovement( SDL_FRect *pRectPlayer, SDL_FRect *arrCollisionRects, int iCollisionRectCount, SDL_FRect *arrMovableRects, int iMovableRectCount, int iPlayerXVel );

int BaseLevel_PushAroundBlocks( SDL_FRect *pRectPlayer, SDL_FRect *arrMovableRects, int iMovableRectCount, int iPlayerXVel ); // returns true if you pushed a block


#endif //BASE_LEVELHEADER_