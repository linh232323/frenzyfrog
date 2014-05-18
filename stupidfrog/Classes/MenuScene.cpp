#include "MenuScene.h"
#include "GameLayer.h"
#include "NormalGameLayer.h"

USING_NS_CC;

CCScene* MenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite * main_bg = CCSprite::create("main_bg.png");
	main_bg->setPosition(ccp(origin.x + winSize.width/2,origin.y  +  winSize.height/2));
	this->addChild(main_bg);
	
	CCMenu *menu = CCMenu::create();
	
	CCLabelBMFont  *lbNormal = CCLabelBMFont::create("Normal Mode","UVNBanhMiRed.fnt");
	lbNormal->setScale(1.5f);
	lbNormal->setColor(ccc3(0,255,255));	

	CCLabelBMFont  *lbFast = CCLabelBMFont::create("Fast Mode","UVNBanhMiRed.fnt");
	lbFast->setScale(1.5f);
	lbFast->setColor(ccc3(0,255,255));
	

	CCMenuItemLabel *pNormalMode = CCMenuItemLabel::create(lbNormal,this,menu_selector(MenuScene::normalMode));
	pNormalMode->setPosition(ccp(0,winSize.height * 0.60));
	menu->addChild(pNormalMode);

	CCMenuItemLabel *pFastMode = CCMenuItemLabel::create(lbFast,this,menu_selector(MenuScene::fastMode));
	pFastMode->setPosition(ccp(0,winSize.height * 0.40));	
	menu->addChild(pFastMode);

	menu->setPosition(ccp(winSize.width * 0.4,0));
	this->addChild(menu);
	
    return true;
}



void MenuScene::normalMode(CCObject *sender)
{
	CCScene *pScene = NormalGameLayer::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void MenuScene::fastMode(CCObject *sender)
{
	CCScene *pScene = GameLayer::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}