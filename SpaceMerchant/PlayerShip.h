//
//  PlayerShip.h
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

#ifndef SpaceMerchant_PlayerShip_h
#define SpaceMerchant_PlayerShip_h

//#include "geometry.h"
#include "Drawable.h"

class PlayerShip : public Drawable {
    vector2d _location;
    double _rotationSpeed;
    double _angle;
    double _thrust;
    double _speedx, _speedy;
    double _maxspeedx, _maxspeedy;
    double _thrustAcceleration;
    
public:
    PlayerShip(vector2d mapCoordinate);
    
    void updateLocation();
    
    void setRotationSpeed(double rotationSpeed);
    void setThrust(double thrust);
    void applyGravity(double gravity, vector2d origin, double radius);
    void applyThrust();
    void removeThrust();
    
    double getSpeedX();
    double getSpeedY();
    double getThrust();
    double getAngle();
    vector2d getMapLocation();
    vector2 getScreenLocation();
    
    void draw(SDL_Surface *screen, vector2 center, double zoomLevel);
    rectangle updateRectFromScreenLocation(vector2 screenLocation);
    void drawSpeedBars(SDL_Surface *screen);
};

#endif
