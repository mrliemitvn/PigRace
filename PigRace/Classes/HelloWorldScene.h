#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    /* Variables will be used. */
    Sprite *gameLabel;
    Menu *menu;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // Create game screen.
    void createGameScreen();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // Handle event when click on setting button.
    void menuSettingCallback(Ref *pSender);
    
    // Handle event when click on high score button.
    void menuHighScoreCallback(Ref *pSender);
    
    // Handle event when click on tutorial button.
    void menuTutorialCallback(Ref *pSender);
    
    // Handle event when click on start button.
    void menuStartCallback(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
