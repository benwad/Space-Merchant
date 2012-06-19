//
//  PlayerShip.cpp
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PlayerShip.h"
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>

#include "drawing.h"
#include "geometry.h"
#include "Config.h"

PlayerShip::PlayerShip(vector2d mapCoordinate)
{
//    _location = mapCoordinate;
    _location.x = mapCoordinate.x;
    _location.y = mapCoordinate.y;
    _speedx = 0.0;
    _speedy = 0.0;
    _maxspeedx = 8.0;
    _maxspeedy = 8.0;
    _angle = 0.0;
    _rotationSpeed = 0.0;
    _thrust = 0.0;
    _thrustAcceleration = 0.08;
}

void PlayerShip::updateLocation()
{
    _angle += _rotationSpeed;
    
    if (_angle > 360.0)
    {
        _angle -= 360.0;
    }
    
    _speedx += _thrust * sin(_angle);
    _speedy += -(_thrust * cos(_angle));
    
//    printf("Speed: (%.2f, %.2f)\n", _speedx, _speedy);
    
    if (abs(_speedx) > _maxspeedx)
    {
        _speedx = (_speedx > 0.0) ? _maxspeedx : -_maxspeedx;
    }
    
    if (abs(_speedy) > _maxspeedy)
    {
        _speedy = (_speedy > 0.0) ? _maxspeedy : -_maxspeedy;
    }
    
    _location.x += _speedx;
    _location.y += _speedy;
}

void PlayerShip::setRotationSpeed(double rotationSpeed)
{
    _rotationSpeed = rotationSpeed;
}

void PlayerShip::setThrust(double thrust)
{
    _thrust = thrust;
}

void PlayerShip::applyThrust()
{
    setThrust(_thrustAcceleration);
}

void PlayerShip::removeThrust()
{
    setThrust(0.0);
}

double PlayerShip::getSpeedX()
{
    return _speedx;
}

double PlayerShip::getSpeedY()
{
    return _speedy;
}

double PlayerShip::getThrust()
{
    return _thrust;
}

double PlayerShip::getAngle()
{
    return _angle;
}

vector2d PlayerShip::getMapLocation()
{
    return _location;
}

vector2 PlayerShip::getScreenLocation()
{
    vector2 screenLocation;
    screenLocation.x = (int)_location.x;
    screenLocation.y = (int)_location.y;
    
    return screenLocation;
}

rectangle PlayerShip::updateRectFromScreenLocation(vector2 screenLocation)
{
    vector2 topLeft;
    topLeft.x = screenLocation.x - 135;
    topLeft.y = screenLocation.y - 135;
    
    vector2 bottomRight;
    bottomRight.x = screenLocation.x + 135;
    bottomRight.y = screenLocation.y + 135;
    
    rectangle updateRect;
    updateRect.topLeft = topLeft;
    updateRect.bottomRight = bottomRight;
    
    return updateRect;
}

void PlayerShip::applyGravity(double gravity, vector2d origin, double radius)
{
    double dx = _location.x - origin.x;
    double dy = _location.y - origin.y;
    
    double squareDistance = dx*dx + dy*dy;
//    printf("SqDistance: %.2f\n", squareDistance - (radius * radius));
    
    if ((squareDistance < radius*radius * 4.0) && (squareDistance > radius*radius))
    {
        double gravityAngle = atan(fabs(dx) / fabs(dy));
        
        if (_location.y > origin.y)
        {
            // below origin
            if (_location.x > origin.x)
            {
                // to the right of origin
                _speedx -= gravity * sin(gravityAngle);
                _speedy -= gravity * cos(gravityAngle);
            }
            else {
                // to the left of origin
                _speedx += gravity * sin(gravityAngle);
                _speedy -= gravity * cos(gravityAngle);
            }
        }
        else {
            // above origin
            
            if (_location.x > origin.x)
            {
                // to the right of origin
                _speedx -= gravity * sin(gravityAngle);
                _speedy += gravity * cos(gravityAngle);
            }
            else {
                // to the left of origin
                _speedx += gravity * sin(gravityAngle);
                _speedy += gravity * cos(gravityAngle);
            }
        }
        printf("Angle = %.2f\n", gravityAngle);
        printf("dSpeed = (%.2f, %.2f)\n", gravity * sin(gravityAngle), gravity * cos(gravityAngle));
    }
}

