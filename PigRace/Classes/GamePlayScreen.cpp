//
//  GamePlayScreen.cpp
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#include "GamePlayScreen.h"
#include "Line.h"
#include "FarmProduce.h"
#include "Obstacle.h"
#include "Consts.h"

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
    
    farmProduceArray = CCArray::create();
    farmProduceArray->retain();
    
    obstacleArray = CCArray::create();
    obstacleArray->retain();
    
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
    ///////////////////////////////////
    
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
    
    // Add overlay color.
    overlayColor = LayerColor::create(Color4B(0, 0, 0, 80));
    overlayColor->setVisible(false);
    this->addChild(overlayColor, sixthGround);
    
    ///////////////////////////////////
    // Add level label.
    // Add score label.
    ///////////////////////////////////
    levelLabel = Label::createWithSystemFont("Level 1", "Marker Felt", 25);
    int currentLevel = UserDefault::getInstance()->getIntegerForKey(CURRENT_LEVEL, 1);
    char levelString[100]={0};
    sprintf(levelString,"Level %i", currentLevel);
    levelLabel->setString(levelString);
    levelLabel->setPosition(levelLabel->getContentSize().width / 2 + 10, visibleSize.height - 5 - levelLabel->getContentSize().height / 2);
    
    coinDisplay = Label::createWithSystemFont("Coin: 0", "Marker Felt", 25);
    coinDisplay->setPosition(Point(coinDisplay->getContentSize().width / 2 + 10, levelLabel->getPositionY() - 25));
    
    this->addChild(levelLabel, secondGround);
    this->addChild(coinDisplay, secondGround);
    
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
    float scale = (visibleSize.height / 5 - 10) / iconPig->getContentSize().height;
    iconPig->setScale(scale);
    iconPig->setPosition(Point(iconPig->getContentSize().width * scale / 2 + 5, visibleSize.height / 2));
    this->addChild(iconPig, fourthGround);
    
}

void GamePlayScreen::stopGame(bool isEnd) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (!isEnd) {
        // Add boom icon.
        auto *iconBoom = Sprite::create("icon_boom.png");
        iconBoom->setScale(visibleSize.height / 5 / iconBoom->getContentSize().height / 2);
        iconBoom->setPosition(iconPig->getPositionX() + iconPig->getContentSize().width / 2 * (visibleSize.height / 5 - 10) / iconPig->getContentSize().height,
                              iconPig->getPositionY());
        this->addChild(iconBoom, fifthGround);
        
        Action *actionScale = CCSequence::create(ScaleTo::create(0.125, visibleSize.height / 5 / iconBoom->getContentSize().height), NULL ,NULL);
        iconBoom->runAction(actionScale);
        
        // Stop all moving items.
        for (int i = 0; i < farmProduceArray->count(); i++) {
            FarmProduce *farmProduce = (FarmProduce*) farmProduceArray->getObjectAtIndex(i);
            farmProduce->stopAllActions();
        }
        for (int i = 0; i < obstacleArray->count(); i++) {
            ((Obstacle*) obstacleArray->getObjectAtIndex(i))->stopAllActions();
        }
        for (int i = 0; i < lineArray->count(); i++) {
            ((Line*) lineArray->getObjectAtIndex(i))->stopAllActions();
        }
    }
    this->unscheduleUpdate();
}

void GamePlayScreen::update(float dt) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    roadTimer += dt;
    if (roadTimer >= roadInterval)
    {
        roadTimer = 0;
        this->addLine();
    }
    
    farmProduceAndObstacleTimer += dt;
    if (farmProduceAndObstacleTimer >= farmProduceAndObstacleInterval) {
        farmProduceAndObstacleTimer = 0;
        if (rand() % 3 == 0) {
            this->addObstacle();
        } else {
            this->addFarmProduce();
        }
    }
    
    CCArray *farmProduceToDelete = CCArray::create();
    for (int j=0; j < farmProduceArray->count(); j++)
    {
        FarmProduce *farmProduce = (FarmProduce*) farmProduceArray->objectAtIndex(j);
        if (iconPig->boundingBox().intersectsRect(farmProduce->boundingBox())) { //khi Pig chạm với FarmProduce
            farmProduceToDelete->addObject(farmProduce);
            score += farmProduce->coin;
            char coinString[100]={0};
            sprintf(coinString,"Coin: %i", score);
            coinDisplay->setString(coinString);
            coinDisplay->setPosition(coinDisplay->getContentSize().width / 2 + 10, coinDisplay->getPositionY());
            break;
        }
    }
    for (int j=0; j < farmProduceToDelete->count(); j++)
    {
        FarmProduce *farmProduce=(FarmProduce*) farmProduceToDelete->objectAtIndex(j);
        farmProduce->setVisible(false);
        farmProduceArray->fastRemoveObject(farmProduce);
        farmProduce->removeFromParentAndCleanup(true);
    }
    farmProduceToDelete->retain();
    
    for (int i = 0; i < obstacleArray->count(); i++) {
        Obstacle *obstacle = (Obstacle*) obstacleArray->objectAtIndex(i);
        if (iconPig->boundingBox().intersectsRect(obstacle->boundingBox())) {
            // Stop game.
            stopGame(false);
        }
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
    lineArray->addObject(line2);
    // Su chuyen dong cua giai phan cach
    CCAction *_actionMoveLine1=CCSequence::create(CCMoveTo::create(actualDuration, ccp(-visibleSize.width / 2 + line1->getContentSize().width / 2, visibleSize.height / 5 * 3)),
                                                  CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeLine)) ,NULL);
    CCAction *_actionMoveLine2=CCSequence::create(CCMoveTo::create(actualDuration, ccp(-visibleSize.width / 2 + line2->getContentSize().width / 2, visibleSize.height / 5 * 2)),
                                                  CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeLine)) ,NULL);
    line1->runAction((CCAction*)_actionMoveLine1);
    line2->runAction((CCAction*)_actionMoveLine2);
}

