//
//  SelectLevelScreen.cpp
//  PigRace
//
//  Created by admin on 5/15/14.
//
//

#include "SelectLevelScreen.h"
#include "GamePlayScreen.h"
#include "Consts.h"

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
    
    // Add Ok button.
    menuCancel = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(SelectLevelScreen::menuCancelCallback, this));
    menuCancel->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + menuCancel->getContentSize().height));
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(menuCancel, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    // Menu background.
    bgLevel = Sprite::create("bg_tutorial.png");
    
    float width = visibleSize.width - 20;
    float height = visibleSize.height - menuCancel->getContentSize().height * 2 - selectLevelLabel->getContentSize().height * 2;
    bgLevel->setScale(width / bgLevel->getContentSize().width, height / bgLevel->getContentSize().height);
    // position the sprite on the center of the screen
    bgLevel->setPosition(Point(visibleSize.width/2 + origin.x, origin.y + visibleSize.height / 2));
    
    // add the sprite as a child to this layer
    this->addChild(bgLevel, 1);
    
    // Create level buttons.
    createLevelButtons();
    
}

/*
 * Create and add list level buttons.
 */
void SelectLevelScreen::createLevelButtons() {
    // create menu, it's an autorelease object
    Menu *menu = Menu::create();
    menu->setPosition(Point::ZERO);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float bgListMenuHeight = visibleSize.height - menuCancel->getContentSize().height * 2 - selectLevelLabel->getContentSize().height * 2;
    float btnLevelHeight = bgListMenuHeight / 5;
    Label *labelArray[10];
    for (int i = 0; i < 10; i++) {
        menuArray[i] = MenuItemImage::create("btn_wooden_off.png", "btn_wooden_on.png", "btn_wooden_on.png",
                                             CC_CALLBACK_1(SelectLevelScreen::menuLevelCallback, this));
        menuArray[i]->setScale(btnLevelHeight * 725 / 242 / menuArray[i]->getContentSize().width,
                               btnLevelHeight / menuArray[i]->getContentSize().height);
        char health[100];
        sprintf(health,"Level %i", i + 1);
        labelArray[i] = Label::createWithSystemFont("", "Marker Felt", btnLevelHeight - 10);
        labelArray[i]->setString(health);
        labelArray[i]->setColor(Color3B::WHITE);
        if (i == 0) {
            menuArray[i]->setPosition(Point(bgLevel->getPosition().x - btnLevelHeight * 725 / 242 / 2,
                                            bgLevel->getPosition().y + bgListMenuHeight * 2 / 5));
        } else if (i == 5) {
            menuArray[i]->setPosition(Point(bgLevel->getPosition().x + btnLevelHeight * 725 / 242 / 2,
                                            bgLevel->getPosition().y + bgListMenuHeight * 2 / 5));
        } else {
            menuArray[i]->setPosition(Point(menuArray[i-1]->getPosition().x, menuArray[i-1]->getPosition().y - btnLevelHeight));
        }
        labelArray[i]->setPosition(Point(menuArray[i]->getPosition().x, menuArray[i]->getPosition().y));
        this->addChild(labelArray[i], 3);
        menuArray[i]->setTag(i + 1);
        menu->addChild(menuArray[i]);
    }
    
    int nextLevel = UserDefault::getInstance()->getIntegerForKey(NEXT_LEVEL, 1);
    for (int i = 0; i < nextLevel; i++) {
        menuArray[i]->setEnabled(true);
        labelArray[i]->setColor(Color3B::WHITE);
    }
    for (int i = nextLevel; i < 10; i++) {
        menuArray[i]->setEnabled(false);
        labelArray[i]->setColor(Color3B::GRAY);
    }
    this->addChild(menu, 2);
}

/*
 * Handle event when click cancel button.
 */
void SelectLevelScreen::menuCancelCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}

/*
 * Handle event when click each level button.
 */
void SelectLevelScreen::menuLevelCallback(cocos2d::Ref *pSender) {
    UserDefault::getInstance()->setIntegerForKey(CURRENT_LEVEL, ((MenuItemImage*) pSender)->getTag());
    Director::getInstance()->popScene();
    Scene *gamePlayScreen = GamePlayScreen::createScene();
    Director::getInstance()->pushScene(gamePlayScreen);
}