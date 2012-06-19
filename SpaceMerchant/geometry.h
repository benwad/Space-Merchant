//
//  geometry.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SpaceMerchant_geometry_h
#define SpaceMerchant_geometry_h

#include <math.h>

struct vector2 {
    int x;
    int y;
};

struct vector2d {
    double x;
    double y;
};

struct rectangle {
    vector2 topLeft;
    vector2 bottomRight;
};

double distanceBetweenPoints(vector2 p1, vector2 p2);

void rotateVectorAroundCenter(vector2 *point, vector2 center, double angle);

#endif
