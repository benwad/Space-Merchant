//
//  Game.cpp
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Game.h"
#include "Planet.h"
#include "Config.h"
#include "drawing.h"

using namespace std;

Game::Game(SDL_Surface *surface, vector2d startCoordinate) : _playerShip(startCoordinate)
{
    _screen = surface;
    _zoomLevel = 1.0;
    
    vector2d marsLocation;
    marsLocation.x = startCoordinate.x + 1000.0;
    marsLocation.y = startCoordinate.y + 1000.0;
    
    _map = new Map();
    _map->generateRandom();
    
    _mapSize.x = 100000;
    _mapSize.y = 100000;
    
    _frame = 0;
    _finished = false;
}

void Game::drawScene()
{
//    SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);
    
    vector2 center;
    
    center.x = (int)(SCREEN_SIZE_X / 2.0);
    center.y = (int)(SCREEN_SIZE_Y / 2.0);
    
    vector<Drawable*> bodies = _map->getObjectsInMapRect(getMapRect());
    
    vector<Drawable*>::iterator i;
    
    for (i = bodies.begin(); i != bodies.end(); i++)
    {
        rectangle updateRect = (*i)->updateRectFromScreenLocation(screenLocationFromMapLocation((*i)->getMapLocation()));
        if ((updateRect.topLeft.x < updateRect.bottomRight.x) &&
            (updateRect.topLeft.y < updateRect.bottomRight.y))
        {
            SDL_Rect sdlUpdateRect = {(Sint16)(updateRect.topLeft.x), (Sint16)(updateRect.topLeft.y),
                (Uint16)(updateRect.bottomRight.x - updateRect.topLeft.x),
                (Uint16)(updateRect.bottomRight.y - updateRect.topLeft.y)};
            SDL_FillRect(SDL_GetVideoSurface(), &sdlUpdateRect, 0);
            Planet *thePlanet = dynamic_cast<Planet*>(*i);
            if (thePlanet != NULL)
            {
                _playerShip.applyGravity(GRAVITY, ((Planet *)*i)->getMapLocation(), ((Planet *)*i)->getRadius());
            }
//            drawRect(_screen, updateRect);
        }
    }
    
    rectangle updateRect = _playerShip.updateRectFromScreenLocation(screenLocationFromMapLocation(_playerShip.getMapLocation()));
    SDL_Rect sdlUpdateRect = {(Sint16)(updateRect.topLeft.x), (Sint16)(updateRect.topLeft.y),
        (Uint16)(updateRect.bottomRight.x - updateRect.topLeft.x),
        (Uint16)(updateRect.bottomRight.y - updateRect.topLeft.y)};
    SDL_FillRect(SDL_GetVideoSurface(), &sdlUpdateRect, 0);
//    drawRect(_screen, updateRect);
    
    for (i = bodies.begin(); i != bodies.end(); i++)
    {
        (*i)->draw(_screen, screenLocationFromMapLocation((*i)->getMapLocation()), 1.0);
    }
    
    _playerShip.draw(_screen, center, _zoomLevel);
    
    drawMiniMap();
    
    SDL_Flip(_screen);
}

