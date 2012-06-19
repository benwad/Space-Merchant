//
//  Game.h
//  SpaceMerchant
//
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

#ifndef SpaceMerchant_Game_h
#define SpaceMerchant_Game_h

#include <SDL/SDL.h>
#include <time.h>
#include "PlayerShip.h"
#include "Map.h"
#include "Timer.h"

class Game {
    SDL_Surface *_screen;
    SDL_Event _keyevent;
    
    PlayerShip _playerShip;
    Map *_map;
    
    vector2 _mapSize;
    
    double _zoomLevel;
    bool _finished;
    int _frame;
    Timer _timer;
    
public:
    Game(SDL_Surface *screen, vector2d startCoordinate);
    void mainLoop();
    void drawScene();
    void drawMiniMap();
    void update();
    rectangle getMapRect();
    vector2 screenLocationFromMapLocation(vector2d mapLocation);
};

#endif
