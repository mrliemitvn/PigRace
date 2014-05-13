//
//  SettingScreen.cpp
//  PigRace
//
//  Created by admin on 5/13/14.
//
//

#include "SettingScreen.h"

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
    
    // position the sprite on the center of the screen
    bgSetting->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgSetting, 0);
    
    // add a label shows "Pig Race"
    // create and initialize a label
    settingLabel = Label::createWithSystemFont("Setting", "Arial", 30);
    
    settingLabel->setScale(2.0);
    // position the label on the center of the screen
    settingLabel->setPosition(Point(origin.x + visibleSize.width/2,
                                                   origin.y + visibleSize.height - settingLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(settingLabel, 1);
    
    bgSettingMenu = Sprite::create("bg_menu_setting.png");
    
    // position the sprite on the center of the screen
    bgSettingMenu->setPosition(Point(visibleSize.width/2 + origin.x,
                                     visibleSize.height - settingLabel->getContentSize().height*3 - bgSettingMenu->getContentSize().height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(bgSettingMenu, 1);
    
    // Add Ok button.
    btnOk = MenuItemImage::create("btn_ok_off.png", "btn_ok_on.png", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    btnOk->setPosition(Point(origin.x + bgSettingMenu->getPosition().x, origin.y + bgSettingMenu->getPosition().y - bgSettingMenu->getContentSize().height / 4));
    
    // Add sound effect checkbox.
    auto *btnSoundEffect = MenuItemImage::create("btn_sound_effect_off.png", "btn_sound_effect_on.png", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    btnSoundEffect->setPosition(Point(origin.x + bgSettingMenu->getPosition().x, origin.y + bgSettingMenu->getPosition().y + bgSettingMenu->getContentSize().height / 4));
    
    // Add game music checkbox.
    auto *btnGameMusic = MenuItemImage::create("btn_game_music_off.png", "btn_game_music_on.png", CC_CALLBACK_1(SettingScreen::menuOkCallback, this));
    btnGameMusic->setPosition(Point(origin.x + bgSettingMenu->getPosition().x, origin.y + btnSoundEffect->getPosition().y - btnSoundEffect->getContentSize().height));
    
    // create menu, it's an autorelease object
    Menu *menu = Menu::create(btnOk, btnSoundEffect, btnGameMusic, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
}

/*
 * Close this screen when click Ok button.
 */
void SettingScreen::menuOkCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}