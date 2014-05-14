//
//  TutorialScreen.cpp
//  PigRace
//
//  Created by admin on 5/14/14.
//
//

#include "TutorialScreen.h"

USING_NS_CC;

Scene* TutorialScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TutorialScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TutorialScreen::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create tutorial screen.
    createTutorialScreen();
    
    return true;
}

/*
 * Create tutorial screen.
 * Add features: label, menu background, buttons.
 */
void TutorialScreen::createTutorialScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add background.
    auto bgTutorial = Sprite::create("bg.png");
    
    // position the sprite on the center of the screen
    bgTutorial->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgTutorial, 0);
    
    // add a label shows "Tutorial"
    // create and initialize a label
    tutorialLabel = Label::createWithSystemFont("Tutorial", "Arial", 30);
    
    tutorialLabel->setScale(2.0);
    // position the label on the center of the screen
    tutorialLabel->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - tutorialLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(tutorialLabel, 1);
    
    // Add Ok button.
    btnOk = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(TutorialScreen::menuOkCallback, this));
    btnOk->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + btnOk->getContentSize().height));
    
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnOk, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    // Menu background.
    bgTutorialMenu = Sprite::create("bg_tutorial.png");
    
    // position the sprite on the center of the screen
    bgTutorialMenu->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    float width = visibleSize.width - 20;
    float height = visibleSize.height - btnOk->getContentSize().height * 2 - tutorialLabel->getContentSize().height * 2;
    bgTutorialMenu->setScale(width / bgTutorialMenu->getContentSize().width, height / bgTutorialMenu->getContentSize().height);
    
    // add the sprite as a child to this layer
    this->addChild(bgTutorialMenu, 1);
    
}

/*
 * Close this screen when click Ok button.
 */
void TutorialScreen::menuOkCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}