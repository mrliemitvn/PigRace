//
//  HighScore.h
//  PigRace
//
//  Created by admin on 5/14/14.
//
//

#ifndef PigRace_HighScore_h
#define PigRace_HighScore_h

#include "cocos2d.h"

USING_NS_CC;

class HighScoreScreen : public Layer {
public:
    /* Variables will be used. */
    Label *settingLabel;
    Sprite *bgSettingMenu;
    MenuItemImage *btnOk;
    
    /* Methods will be used. */
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // Create high score screen.
    void createHighScoreScreen();
    
    // Set high score string.
    void setHighScore(Label *label, int score);
    
    // Handle event when click Ok button.
    void menuOkCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HighScoreScreen);
};

#endif
