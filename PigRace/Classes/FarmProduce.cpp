//
//  FarmProduce.cpp
//  PigRace
//
//  Created by admin on 5/21/14.
//
//

#include "FarmProduce.h"

FarmProduce *FarmProduce::create(const char *pszSpriteFrameName, int coin, int minMoveDuration, int MoveDuration) {
    FarmProduce *farmProduce = new FarmProduce();
    if (farmProduce && farmProduce->initWithFile(pszSpriteFrameName)) {
        farmProduce->coin = coin;
        farmProduce->minMoveDuration = minMoveDuration;
        farmProduce->maxMoveDuration = maxMoveDuration;
        farmProduce->autorelease();
        return farmProduce;
    }
    CC_SAFE_DELETE(farmProduce);
    return NULL;
}

Carrot *Carrot::create() {
    Carrot *carrot = new Carrot();
    if (carrot && carrot->initWithFile("icon_carrot.png")) {
        carrot->coin = 10;
        carrot->minMoveDuration = 2;
        carrot->maxMoveDuration = 4;
        carrot->autorelease();
        return carrot;
    }
    CC_SAFE_DELETE(carrot);
    return NULL;
}

Strawberry *Strawberry::create() {
    Strawberry *strawberry = new Strawberry();
    if (strawberry && strawberry->initWithFile("icon_strawberry.png")) {
        strawberry->coin = 20;
        strawberry->minMoveDuration = 2;
        strawberry->maxMoveDuration = 4;
        strawberry->autorelease();
        return strawberry;
    }
    CC_SAFE_DELETE(strawberry);
    return NULL;
}

Apple *Apple::create() {
    Apple *apple = new Apple();
    if (apple && apple->initWithFile("icon_apple.png")) {
        apple->coin = 30;
        apple->minMoveDuration = 2;
        apple->maxMoveDuration = 4;
        apple->autorelease();
        return apple;
    }
    CC_SAFE_DELETE(apple);
    return NULL;
}