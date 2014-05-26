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

HayStack *HayStack::create() {
    HayStack *haystack = new HayStack();
    if (haystack && haystack->initWithFile("icon_haystack.png")) {
        haystack->minMoveDuration = 2;
        haystack->maxMoveDuration = 4;
        haystack->setTag(HAY_STACK_TYPE);
        haystack->autorelease();
        return haystack;
    }
    CC_SAFE_DELETE(haystack);
    return NULL;
}

Stone *Stone::create() {
    Stone *stone = new Stone();
    if (stone && stone->initWithFile("icon_stone.png")) {
        stone->minMoveDuration = 2;
        stone->maxMoveDuration = 4;
        stone->setTag(STONE_TYPE);
        stone->autorelease();
        return stone;
    }
    CC_SAFE_DELETE(stone);
    return NULL;
}

Cow *Cow::create() {
    Cow *cow = new Cow();
    if (cow && cow->initWithFile("icon_cow_cute.png")) {
        cow->minMoveDuration = 2;
        cow->maxMoveDuration = 4;
        cow->setTag(COW_TYPE);
        cow->autorelease();
        return cow;
    }
    CC_SAFE_DELETE(cow);
    return NULL;
}

Log *Log::create() {
    Log *log = new Log();
    if (log && log->initWithFile("icon_wood.png")) {
        log->minMoveDuration = 2;
        log->maxMoveDuration = 4;
        log->setTag(LOG_TYPE);
        log->autorelease();
        return log;
    }
    CC_SAFE_DELETE(log);
    return NULL;
}

Pumpkin *Pumpkin::create() {
    Pumpkin *pumpkin = new Pumpkin();
    if (pumpkin && pumpkin->initWithFile("icon_pumpkin.png")) {
        pumpkin->minMoveDuration = 2;
        pumpkin->maxMoveDuration = 4;
        pumpkin->setTag(PUMPKIN_TYPE);
        pumpkin->autorelease();
        return pumpkin;
    }
    CC_SAFE_DELETE(pumpkin);
    return NULL;
}
