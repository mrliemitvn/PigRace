//
//  GamePlayScreen.h
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#ifndef PigRace_GamePlayScreen_h
#define PigRace_GamePlayScreen_h

#include "cocos2d.h"

USING_NS_CC;

enum {
    firstGround = 1,
    secondGround = 2,
    thirdGround = 3,
    fourthGround = 4
};

class GamePlayScreen : public Layer {
public:
    /* Variables will be used. */
    Label *levelLabel;
    Sprite *bgGame;
    Sprite *bgRoad;
    Sprite *iconPig;
    MenuItemImage *btnJump;
    MenuItemImage *btnUpArrow;
    MenuItemImage *btnDownArrow;
    CCArray *lineArray;
    float roadTimer;
    float roadInterval = 1;
    
    /* Methods will be used. */
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float dt);
    
    // Create game play screen.
    void createGamePlayScreen();
    
    // Add line on road.
    void addLine();
    
    // Remove line on road.
    void removeLine(CCNode *pSender);
    
    // Handle event when click on control buttons.
    void controlButtonCallback(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScreen);
};

#endif
