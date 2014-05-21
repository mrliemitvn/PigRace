//
//  FarmProduce.h
//  PigRace
//
//  Created by admin on 5/21/14.
//
//

#ifndef PigRace_FarmProduce_h
#define PigRace_FarmProduce_h

#include "cocos2d.h"

USING_NS_CC;

class FarmProduce : public Sprite {
public:
    int coin;
    int minMoveDuration;
    int maxMoveDuration;
    FarmProduce *create(const char * pszSpriteFrameName, int coin, int minMoveDuration,int MoveDuration);
};

class Carrot : public FarmProduce {
public:
    static Carrot *create();
};

class Strawberry : public FarmProduce {
public:
    static Strawberry *create();
};

#endif