void GamePlayScreen::removeLine(CCNode *pSender) {
    lineArray->removeObject(pSender);
    pSender->removeFromParentAndCleanup(true);
}

void GamePlayScreen::addFarmProduce() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    FarmProduce *farmProduce = NULL;
    // Thêm 2 đối tượng: carrot or strawberry
    if (rand() % 2 == 0)
    {
        farmProduce = Carrot::create();
    } else {
        farmProduce = Strawberry::create();
    }
    
    // Xac dinh su xuat hien cua nong san tren 3 duong mot cach ngau nhien
    int onRoad = rand() % 3;
    switch (onRoad) {
        case SECOND_ROAD:
            farmProduce->setPosition(Point(visibleSize.width + farmProduce->getContentSize().width/2, visibleSize.height / 2));
            break;
        case THIRD_ROAD:
            farmProduce->setPosition(Point(visibleSize.width + farmProduce->getContentSize().width/2, visibleSize.height * 7 / 10));
            break;
        default:
            farmProduce->setPosition(Point(visibleSize.width + farmProduce->getContentSize().width/2, visibleSize.height * 3 / 10));
            break;
    }
    
    this->addChild(farmProduce, thirdGround);
    
    //Xac dinh toc do
    int minDuration = farmProduce->minMoveDuration;
    int maxDuration = farmProduce->maxMoveDuration;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = rangeDuration + minDuration;
    farmProduceArray->addObject(farmProduce);
    //Su chuyen dong
    CCAction *_actionMove = CCSequence::create(CCMoveTo::create(actualDuration, ccp(-visibleSize.width / 2 + farmProduce->getContentSize().width / 2, farmProduce->getPosition().y)),
                                               CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeFarmProduce)) ,NULL);
    farmProduce->runAction((CCAction*)_actionMove);
}

void GamePlayScreen::removeFarmProduce(CCNode *pSender) {
    farmProduceArray->removeObject(pSender);
    pSender->removeFromParentAndCleanup(true);
}

void GamePlayScreen::addObstacle() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Obstacle *obstacle = NULL;
    // Add obstacle on road.
    obstacle = Stone::create();
    obstacle->setScale((visibleSize.height / 5 - 10) / obstacle->getContentSize().height);
    
    // Set position of obstacle.
    int onRoad = rand() % 3;
    switch (onRoad) {
        case SECOND_ROAD:
            obstacle->setPosition(Point(visibleSize.width + obstacle->getContentSize().width / 2,
                                        visibleSize.height / 2));
            break;
        case THIRD_ROAD:
            obstacle->setPosition(Point(visibleSize.width + obstacle->getContentSize().width / 2,
                                        visibleSize.height * 7 / 10));
            break;
        default:
            obstacle->setPosition(Point(visibleSize.width + obstacle->getContentSize().width / 2,
                                        visibleSize.height * 3 / 10));
            break;
    }
    this->addChild(obstacle, thirdGround);
    
    //Xac dinh toc do
    int minDuration = obstacle->minMoveDuration;
    int maxDuration = obstacle->maxMoveDuration;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = rangeDuration + minDuration;
    obstacleArray->addObject(obstacle);
    //Su chuyen dong
    CCAction *_actionMove = CCSequence::create(CCMoveTo::create(actualDuration,ccp(-visibleSize.width / 2 + obstacle->getContentSize().width / 2, obstacle->getPosition().y)), CCCallFuncN::create(this, callfuncN_selector(GamePlayScreen::removeObstacle)) ,NULL);
    obstacle->runAction((CCAction*)_actionMove);
}

void GamePlayScreen::removeObstacle(CCNode *pSender) {
    obstacleArray->removeObject(pSender);
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