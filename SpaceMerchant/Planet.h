//
//  Planet.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SpaceMerchant_Planet_h
#define SpaceMerchant_Planet_h

#include "Drawable.h"
#include "geometry.h"

class Planet : public Drawable {
    vector2d _mapLocation;
    double _radius;
    
public:
    Planet(double radius, vector2d mapLocation);
    vector2d getMapLocation();
    double getRadius();
    
    void draw(SDL_Surface *screen, vector2 center, double zoomLevel);
    rectangle updateRectFromScreenLocation(vector2 screenLocation);
};

#endif
