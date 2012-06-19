//
//  geometry.cpp
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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