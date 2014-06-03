//
//  HighScore.cpp
//  PigRace
//
//  Created by admin on 5/14/14.
//
//

#include "HighScoreScreen.h"
#include "Consts.h"

USING_NS_CC;

Scene* HighScoreScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HighScoreScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HighScoreScreen::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create high score screen.
    createHighScoreScreen();
    
    return true;
}

/*
 * Create high score screen.
 * Add features: label, menu background, buttons.
 */
void HighScoreScreen::createHighScoreScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add background.
    auto bgSetting = Sprite::create("bg.png");
    bgSetting->setScale(visibleSize.width / bgSetting->getContentSize().width);
    
    // position the sprite on the center of the screen
    bgSetting->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgSetting, 0);
    
    // add a label shows "High score"
    // create and initialize a label
    settingLabel = Label::createWithSystemFont("High score", "Marker Felt", 30);
    
    settingLabel->setScale(2.0);
    settingLabel->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    settingLabel->setPosition(Point(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height - settingLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(settingLabel, 1);
    
    // Menu background.
    bgSettingMenu = Sprite::create("bg_menu_setting.png");
    
    // position the sprite on the center of the screen
    bgSettingMenu->setPosition(Point(visibleSize.width/2 + origin.x, origin.y
                                     + visibleSize.height / 2));
    
    // add the sprite as a child to this layer
    this->addChild(bgSettingMenu, 1);
    
    // Add coin icon.
    auto *iconCoin = Sprite::create("icon_coin.png");
    iconCoin->setPosition(Point(origin.x + bgSettingMenu->getPosition().x - bgSettingMenu->getContentSize().width / 4,
                                origin.y + bgSettingMenu->getPosition().y + iconCoin->getContentSize().height / 2 + 5));
    this->addChild(iconCoin, 2);
    
    // Add fruit icon.
    auto *iconFruit = Sprite::create("icon_fruit.png");
    iconFruit->setPosition(Point(origin.x + bgSettingMenu->getPosition().x - bgSettingMenu->getContentSize().width / 4,
                                      origin.y + bgSettingMenu->getPosition().y - iconFruit->getContentSize().height / 2 - 5));
    this->addChild(iconFruit, 2);
    
    // Add coin number.
    Label *coinNumberLabel = Label::createWithSystemFont("0", "Arial", 25);
    coinNumberLabel->setPosition(Point(origin.x + bgSettingMenu->getPosition().x + bgSettingMenu->getContentSize().width / 4,
                                  origin.y + iconCoin->getPositionY()));
    coinNumberLabel->setColor(Color3B(0, 0, 0));
    int coinNumber = UserDefault::getInstance()->getIntegerForKey(COIN_HIGH_SCORE_KEY, 0);
    setHighScore(coinNumberLabel, coinNumber);
    this->addChild(coinNumberLabel, 2);
    
    // Add fruit number.
    Label *fruitNumberLabel = Label::createWithSystemFont("0", "Arial", 25);
    fruitNumberLabel->setPosition(Point(origin.x + bgSettingMenu->getPosition().x + bgSettingMenu->getContentSize().width / 4,
                                         origin.y + iconFruit->getPositionY()));
    fruitNumberLabel->setColor(Color3B(0, 0, 0));
    int strawberryNumber = UserDefault::getInstance()->getIntegerForKey(FRUIT_HIGH_SCORE_KEY, 0);
    setHighScore(fruitNumberLabel, strawberryNumber);
    this->addChild(fruitNumberLabel, 2);
    
    // Add Ok button.
    btnOk = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(HighScoreScreen::menuOkCallback, this));
    btnOk->setPosition(Point(origin.x + bgSettingMenu->getPosition().x,
                             origin.y + bgSettingMenu->getPosition().y - bgSettingMenu->getContentSize().height / 2
                             - btnOk->getContentSize().height));
    
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnOk, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
}

/*
 * Set high score string.
 */
void HighScoreScreen::setHighScore(cocos2d::Label *label, int score) {
    // Display score.
    char charScore[100]={0};
    sprintf(charScore,"%i", score);
    label->setString(charScore);
}

/*
 * Close this screen when click Ok button.
 */
void HighScoreScreen::menuOkCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}