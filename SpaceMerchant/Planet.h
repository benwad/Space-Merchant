//
//  Planet.h
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
