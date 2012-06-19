//
//  geometry.cpp
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
#include "geometry.h"

double distanceBetweenPoints(vector2 p1, vector2 p2)
{
    double dx = abs(p2.x - p1.x);
    double dy = abs(p2.y - p1.y);
    
    return sqrt(dx*dx + dy*dy);
}

void rotateVectorAroundCenter(vector2 *point, vector2 center, double angle)
{
    int px = point->x - center.x;
    int py = point->y - center.y;
    
    float s = sin(angle);
    float c = cos(angle);
    
    float xnew = px * c - py * s;
    float ynew = px * s + py * c;
    
    point->x = xnew + center.x;
    point->y = ynew + center.y;
}