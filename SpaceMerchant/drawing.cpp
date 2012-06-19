//
//  drawing.cpp
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <SDL/SDL.h>
#include <math.h>

#include "drawing.h"
#include "geometry.h"
#include "Config.h"

using namespace std;

static Uint32 white = 0xFFFFFF00;
static Uint32 red = 0x0000FF00;

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color)
{
    if ((x > 0) && (x < SCREEN_SIZE_X))
    {
        if ((y > 0) && (y < SCREEN_SIZE_Y))
        {
            Uint8 * pixel = (Uint8*)surface->pixels;
            pixel += (y * surface->pitch) + (x * sizeof(Uint32));
            *((Uint32*)pixel) = color;
        }
    }
}

void drawPixel(SDL_Surface *screen, int x, int y, pixelcolor pColor)
{
    Uint32 color;
    
    if ((pColor.r == 255) && (pColor.g == 255) && (pColor.b == 255))
    {
        color = white;
    }
    else if ((pColor.r == 255) && (pColor.g == 0) && (pColor.b == 0))
    {
        color = red;
    }
    else {
        color = SDL_MapRGB(screen->format, pColor.r, pColor.g, pColor.b);
    }
    
    PutPixel32_nolock(screen, x, y, color);
}

void drawLine(SDL_Surface *screen, vector2 start, vector2 end, pixelcolor pColor, int thickness)
{
    vector2 lineStart = start;
    vector2 lineEnd = end;
    
    lineStart.x -= (int)floor(thickness / 2.0);
    lineStart.y -= (int)floor(thickness / 2.0);
    
    lineEnd.x -= (int)floor(thickness / 2.0);
    lineEnd.y -= (int)floor(thickness / 2.0);
    
    for (int i=0; i < thickness; i++)
    {
        drawLine(screen, lineStart, lineEnd, pColor);
        
        if (pColor.r > 0)
            pColor.r -= 30;
        if (pColor.g > 0)
            pColor.g -= 30;
        if (pColor.b > 0)
            pColor.b -= 30;
        
        
        lineStart.x += 1;
        lineEnd.x += 1;
        
        drawLine(screen, lineStart, lineEnd, pColor);
        
        lineStart.y += 1;
        lineEnd.y += 1;
    }
}

void drawLine(SDL_Surface *screen, vector2 start, vector2 end, pixelcolor pColor)
{
    double x = end.x - start.x;
    double y = end.y - start.y;
    double length = sqrt(x*x + y*y);
    
    double addx = x / length;
    double addy = y / length;
    
    x = start.x;
    y = start.y;
    
    for (double i = 0; i < length; i += 1)
    {
        drawPixel(screen, (int)x, (int)y, pColor);
        x += addx;
        y += addy;
    }
}

void drawCircle(SDL_Surface *screen, vector2 center, int radius, pixelcolor pColor)
{
    double error = (double)-radius;
    double x = (double)radius - 0.5;
    double y = (double)0.5;
    double cx = center.x - 0.5;
    double cy = center.y - 0.5;
    
//    Uint32 pixel = SDL_MapRGB(screen->format, pColor.r, pColor.g, pColor.b);
    
    while (x >= y)
    {
        drawPixel(screen, (int)(cx + x), (int)(cy + y), pColor);
        drawPixel(screen, (int)(cx + y), (int)(cy + x), pColor);
        
        if (x != 0)
        {
            drawPixel(screen, (int)(cx - x), (int)(cy + y), pColor);
            drawPixel(screen, (int)(cx + y), (int)(cy - x), pColor);
        }
        
        if (y != 0)
        {
            drawPixel(screen, (int)(cx + x), (int)(cy - y), pColor);
            drawPixel(screen, (int)(cx - y), (int)(cy + x), pColor);
        }
        
        if ((x != 0) && (y != 0))
        {
            drawPixel(screen, (int)(cx - x), (int)(cy - y), pColor);
            drawPixel(screen, (int)(cx - y), (int)(cy - x), pColor);
        }
        
        error += y;
        y++;
        error += y;
        
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void drawRect(SDL_Surface *screen, rectangle rect)
{
    vector2 bottomLeft;
    bottomLeft.x = rect.topLeft.x;
    bottomLeft.y = rect.bottomRight.y;
    
    vector2 topRight;
    topRight.x = rect.bottomRight.x;
    topRight.y = rect.topLeft.y;
    
    pixelcolor white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    
    drawLine(screen, rect.topLeft, topRight, white);
    drawLine(screen, topRight, rect.bottomRight, white);
    drawLine(screen, rect.bottomRight, bottomLeft, white);
    drawLine(screen, bottomLeft, rect.topLeft, white);
    
}





