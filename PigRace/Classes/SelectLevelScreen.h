//
//  SelectLevelScreen.h
//  PigRace
//
//  Created by admin on 5/15/14.
//
//

#ifndef PigRace_SelectLevelScreen_h
#define PigRace_SelectLevelScreen_h

#include "cocos2d.h"

USING_NS_CC;

class SelectLevelScreen : public Layer {
public:
    /* Variables will be used. */
    Label *selectLevelLabel;
    Sprite *bgLevel;
    MenuItemImage *menuCancel;
    MenuItemImage *menuArray[10];
    
    /* Methods will be used. */
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // Create select level screen.
    void createSelectLevelScreen();
    
    // Create level buttons.
    void createLevelButtons();
    
    // Handle event when click menu button.
    void menuCallback(Ref* pSender);
    
    // Handle event when click cancel button.
    void menuCancelCallback(Ref *pSender);
    
    // Handle event when click each level button.
    void menuLevelCallback(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SelectLevelScreen);
};

#endif
