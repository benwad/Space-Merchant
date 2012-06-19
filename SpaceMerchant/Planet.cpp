//
//  Planet.cpp
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

#include <iostream>

#include "Planet.h"
#include "drawing.h"
#include "Config.h"

Planet::Planet(double radius, vector2d mapLocation)
{
    _radius = radius;
    _mapLocation = mapLocation;
}

void Planet::draw(SDL_Surface *screen, vector2 center, double zoomLevel)
{
    pixelcolor pColor;
    pColor.r = 255;
    pColor.g = 0;
    pColor.b = 0;
    
    for (int i=0; i < 5; i++)
    {
        drawCircle(screen, center, _radius + i, pColor);
        
//        pColor.r -= 5;
//        pColor.g *= 5;
//        pColor.b *= 5;
    }
    
//    rectangle updateRect = updateRectFromScreenLocation(center);
//    SDL_Rect sdlUpdateDect = 
}

rectangle Planet::updateRectFromScreenLocation(vector2 screenLocation)
{
    vector2 topLeft;
    topLeft.x = (int)(screenLocation.x - _radius - 51.0);
    topLeft.y = (int)(screenLocation.y - _radius - 51.0);
    
    vector2 bottomRight;
    bottomRight.x = (int)(screenLocation.x + _radius + 51.0);
    bottomRight.y = (int)(screenLocation.y + _radius + 51.0);
    
    if (topLeft.x < 0)
        topLeft.x = 1;
    if (topLeft.y < 0)
        topLeft.y = 1;
    if (bottomRight.x > SCREEN_SIZE_X)
        bottomRight.x = SCREEN_SIZE_X - 1;
    if (bottomRight.y > SCREEN_SIZE_Y)
        bottomRight.y = SCREEN_SIZE_Y - 1;
    
    rectangle updateRect;
    updateRect.topLeft = topLeft;
    updateRect.bottomRight = bottomRight;
    
    return updateRect;
}

vector2d Planet::getMapLocation()
{
    return _mapLocation;
}

double Planet::getRadius()
{
    return _radius;
}