//
//  GamePlayScreen.cpp
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#include "GamePlayScreen.h"
#include "Line.h"

USING_NS_CC;

Scene* GamePlayScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayScreen::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create game play screen.
    createGamePlayScreen();
    
    lineArray = CCArray::create();
    lineArray->retain();
    
    this->scheduleUpdate();
    
    return true;
}

/*
 * Create game play screen.
 */
void GamePlayScreen::createGamePlayScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    ///////////////////////////////////
    // add background.
    //////////////////////////////////
    
    // First background.
    bgGame = Sprite::create("bg_game_play.png");
    
    // position the sprite on the center of the screen
    bgGame->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgGame, firstGround);
    
    // Add background of road.
    bgRoad = Sprite::create("bg_game_play_road.png");
    
    // position the sprite on the center of the screen
    bgRoad->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float roadHeight = visibleSize.height / 5 * 3;
    bgRoad->setScale(visibleSize.width / bgRoad->getContentSize().width, roadHeight / bgRoad->getContentSize().height);
    this->addChild(bgRoad, secondGround);
    
    //////////////////////////////////
    // Add control buttons.
    //////////////////////////////////
    // Jump button.
    btnJump = MenuItemImage::create("btn_jump_off.png", "btn_jump_on.png", CC_CALLBACK_1(GamePlayScreen::controlButtonCallback, this));
    btnJump->setScale(40 / btnJump->getContentSize().width);
    btnJump->setPosition(Point(20 + 10, visibleSize.height / 10));
    
    // Arrow buttons.
    btnUpArrow = MenuItemImage::create("btn_arrow_up_off.png", "btn_arrow_up_on.png", CC_CALLBACK_1(GamePlayScreen::controlButtonCallback, this));
    btnDownArrow = MenuItemImage::create("btn_arrow_down_off.png", "btn_arrow_down_on.png", CC_CALLBACK_1(GamePlayScreen::controlButtonCallback, this));
    btnUpArrow->setScale(40 / btnUpArrow->getContentSize().width);
    btnDownArrow->setScale(40 / btnDownArrow->getContentSize().width);
    btnDownArrow->setPosition(Point(visibleSize.width - 20 - 10, visibleSize.height / 10));
    btnUpArrow->setPosition(Point(btnDownArrow->getPosition().x - 40 - 5, visibleSize.height / 10));
    
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnJump, btnUpArrow, btnDownArrow, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, thirdGround);
    
    //////////////////////////////////
    // Add icon pig.
    //////////////////////////////////
    iconPig = Sprite::create("icon_pig.png");
    float scale = 50 / iconPig->getContentSize().height;
    iconPig->setScale(scale);
    iconPig->setPosition(Point(iconPig->getContentSize().width * scale / 2 + 5, visibleSize.height / 2));
    this->addChild(iconPig, fourthGround);
}

void GamePlayScreen::update(float dt) {
    roadTimer+=dt;
    if (roadTimer >= roadInterval)
    {
        roadTimer = 0;
        this->addLine();
    }
}

void GamePlayScreen::addLine() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //Add 2 line object.
    Line *line1 = NULL;
    Line *line2 = NULL;
    line1 = Line::create();
    line1->setTag(1);
    line2 = Line::create();
    line2->setTag(3);
    //Xac dinh vi tri xuat hien 2 giai phan cach theo truc Y
    line1->setPosition(Point(visibleSize.width + line1->getContentSize().width / 2, visibleSize.height / 5 * 3));
    line2->setPosition(Point(visibleSize.width + line2->getContentSize().width / 2, visibleSize.height / 5 * 2));
    line1->setScale(5 / line1->getContentSize().height);
    line2->setScale(5 / line2->getContentSize().height);
    this->addChild(line1, thirdGround);
    this->addChild(line2, thirdGround);
    //Xac dinh toc do quai vat
    int minDuration = line1->minMoveDuration;
    int maxDuration = line1->maxMoveDuration;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = rangeDuration + minDuration;
    
    lineArray->addObject(line1);
    // Su chuyen dong cua giai phan cach
    CCAction *_actionMoveLine1=CCSequence::create(CCMoveTo::create(actualDuration, ccp(-visibleSize.width*0.05f, visibleSize.height / 5 * 3)),
                                             CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeLine)) ,NULL);
    CCAction *_actionMoveLine2=CCSequence::create(CCMoveTo::create(actualDuration, ccp(-visibleSize.width*0.05f, visibleSize.height / 5 * 2)),
                                                  CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeLine)) ,NULL);
    line1->runAction((CCAction*)_actionMoveLine1);
    line2->runAction((CCAction*)_actionMoveLine2);
}

void GamePlayScreen::removeLine(CCNode *pSender) {
    lineArray->removeObject(pSender);
    pSender->removeFromParentAndCleanup(true);
}

/* 
 * Handle event when click on control button.
 */
void GamePlayScreen::controlButtonCallback(cocos2d::Ref *pSender) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (pSender->_ID == btnUpArrow->_ID) {
        float positionTop = visibleSize.height * 7 / 10;
        if (iconPig->getPosition().y >= positionTop) return;
        iconPig->setPosition(iconPig->getPosition().x, iconPig->getPosition().y + visibleSize.height / 5);
    } else if (pSender->_ID == btnDownArrow->_ID) {
        float positionBottom = visibleSize.height * 3 / 10;
        if (iconPig->getPosition().y <= positionBottom) return;
        iconPig->setPosition(iconPig->getPosition().x, iconPig->getPosition().y - visibleSize.height / 5);
    }
}