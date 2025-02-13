#include "LTimer.h"

void Timer_Start( struct LTIMER_ *pInputTimer )
{
    pInputTimer->bState = 1; // running
    pInputTimer->iStartTime = SDL_GetTicks();
}

Uint32 Timer_GetTicks( struct LTIMER_ *pInputTimer )
{
    if( pInputTimer->bState == 1 )
    {
        return SDL_GetTicks() - pInputTimer->iStartTime;
    } else
    {
        return 0;
    }
}