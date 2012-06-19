//
//  drawing.h
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
