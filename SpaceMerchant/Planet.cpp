//
//  Planet.cpp
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Planet.h"
#include "drawing.h"

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
    
    for (int i=0; i < 51; i++)
    {
        drawCircle(screen, center, _radius + i, pColor);
        
        pColor.r -= 5;
//        pColor.g *= 5;
//        pColor.b *= 5;
    }
}

vector2d Planet::getMapLocation()
{
    return _mapLocation;
}

double Planet::getRadius()
{
    return _radius;
}