//
//  TutorialScreen.h
//  PigRace
//
//  Created by admin on 5/14/14.
//
//

#ifndef PigRace_TutorialScreen_h
#define PigRace_TutorialScreen_h

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

//USING_NS_CC_EXT;

class TutorialScreen : public Layer {
public:
    /* Variables will be used. */
    Label *tutorialLabel;
    Sprite *bgTutorialMenu;
    MenuItemImage *btnOk;
//    ScrollView *scrollView;
    
    /* Methods will be used. */
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // Create tutorial screen.
    void createTutorialScreen();
    
    // Handle event when click Ok button.
    void menuOkCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TutorialScreen);
};

#endif
