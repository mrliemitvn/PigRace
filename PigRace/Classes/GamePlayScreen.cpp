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
    
    // add background.
    bgGame = Sprite::create("bg_game_play.png");
    
    // position the sprite on the center of the screen
    bgGame->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgGame, 0);
    
    // Add background of road.
    bgRoad = Sprite::create("bg_game_play_road.png");
    
    // position the sprite on the center of the screen
    bgRoad->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float roadHeight = visibleSize.height / 5 * 3;
    bgRoad->setScale(visibleSize.width / bgRoad->getContentSize().width, roadHeight / bgRoad->getContentSize().height);
    this->addChild(bgRoad, 1);
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
    this->addChild(line1, 2);
    this->addChild(line2, 2);
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