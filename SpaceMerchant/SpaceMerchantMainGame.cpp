//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 Ben Wadsworth
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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