void Game::drawMiniMap()
{
    rectangle miniMapRect;
    
    vector2 topLeft;
    topLeft.x = SCREEN_SIZE_X - MINI_MAP_SIZE_X;
    topLeft.y = SCREEN_SIZE_Y - MINI_MAP_SIZE_Y;
    
    miniMapRect.topLeft = topLeft;
    
    vector2 bottomRight;
    bottomRight.x = SCREEN_SIZE_X - 1;
    bottomRight.y = SCREEN_SIZE_Y - 1;
    
    miniMapRect.bottomRight = bottomRight;
    
    pixelcolor white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    
    drawRect(_screen, miniMapRect);
    
    vector<Drawable*> bodies = _map->getAllObjects();
    
    vector<Drawable*>::iterator i;
    
    for (i = bodies.begin(); i != bodies.end(); i++)
    {
        Planet *thePlanet = dynamic_cast<Planet*>(*i);
        if (thePlanet != NULL)
        {
            vector2d planetLocation = thePlanet->getMapLocation();
            vector2 miniLocation;
            miniLocation.x = (miniMapRect.topLeft.x + (int)(planetLocation.x * ((double)MINI_MAP_SIZE_X / (double)_mapSize.x)));
            miniLocation.y = (miniMapRect.topLeft.y + (int)(planetLocation.y * ((double)MINI_MAP_SIZE_Y / (double)_mapSize.y)));
            drawCircle(_screen, miniLocation, thePlanet->getRadius() / 200, white);
        }
    }
    
    vector2 miniPlayerLocation;
    miniPlayerLocation.x = (miniMapRect.topLeft.x + (int)(_playerShip.getMapLocation().x * ((double)MINI_MAP_SIZE_X / (double)_mapSize.x)));
    miniPlayerLocation.y = (miniMapRect.topLeft.y + (int)(_playerShip.getMapLocation().y * ((double)MINI_MAP_SIZE_Y / (double)_mapSize.y)));
    
    drawPixel(_screen, miniPlayerLocation.x, miniPlayerLocation.y, white);
    
}

void Game::update()
{
    _playerShip.updateLocation();
}

rectangle Game::getMapRect()
{
    rectangle mapRect;
    
    vector2 topLeft;
    topLeft.x = _playerShip.getMapLocation().x - (int)(SCREEN_SIZE_X * 2.0);
    topLeft.y = _playerShip.getMapLocation().y - (int)(SCREEN_SIZE_Y * 2.0);
    
    vector2 bottomRight;
    bottomRight.x = _playerShip.getMapLocation().x + (int)(SCREEN_SIZE_X * 2.0);
    bottomRight.y = _playerShip.getMapLocation().y + (int)(SCREEN_SIZE_Y * 2.0);
    
    mapRect.topLeft = topLeft;
    mapRect.bottomRight = bottomRight;
    
    return mapRect;
}

vector2 Game::screenLocationFromMapLocation(vector2d mapLocation)
{
    vector2 center;
    center.x = (int)(SCREEN_SIZE_X / 2.0);
    center.y = (int)(SCREEN_SIZE_Y / 2.0);
    
    vector2d playerMapLocation = _playerShip.getMapLocation();
    
    vector2 screenLocation;
    screenLocation.x = center.x - (playerMapLocation.x - mapLocation.x);
    screenLocation.y = center.y - (playerMapLocation.y - mapLocation.y);
    
    return screenLocation;
}

void Game::mainLoop()
{
    while (!_finished)
    {
        _timer.start();
        
        while (SDL_PollEvent(&_keyevent))
        {
            switch (_keyevent.type) {
                case SDL_KEYDOWN:
                    switch (_keyevent.key.keysym.sym) {
                        case SDLK_LEFT:
                            _playerShip.setRotationSpeed(-0.05);
                            break;
                        case SDLK_RIGHT:
                            _playerShip.setRotationSpeed(0.05);
                            break;
                        case SDLK_UP:
                            _playerShip.applyThrust();
                            break;
                            //                        case SDLK_DOWN:
                            //                            zoomLevel -= 0.1;
                            //                            break;
                        case SDLK_ESCAPE:
                            _finished = true;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (_keyevent.key.keysym.sym) {
                        case SDLK_LEFT:
                            _playerShip.setRotationSpeed(0.0);
                            break;
                        case SDLK_RIGHT:
                            _playerShip.setRotationSpeed(0.0);
                            break;
                        case SDLK_UP:
                            _playerShip.removeThrust();
                            break;
                        default:
                            break;
                    }
                    
                default:
                    break;
            }
        }
        
        update();
        drawScene();
        
        _frame++;
        
//        printf("Framerate: %i\n", (1000 / _timer.get_ticks()));
        
        if (CAP_FRAME_RATE && (_timer.get_ticks() < 1000 / FRAMES_PER_SECOND))
        {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - _timer.get_ticks());
        }
    }
}
