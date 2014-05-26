//
//  Obstacle.h
//  PigRace
//
//  Created by admin on 5/22/14.
//
//

#ifndef PigRace_Obstacle_h
#define PigRace_Obstacle_h

#define HAY_STACK_TYPE 0
#define STONE_TYPE 1
#define COW_TYPE 2
#define LOG_TYPE 3
#define PUMPKIN_TYPE 4

#include "cocos2d.h"

USING_NS_CC;

class Obstacle : public Sprite {
public:
    int minMoveDuration;
    int maxMoveDuration;
    Obstacle *create(const char * pszSpriteFrameName, int minMoveDuration,int MoveDuration);
};

class HayStack : public Obstacle {
public:
    static HayStack *create();
};

class Stone : public Obstacle {
public:
    static Stone *create();
};

class Cow : public Obstacle {
public:
    static Cow *create();
};

class Log : public Obstacle {
public:
    static Log *create();
};

class Pumpkin : public Obstacle {
public:
    static Pumpkin *create();
};

#endif
