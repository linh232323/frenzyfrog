#include "EndScene.h"
#include "GameLayer.h";
USING_NS_CC;

CCScene* EndScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    EndScene *layer = EndScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist");

	CCSprite *bgSprite = CCSprite::create("main_bg.png");
	bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(bgSprite);

	CCSprite *panel = CCSprite::createWithSpriteFrameName("bg_ui.png");
	panel->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(panel);

	CCSprite *game_over = CCSprite::createWithSpriteFrameName("game_over.png");
	game_over->setPosition(ccp(winSize.width/2,winSize.height/2 + panel->getContentSize().height/2));
	this->addChild(game_over);

	//CCSprite *crocodile_avatar = CCSprite::createWithSpriteFrameName("crocodile_avatar.png");
	//crocodile_avatar->setPosition(ccp(winSize.width/2,winSize.height/2));
	//this->addChild(crocodile_avatar);

	CCMenu *menu = CCMenu::create();
	CCMenuItemSpriteCustom *itemReplay = CCMenuItemSpriteCustom::create(
		CCSprite::createWithSpriteFrameName("btn_replay.png"),
		CCSprite::createWithSpriteFrameName("btn_replay.png"),
		CCSprite::createWithSpriteFrameName("btn_replay.png"),
		this,
		menu_selector(EndScene::replay));
	itemReplay->setPosition(ccp(winSize.width/3,winSize.height/2 - panel->getContentSize().height/2 + 100));
	menu->addChild(itemReplay);

	CCMenuItemSpriteCustom *itemRanking = CCMenuItemSpriteCustom::create(
		CCSprite::createWithSpriteFrameName("btn_rank.png"),
		CCSprite::createWithSpriteFrameName("btn_rank.png"),
		CCSprite::createWithSpriteFrameName("btn_rank.png"),
		this,
		menu_selector(EndScene::replay));
	menu->addChild(itemRanking);
	itemRanking->setPosition(ccp(winSize.width*2/3,winSize.height/2 - panel->getContentSize().height/2 + 100));

	CCMenuItemSpriteCustom *itemClose = CCMenuItemSpriteCustom::create(
		CCSprite::createWithSpriteFrameName("btn_close.png"),
		CCSprite::createWithSpriteFrameName("btn_close.png"),
		CCSprite::createWithSpriteFrameName("btn_close.png"),
		this,
		menu_selector(EndScene::close));
//	menu->addChild(itemClose);
	itemClose->setPosition(ccp(winSize.width/2 + panel->getContentSize().width/2 - 20,winSize.height/2 + panel->getContentSize().height/2 - 20));

	this->addChild(menu);
	menu->setPosition(0,0);
    return true;
}

void EndScene::replay(CCObject *sender)
{
	CCScene *pScene = GameLayer::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void EndScene::ranking(CCObject *sender)
{

}
void EndScene::close(CCObject *sender)
{

}
