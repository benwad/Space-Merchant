//
//  Map.h
//  SpaceMerchant
//
//  Created by Ben Wadsworth on 18/06/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SpaceMerchant_Map_h
#define SpaceMerchant_Map_h

#include <list>
#include <vector>
#include "Drawable.h"
#include "geometry.h"

using namespace std;

class Map {
    vector<Drawable*> _bodies;
    vector2 _size;
    
public:
    ~Map();
    void addBody(Drawable *body);
    void removeBody(Drawable *body);
    void generateRandom();
    vector<Drawable*>getObjectsInMapRect(rectangle mapRect);
    vector<Drawable*> getAllObjects();
    
};

#endif
