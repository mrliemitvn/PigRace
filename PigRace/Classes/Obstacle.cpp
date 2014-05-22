//
//  Obstacle.cpp
//  PigRace
//
//  Created by admin on 5/22/14.
//
//

#include "Obstacle.h"

Obstacle *Obstacle::create(const char *pszSpriteFrameName, int minMoveDuration, int MoveDuration) {
    Obstacle *obstacle = new Obstacle();
    if (obstacle && obstacle->initWithFile(pszSpriteFrameName)) {
        obstacle->minMoveDuration = minMoveDuration;
        obstacle->maxMoveDuration = maxMoveDuration;
        obstacle->autorelease();
        return obstacle;
    }
    CC_SAFE_DELETE(obstacle);
    return NULL;
}

Stone *Stone::create() {
    Stone *stone = new Stone();
    if (stone && stone->initWithFile("icon_stone.png")) {
        stone->minMoveDuration = 3;
        stone->maxMoveDuration = 5;
        stone->autorelease();
        return stone;
    }
    CC_SAFE_DELETE(stone);
    return NULL;
}

//Strawberry *Strawberry::create() {
//    Strawberry *strawberry = new Strawberry();
//    if (strawberry && strawberry->initWithFile("icon_strawberry.png")) {
//        strawberry->coin = 20;
//        strawberry->minMoveDuration = 3;
//        strawberry->maxMoveDuration = 5;
//        strawberry->autorelease();
//        return strawberry;
//    }
// CC_SAFE_DELETE(strawberry);
//return NULL;
//}