//
//  GamePlayScreen.h
//  PigRace
//
//  Created by admin on 5/16/14.
//
//

#ifndef PigRace_GamePlayScreen_h
#define PigRace_GamePlayScreen_h

#include "cocos2d.h"

USING_NS_CC;

enum {
    firstGround = 1,
    secondGround = 2,
    thirdGround = 3,
    fourthGround = 4,
    fifthGround = 5,
    sixthGround = 6,
    seventhGround = 7
};

class GamePlayScreen : public Layer {
public:
    /* Variables will be used. */
    Label *levelLabel;
    Label *fruitDisplay;
    Label *gameOverLabel;
    Label *progressLabel;
    Label *totalFruitLabel;
    Label *totalCoinLabel;
    Label *timeDisplayLabel;
    LayerColor *overlayColor;
    Sprite *bgGame;
    Sprite *bgRoad;
    Sprite *iconPig;
    Sprite *iconBoom;
    MenuItemImage *btnJump;
    MenuItemImage *btnUpArrow;
    MenuItemImage *btnDownArrow;
    MenuItemFont *okMenuLabel;
    MenuItemFont *retryMenuLabel;
    CCArray *lineArray;
    CCArray *farmProduceArray;
    CCArray *obstacleArray;
    bool isPlaying;
    int score;
    int roundTime;
    float roadTimer;
    float roadInterval = 1;
    float farmProduceAndObstacleTimer;
    float farmProduceAndObstacleInterval = 1;
    
    /* Methods will be used. */
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float dt);
    
    // Create game play screen.
    void createGamePlayScreen();
    
    // Stop game.
    void stopGame(bool isEnd);
    
    // Restart game.
    void restartGame();
    
    // Show or hide game over items.
    void showGameOverItems(bool show, bool isEndGame);
    
    // Add line on road.
    void addLine();
    
    // Remove line on road.
    void removeLine(CCNode *pSender);
    
    // Add farm produce on road.
    void addFarmProduce();
    
    // Remove farm produce on road.
    void removeFarmProduce(CCNode *pSender);
    
    // Add obstacle on road.
    void addObstacle();
    
    // Remove obstacle on road.
    void removeObstacle(CCNode *pSender);
    
    // Handle event when click on control buttons.
    void controlButtonCallback(Ref *pSender);
    
    // Handle event when click on menus.
    void menuCallback(Ref *pSender);
    
    // Countdown time playing.
    void countDownTimePlaying(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScreen);
};

#endif
