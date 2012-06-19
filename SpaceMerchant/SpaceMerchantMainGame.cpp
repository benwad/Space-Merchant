#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <math.h>

#include "geometry.h"
#include "drawing.h"
#include "Config.h"
#include "PlayerShip.h"
#include "Game.h"

using namespace std;

int main( int argc, char* args[] )
{
    SDL_Surface* screen = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );
    if (FULL_SCREEN)
        screen = SDL_SetVideoMode( SCREEN_SIZE_X, SCREEN_SIZE_Y, 32, (SDL_HWSURFACE | SDL_FULLSCREEN) );
    else screen = SDL_SetVideoMode( SCREEN_SIZE_X, SCREEN_SIZE_Y, 32, SDL_HWSURFACE );
    
    vector2d startCoordinate;
    startCoordinate.x = 5000;
    startCoordinate.y = 5000;
    
    Game game(screen, startCoordinate);
    game.mainLoop();
    
    SDL_Quit();
    
    return 0;
}