#include "BeginScene.h"
#include "GameLayer.h";

USING_NS_CC;

CCScene* BeginScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BeginScene *layer = BeginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BeginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist");

	CCSprite * main_bg = CCSprite::create("flash_screen.jpg");
	main_bg->setPosition(ccp(origin.x + winSize.width/2,origin.y  +  winSize.height/2));
	this->addChild(main_bg);
	
	CCMenu *menu = CCMenu::create();

	CCMenuItemSpriteCustom * playItem = CCMenuItemSpriteCustom::create(
		CCSprite::createWithSpriteFrameName("touch_normal.png"),
		CCSprite::createWithSpriteFrameName("touch.png"),
		CCSprite::createWithSpriteFrameName("touch.png"),
		this,
		menu_selector(BeginScene::replay));
	playItem->setPositionY(winSize.height * 0.1);
	menu->addChild(playItem);
	menu->setPositionY(0);
	this->addChild(menu);
    return true;
}

void BeginScene::replay(CCObject *sender)
{
	CCScene *pScene = GameLayer::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void BeginScene::ranking(CCObject *sender)
{

}
void BeginScene::close(CCObject *sender)
{

}
