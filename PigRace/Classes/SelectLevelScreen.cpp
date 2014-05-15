//
//  SelectLevelScreen.cpp
//  PigRace
//
//  Created by admin on 5/15/14.
//
//

#include "SelectLevelScreen.h"

USING_NS_CC;

Scene* SelectLevelScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectLevelScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevelScreen::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create select level screen.
    createSelectLevelScreen();
    
    return true;
}

/*
 * Create select level screen.
 */
void SelectLevelScreen::createSelectLevelScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add background.
    auto bg = Sprite::create("bg.png");
    
    // position the sprite on the center of the screen
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bg, 0);
    
    // add a label shows "Select level"
    // create and initialize a label
    selectLevelLabel = Label::createWithSystemFont("Select level", "Marker Felt", 30);
    
    selectLevelLabel->setScale(2.0);
    selectLevelLabel->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    selectLevelLabel->setPosition(Point(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height - selectLevelLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(selectLevelLabel, 1);
    
    // Menu background.
    bgLevel = Sprite::create("bg_tutorial.png");
    
    // position the sprite on the center of the screen
    bgLevel->setPosition(Point(visibleSize.width/2 + origin.x, origin.y
                                     + visibleSize.height - selectLevelLabel->getContentSize().height*3
                                     - bgLevel->getContentSize().height/2));
    
    // add the sprite as a child to this layer
    this->addChild(bgLevel, 1);
    
    // Add Ok button.
    auto btnCancel = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(SelectLevelScreen::menuCancelCallback, this));
    btnCancel->setPosition(Point(origin.x + visibleSize.width / 2,
                             origin.y + btnCancel->getContentSize().height));
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnCancel, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

/*
 * Handle event when click cancel button.
 */
void SelectLevelScreen::menuCancelCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}