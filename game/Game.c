#include "Game.h"

SDL_Renderer *pGameRenderer = NULL;
SDL_Window *pGameWindow = NULL;
int iWindowWidth, iWindowHeight;

enum gameLevels currentLevel;
int bGoToNextLevel;

int Game_Init()
{
    if( SDL_CreateWindowAndRenderer( "c_sdl_template", 0, 0, SDL_WINDOW_FULLSCREEN, &pGameWindow, &pGameRenderer ) )
    {
        if( TTF_Init() )
        {
            SDL_SetRenderDrawColor( pGameRenderer, 255, 255, 255, 255 );

            SDL_SyncWindow( pGameWindow );
            SDL_GetWindowSize( pGameWindow, &iWindowWidth, &iWindowHeight );

            bGoToNextLevel = 0;
            //currentLevel = LEVEL_ONE;
            //LevelOne_Init(pGameRenderer);

            currentLevel = LEVEL_THREE;
            LevelThree_Init(pGameRenderer);
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
    objTimer gameTimer;
    int bGameRunning;
    int iFrameTicks;

    SDL_SetRenderDrawColor( pGameRenderer, 255, 255, 255, 225 );
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
            Game_EventHandling(&sdlEvents);
        }

        if(!bGameRunning)
            break;

        Timer_Start(&gameTimer);

        Game_Tick();
        // Main Game Loop
        SDL_SetRenderDrawColor( pGameRenderer, 255, 255, 255, 255 );
        SDL_RenderClear(pGameRenderer);
        Game_Render();
        SDL_RenderPresent(pGameRenderer);

        iFrameTicks = Timer_GetTicks(&gameTimer);
        if( iFrameTicks < SCREEN_TICKS_PER_FRAME )
            SDL_Delay( SCREEN_TICKS_PER_FRAME - iFrameTicks );
    }
}

void Game_Render()
{
    switch(currentLevel)
    {
        case LEVEL_ONE:
            LevelOne_Render(pGameRenderer);
            break;

        case LEVEL_TWO:
            LevelTwo_Render(pGameRenderer);
            break;

        case LEVEL_THREE:
            LevelThree_Render(pGameRenderer);
            break;

        default:
            break;
    }
}

void Game_EventHandling(SDL_Event *pSDLEvent)
{
    switch(currentLevel)
    {
        case LEVEL_ONE:
            LevelOne_HandleInput(pSDLEvent);
            break;

        case LEVEL_TWO:
            LevelTwo_HandleInput(pSDLEvent);
            break;
        
        case LEVEL_THREE:
            LevelThree_HandleInput(pSDLEvent);
            break;

        default:
            break;
    }
}

void Game_Tick()
{
    switch(currentLevel)
    {
        case LEVEL_ONE:
            LevelOne_Tick( &bGoToNextLevel );
            break;

        case LEVEL_TWO:
            LevelTwo_Tick( &bGoToNextLevel );
            break;

        case LEVEL_THREE:
            LevelThree_Tick( &bGoToNextLevel );
            break;

        default:
            break;
    }

    // did we win?
    if( bGoToNextLevel )
    {
        switch(currentLevel)
        {
            case LEVEL_ONE:
                LevelOne_Destroy();
                currentLevel = LEVEL_TWO;
                LevelTwo_Init(pGameRenderer);
                bGoToNextLevel = 0;
                break;
            
            case LEVEL_TWO:
                LevelTwo_Destroy();
                currentLevel = LEVEL_THREE;
                LevelThree_Init(pGameRenderer);
                bGoToNextLevel = 0;
                break;
            
            default:
                break;
        }
    }
}