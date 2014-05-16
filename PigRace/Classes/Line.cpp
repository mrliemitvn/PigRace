//
//  Line.cpp
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#include "Line.h"

Line *Line::create(){
    Line *line = new Line();
    if (line && line->initWithFile("icon_line.png"))
    {
        line->minMoveDuration=2;
        line->maxMoveDuration=4;
        line->autorelease();
        return line;
    }
    CC_SAFE_DELETE(line);
    return NULL;
}