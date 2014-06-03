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
    bgTutorial->setScale(visibleSize.width / bgTutorial->getContentSize().width);
    
    // position the sprite on the center of the screen
    bgTutorial->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgTutorial, 0);
    
    // add a label shows "Tutorial"
    // create and initialize a label
    tutorialLabel = Label::createWithSystemFont("Tutorial", "Marker Felt", 30);
    
    tutorialLabel->setScale(2.0);
    tutorialLabel->setColor(Color3B::YELLOW);
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
    
    // Add guide.
    auto textAreaSize = CCSizeMake(visibleSize.width - 165, 50);
    auto btnArrowUp = Sprite::create("btn_arrow_up_off.png");
    auto btnArrowDown = Sprite::create("btn_arrow_down_off.png");
    auto btnJump = Sprite::create("btn_jump_off.png");
    
    btnArrowUp->setPosition(Point(origin.x + 10 + 40 / 2,
                                  visibleSize.height - tutorialLabel->getContentSize().height * 2 - 20));
    btnArrowUp->setScale(40 / btnArrowUp->getContentSize().width, 40 / btnArrowUp->getContentSize().height);
    btnArrowDown->setPosition(Point(btnArrowUp->getPosition().x + 40, btnArrowUp->getPosition().y));
    btnArrowDown->setScale(40 / btnArrowDown->getContentSize().width, 40 / btnArrowDown->getContentSize().height);
    btnJump->setPosition(Point(btnArrowDown->getPosition().x + 40, btnArrowDown->getPosition().y));
    btnJump->setScale(40 / btnJump->getContentSize().width, 40 / btnJump->getContentSize().height);
    
    auto controlLabel = CCLabelTTF::create("Use these buttons to control the pig", "Marker Felt", 25,
                                           textAreaSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    controlLabel->setColor(Color3B::BLACK);
    controlLabel->setPosition(Point(btnJump->getPosition().x + 25, btnJump->getPosition().y - 12.5));
    controlLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    controlLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    
    auto iconCarrot = Sprite::create("icon_carrot.png");
    auto iconStrawberry = Sprite::create("icon_strawberry.png");
    iconCarrot->setPosition(Point(btnArrowUp->getPosition().x, controlLabel->getPosition().y - 30 - iconCarrot->getContentSize().height / 2));
    iconStrawberry->setPosition(Point(iconCarrot->getPosition().x + iconStrawberry->getContentSize().width + 5,
                                      controlLabel->getPosition().y - 30 - iconCarrot->getContentSize().height / 2));
    
    auto collectLabel = CCLabelTTF::create("Collect farm produces to get more coins", "Marker Felt", 25,
                                           textAreaSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    collectLabel->setColor(Color3B::BLACK);
    collectLabel->setPosition(Point(controlLabel->getPosition().x, controlLabel->getPosition().y - textAreaSize.height - 5));
    collectLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    collectLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    
    auto iconStone = Sprite::create("icon_stone.png");
    iconStone->setPosition(Point(20 + 69 / 2, collectLabel->getPosition().y - 30 - 20));
    iconStone->setScale(69 / iconStone->getContentSize().width, 40 / iconStone->getContentSize().height);
    
    auto evadeLabel = CCLabelTTF::create("Evade all obstructions", "Marker Felt", 25, textAreaSize,
                                         kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    evadeLabel->setColor(Color3B::BLACK);
    evadeLabel->setPosition(Point(collectLabel->getPosition().x, collectLabel->getPosition().y - textAreaSize.height - 5));
    evadeLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    evadeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    
    this->addChild(btnArrowUp, 2);
    this->addChild(btnArrowDown, 2);
    this->addChild(btnJump, 2);
    this->addChild(controlLabel, 2);
    this->addChild(iconCarrot, 2);
    this->addChild(iconStrawberry, 2);
    this->addChild(collectLabel, 2);
    this->addChild(iconStone, 2);
    this->addChild(evadeLabel, 2);
}

/*
 * Close this screen when click Ok button.
 */
void TutorialScreen::menuOkCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}