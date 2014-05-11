#include "EndScene.h"
#include "GameLayer.h"
#include "UserModel.h"
USING_NS_CC;

EndScene* EndScene::createWithResult(int result){
	 EndScene *endscene = new EndScene();
    if(endscene && endscene->initWithResult(result))
    {
        endscene->autorelease();
        return endscene;
    }
    else
    {
        delete endscene;
        return NULL;
    }
}

CCScene* EndScene::scene(int result)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    EndScene *layer = EndScene::createWithResult(result);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::initWithResult(int result)
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

	CCSprite *lbScore = CCSprite::createWithSpriteFrameName("score_lb.png");
	lbScore->setPosition(ccp(winSize.width *0.3,winSize.height/2));
	this->addChild(lbScore);

	CCSprite *lbBest = CCSprite::createWithSpriteFrameName("best_lb.png");
	lbBest->setPosition(ccp(winSize.width *0.3,winSize.height/2 + 150));	
	this->addChild(lbBest);

	CCLabelBMFont *lbcScore = CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getCrtScore())->getCString(),"UVNBanhMiRed.fnt");
	lbcScore->setPosition(ccp(winSize.width *0.6,winSize.height/2 + 17));
	lbcScore->setScale(1.4f);
	this->addChild(lbcScore);

	CCLabelBMFont *lbcBest = CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getBestScore())->getCString(),"UVNBanhMiRed.fnt");
	lbcBest->setScale(1.4f);
	lbcBest->setPosition(ccp(winSize.width *0.6,winSize.height/2 + 167));
	
	this->addChild(lbcBest);

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
