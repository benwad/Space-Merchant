//
//  Map.cpp
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
#include <stdlib.h>
#include <time.h>

#include "Planet.h"

#include "Map.h"

using namespace std;

Map::~Map()
{
    vector<Drawable*> objects;
    
    vector<Drawable*>::iterator i;
    
    for (i = _bodies.begin(); i != _bodies.end(); i++)
    {
        (*i)->~Drawable();
    }
    
}

void Map::addBody(Drawable *body)
{
    _bodies.push_back(body);
}

void Map::removeBody(Drawable *body)
{
    // @todo: do this
}

void Map::generateRandom()
{
    srand(time(NULL));
    int numPlanets = 1000;
    
    for (int i=0; i < numPlanets; i++)
    {
        double radius = rand() % 800 + 1;
        vector2d mapLocation;
        mapLocation.x = rand() % 100000 + 1;
        mapLocation.y = rand() % 100000 + 1;
        
        Planet *newPlanet = new Planet(radius, mapLocation);
        addBody(newPlanet);
    }
}

vector<Drawable*> Map::getObjectsInMapRect(rectangle mapRect)
{
    vector<Drawable*> objects;
    
    vector<Drawable*>::iterator i;
    
    for (i = _bodies.begin(); i != _bodies.end(); i++)
    {
        if (((*i)->getMapLocation().x > mapRect.topLeft.x) &&
            ((*i)->getMapLocation().x < mapRect.bottomRight.x) &&
            ((*i)->getMapLocation().y > mapRect.topLeft.y) &&
            ((*i)->getMapLocation().y < mapRect.bottomRight.y))
        {
            objects.push_back(*i);
        }
    }
    
    return objects;
}

vector<Drawable*> Map::getAllObjects()
{
    return _bodies;
}