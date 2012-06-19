//
//  drawing.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SpaceMerchant_drawing_h
#define SpaceMerchant_drawing_h

#include "geometry.h"

struct pixelcolor {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
void drawPixel(SDL_Surface *screen, int x, int y, pixelcolor pColor);
void drawLine(SDL_Surface *screen, vector2 start, vector2 end, pixelcolor pColor);
void drawLine(SDL_Surface *screen, vector2 start, vector2 end, pixelcolor pColor, int thickness);
void drawCircle(SDL_Surface *screen, vector2 center, int radius, pixelcolor pColor);
void drawRect(SDL_Surface *screen, rectangle rect);

#endif
