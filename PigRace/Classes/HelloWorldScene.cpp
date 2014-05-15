#include "HelloWorldScene.h"
#include "SettingScreen.h"
#include "HighScoreScreen.h"
#include "TutorialScreen.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create Home screen.
    createGameScreen();
    
    return true;
}

/*
 Create home screen.
 */
void HelloWorld::createGameScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add background.
    auto sprite = Sprite::create("bg.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // add a label shows "Pig Race"
    // create and initialize a label
    gameLabel = Label::createWithSystemFont("Pig Race", "Marker Felt", 30);
    
    gameLabel->setScale(2.0);
    gameLabel->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    gameLabel->setPosition(Point(origin.x + visibleSize.width/2,
                                         origin.y + visibleSize.height - gameLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(gameLabel, 1);
    
    /////////////////////////////
    // Add quit button.
    auto btnQuit = MenuItemImage::create("btn_quit_off.png", "btn_quit_on.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    btnQuit->setPosition(Point(origin.x + visibleSize.width/2, origin.y + btnQuit->getContentSize().height));
    // Add setting button.
    auto btnSetting = MenuItemImage::create("btn_setting_off.png", "btn_setting_on.png", CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
    btnSetting->setPosition(Point(origin.x + visibleSize.width/2, origin.y + btnSetting->getContentSize().height*2));
    // Add tutorial button.
    auto btnTutorial = MenuItemImage::create("btn_tutorial_off.png", "btn_tutorial_on.png", CC_CALLBACK_1(HelloWorld::menuTutorialCallback, this));
    btnTutorial->setPosition(Point(origin.x + visibleSize.width/2, origin.y + btnTutorial->getContentSize().height*3));
    // Add high score button.
    auto btnHighScore = MenuItemImage::create("btn_highscore_off.png", "btn_highscore_on.png", CC_CALLBACK_1(HelloWorld::menuHighScoreCallback, this));
    btnHighScore->setPosition(Point(origin.x + visibleSize.width/2, origin.y + btnHighScore->getContentSize().height*4));
    // Add start button.
    auto btnStart = MenuItemImage::create("btn_start_off.png", "btn_start_on.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    btnStart->setPosition(Point(origin.x + visibleSize.width/2, origin.y + btnStart->getContentSize().height*5));
    
    // create menu, it's an autorelease object
    menu = Menu::create(btnQuit, btnSetting, btnTutorial, btnHighScore, btnStart, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

/*
 * Handle event when click on quit button.
 */
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/*
 * Handle event when click on setting button.
 */
void HelloWorld::menuSettingCallback(Ref *pSender) {
    Scene *settingScene = SettingScreen::createScene();
    Director::getInstance()->pushScene(settingScene);
}

/*
 * Handle event when click on high score button.
 */
void HelloWorld::menuHighScoreCallback(Ref *pSender) {
    Scene *highScoreScene = HighScoreScreen::createScene();
    Director::getInstance()->pushScene(highScoreScene);
}

/*
 * Handle event when click on tutorial button.
 */
void HelloWorld::menuTutorialCallback(Ref *pSender) {
    Scene *highScoreScene = TutorialScreen::createScene();
    Director::getInstance()->pushScene(highScoreScene);
}