// Drawable methods

void PlayerShip::draw(SDL_Surface *screen, vector2 center, double zoomLevel)
{
    int ship_width = floor(32 / zoomLevel);    // @todo: adjust according to zoom level
    int ship_height = floor(32 / zoomLevel);
    
    // initialise line points
    vector2 backLeft;
    backLeft.x = center.x - (int)(ship_width / 2.0);
    backLeft.y = center.y + (int)(ship_height / 2.0);
    
    vector2 front;
    front.x = center.x;
    front.y = center.y - (int)(ship_height / 2.0);
    
    vector2 backRight;
    backRight.x = center.x + (int)(ship_width / 2.0);
    backRight.y = center.y + (int)(ship_height / 2.0);
    
    vector2 backMiddle;
    backMiddle.x = center.x;
    backMiddle.y = center.y + (int)(ship_height / 4.0);
    
    // draw connecting lines
    pixelcolor white;
    white.r = (Uint8)255;
    white.g = (Uint8)255;
    white.b = (Uint8)255;
    
    pixelcolor red;
    red.r = (Uint8)255;
    red.g = (Uint8)0;
    red.b = (Uint8)0;
    
    // thruster drawing
    vector2 thrust;
    thrust.x = front.x;
    thrust.y = backMiddle.y + (int)(_thrust * 500);
    
    rotateVectorAroundCenter(&backLeft, center, _angle);
    rotateVectorAroundCenter(&front, center, _angle);
    rotateVectorAroundCenter(&backRight, center, _angle);
    rotateVectorAroundCenter(&backMiddle, center, _angle);
    rotateVectorAroundCenter(&thrust, center, _angle);
    
    drawLine(screen, backLeft, front, white, 4);
    drawLine(screen, front, backRight, white, 4);
    drawLine(screen, backRight, backMiddle, white, 4);
    drawLine(screen, backMiddle, backLeft, white, 4);
    
    if (_thrust > 0.0)
    {
        drawLine(screen, backLeft, thrust, red, 2);
        drawLine(screen, thrust, backRight, red, 2);
    }
    
    drawSpeedBars(screen);
}

void PlayerShip::drawSpeedBars(SDL_Surface *screen)
{
    vector2 center;
    center.x = (int)(SCREEN_SIZE_X / 2.0);
    center.y = (int)(SCREEN_SIZE_Y / 2.0);
    
    pixelcolor red;
    red.r = 255;
    red.g = 0;
    red.b = 0;
    
    // draw speed x
    if (_speedx > 0.0)
    {
        // draw on the right
        vector2 start;
        start.x = center.x + 75.0;
        start.y = center.y;
        
        vector2 end;
        end.x = (int)(start.x + _speedx * 5);
        end.y = center.y;
        
        drawLine(screen, start, end, red, 3);
        
    }
    else {
        // draw on the left
        vector2 start;
        start.x = center.x - 75.0;
        start.y = center.y;
        
        vector2 end;
        end.x = (int)(start.x + _speedx * 5);
        end.y = center.y;
        
        drawLine(screen, start, end, red, 3);
    }
    
    // draw speed y
    if (_speedy < 0.0)
    {
        // draw on the top
        vector2 start;
        start.x = center.x;
        start.y = center.y - 75.0;
        
        vector2 end;
        end.x = center.x;
        end.y = (int)(start.y + _speedy * 5);
        
        drawLine(screen, start, end, red, 3);
        
    }
    else {
        // draw on the bottom
        vector2 start;
        start.x = center.x;
        start.y = center.y + 75.0;
        
        vector2 end;
        end.x = center.x;
        end.y = (int)(start.y + _speedy * 5);
        
        drawLine(screen, start, end, red, 3);
    }
    
}
