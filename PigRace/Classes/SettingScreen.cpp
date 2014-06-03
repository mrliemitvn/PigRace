//
//  SettingScreen.cpp
//  PigRace
//
//  Created by admin on 5/13/14.
//
//

#include "SettingScreen.h"
#include "Consts.h"

USING_NS_CC;

Scene* SettingScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingScreen::init()
{
    //////////////////////////////
    // Super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Create setting screen.
    createSettingScreen();
    
    return true;
}

/*
 * Create setting screen.
 * Add features: label, menu background, buttons.
 */
void SettingScreen::createSettingScreen() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add background.
    auto bgSetting = Sprite::create("bg.png");
    bgSetting->setScale(visibleSize.width / bgSetting->getContentSize().width);
    
    // position the sprite on the center of the screen
    bgSetting->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgSetting, 0);
    
    // add a label shows "Setting"
    // create and initialize a label
    settingLabel = Label::createWithSystemFont("Setting", "Marker Felt", 30);
    
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
                                     + visibleSize.height - settingLabel->getContentSize().height*3
                                     - bgSettingMenu->getContentSize().height/2));
    
    // add the sprite as a child to this layer
    this->addChild(bgSettingMenu, 1);
    
    // Add Ok button.
    btnOk = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    btnOk->setPosition(Point(origin.x + bgSettingMenu->getPosition().x,
                             origin.y + bgSettingMenu->getPosition().y - bgSettingMenu->getContentSize().height / 4));
    
    // Add sound effect toggle.
    btnSoundEffectOff = MenuItemImage::create("btn_sound_effect_off.png", "");
    btnSoundEffectOn = MenuItemImage::create("btn_sound_effect_on.png", "");
    
    soundEffectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScreen::soundEffectToggleCallback, this),
                                                           btnSoundEffectOff, btnSoundEffectOn, NULL);
    soundEffectToggle->setPosition(Point(origin.x + bgSettingMenu->getPosition().x,
                                         origin.y + bgSettingMenu->getPosition().y
                                         + bgSettingMenu->getContentSize().height / 4));
    // Set state for this toggle.
    int soundEffectState = UserDefault::getInstance()->getIntegerForKey(SOUND_EFFECT_KEY, STATE_ON);
    setSoundEffectState(soundEffectState);
    
    // Add game music toggle.
    auto *btnGameMusicOff = MenuItemImage::create("btn_game_music_off.png", "", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    auto *btnGameMusicOn = MenuItemImage::create("btn_game_music_on.png", "", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    
    gameMusicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScreen::gameMusicToggleCallback, this),
                                                         btnGameMusicOff, btnGameMusicOn, NULL);
    gameMusicToggle->setPosition(Point(origin.x + bgSettingMenu->getPosition().x,
                                       origin.y + soundEffectToggle->getPosition().y
                                       - soundEffectToggle->getContentSize().height));
    // Set state for this toggle.
    int gameMusicState = UserDefault::getInstance()->getIntegerForKey(GAME_MUSIC_KEY, STATE_ON);
    setGameMusicState(gameMusicState);
    
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnOk, soundEffectToggle, gameMusicToggle, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
}

/*
 * Close this screen when click Ok button.
 */
void SettingScreen::menuOkCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}

/*
 * Hanlde event when toggle sound effect.
 * Save sound effect setting state.
 */
void SettingScreen::soundEffectToggleCallback(cocos2d::Ref *pSender) {
    int selectedIndex = soundEffectToggle->getSelectedIndex();
    switch (selectedIndex) {
        case STATE_ON:
            UserDefault::getInstance()->setIntegerForKey(SOUND_EFFECT_KEY, STATE_ON);
            break;
        default:
            UserDefault::getInstance()->setIntegerForKey(SOUND_EFFECT_KEY, STATE_OFF);
            break;
    }
}

/*
 * Hanlde event when toggle game music.
 * Save game music setting state.
 */
void SettingScreen::gameMusicToggleCallback(cocos2d::Ref *pSender) {
    int selectedIndex = gameMusicToggle->getSelectedIndex();
    switch (selectedIndex) {
        case STATE_ON:
            UserDefault::getInstance()->setIntegerForKey(GAME_MUSIC_KEY, STATE_ON);
            break;
        default:
            UserDefault::getInstance()->setIntegerForKey(GAME_MUSIC_KEY, STATE_OFF);
            break;
    }
}

/* 
 * Set sound effect state.
 */
void SettingScreen::setSoundEffectState(int state) {
    soundEffectToggle->setSelectedIndex(state);
}

/*
 * Set game music state.
 */
void SettingScreen::setGameMusicState(int state) {
    gameMusicToggle->setSelectedIndex(state);
}