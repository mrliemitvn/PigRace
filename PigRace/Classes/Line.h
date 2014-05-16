//
//  Line.h
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#ifndef PigRace_Line_h
#define PigRace_Line_h

#include "cocos2d.h"

USING_NS_CC;

class Line : public Sprite {
public:
    int minMoveDuration;
    int maxMoveDuration;
    static Line *create();
};

#endif
