#ifndef LTIMER_HEADER_
#define LTIMER_HEADER_

#include <SDL3/SDL.h>

struct LTIMER_
{
    int bState;
    Uint32 iStartTime;
};
typedef struct LTIMER_ objTimer;

void Timer_Start( struct LTIMER_ *pInputTimer );
Uint32 Timer_GetTicks( struct LTIMER_ *pInputTimer );

#endif