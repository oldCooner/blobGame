#include "Game.h"

SDL_Renderer *pGameRenderer = NULL;
SDL_Window *pGameWindow = NULL;
int iWindowWidth, iWindowHeight;

int Game_Init()
{
    if( SDL_CreateWindowAndRenderer( "c_sdl_template", 0, 0, SDL_WINDOW_FULLSCREEN, &pGameWindow, &pGameRenderer ) )
    {
        if( TTF_Init() )
        {
            SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );

            SDL_SyncWindow( pGameWindow );
            SDL_GetWindowSize( pGameWindow, &iWindowWidth, &iWindowHeight );

            /*
                LOAD ALL TEXTURES HERE
            */
        } else
        {
            fprintf(stderr, "Failed to Initialize the TTF Module! SDL ERROR: %s\n", SDL_GetError());
            return 0;
        }
    } else
    {
        fprintf(stderr, "Failed to create window and renderer! SDL ERROR: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void Game_Close()
{
    SDL_DestroyRenderer(pGameRenderer);
    SDL_DestroyWindow(pGameWindow);

    pGameRenderer = NULL;
    pGameWindow = NULL;

    SDL_Quit();
}

void Game_Run()
{
    SDL_Event sdlEvents;
    int bGameRunning;

    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 225 );
    SDL_RenderClear( pGameRenderer );
    Game_Render();
    SDL_RenderPresent( pGameRenderer );

    bGameRunning = 1;
    while(bGameRunning)
    {
        SDL_PollEvent(&sdlEvents);
        if( sdlEvents.type == SDL_EVENT_QUIT )
        {
            bGameRunning = 0;
            break;
        } else
        {
            Game_EventHandling();
        }

        if(!bGameRunning)
            break;

        // Main Game Loop
        SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
        SDL_RenderClear(pGameRenderer);
        Game_Render();
        SDL_RenderPresent(pGameRenderer);
    }
}

void Game_Render()
{
    /*
        INSERT RENDERING HERE
    */
}

void Game_EventHandling()
{
    /*
        HANDLE SDL EVENTS HERE
    */
}