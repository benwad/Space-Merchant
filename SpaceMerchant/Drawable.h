//
//  Drawable.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SpaceMerchant_Drawable_h
#define SpaceMerchant_Drawable_h

#include <SDL/SDL.h>
#include "geometry.h"

class Drawable
{
public:
    virtual void draw(SDL_Surface *screen, vector2 center, double zoomLevel) = 0;
    virtual vector2d getMapLocation() = 0;
    virtual rectangle updateRectFromScreenLocation(vector2 screenLocation) = 0;
};

#endif
