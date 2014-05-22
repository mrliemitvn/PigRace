//
//  Obstacle.h
//  PigRace
//
//  Created by admin on 5/22/14.
//
//

#ifndef PigRace_Obstacle_h
#define PigRace_Obstacle_h

#include "cocos2d.h"

USING_NS_CC;

class Obstacle : public Sprite {
public:
    int minMoveDuration;
    int maxMoveDuration;
    Obstacle *create(const char * pszSpriteFrameName, int minMoveDuration,int MoveDuration);
};

class Stone : public Obstacle {
public:
    static Stone *create();
};

class Log : public Obstacle {
public:
    static Log *create();
};

#endif
