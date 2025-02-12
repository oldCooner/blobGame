#include "Game.h"

int main(int argc, char **argv)
{
    if( ! Game_Init() )
    {
        Game_Close();
    } else
    {
        Game_Run();
    }

    Game_Close();

    return 0;
}