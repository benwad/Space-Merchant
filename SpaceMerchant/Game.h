//
//  Game.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
