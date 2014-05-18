#include "EndScene.h"
#include "GameLayer.h"
#include "NormalGameLayer.h"
#include "UserModel.h"
USING_NS_CC;

EndScene* EndScene::createWithResult(int mode,int result){
	 EndScene *endscene = new EndScene();
    if(endscene && endscene->initWithResult(mode,result))
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

CCScene* EndScene::scene(int mode,int result)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    EndScene *layer = EndScene::createWithResult(mode,result);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::initWithResult(int mode,int result)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->setMode(mode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist");

	CCSprite *bgSprite;
	
	if(result == RESULT_C)
		bgSprite = CCSprite::create("bg_result_w.png");
	else if(result == RESULT_W)
		bgSprite = CCSprite::create("bg_result_cor.png");
	else
		bgSprite = CCSprite::create("main_bg.png");
	bgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(bgSprite);

	CCLayer *layer = CCLayer::create();

	CCSprite *panel = CCSprite::createWithSpriteFrameName("bg_ui.png");
	panel->setPosition(ccp(winSize.width/2,winSize.height/2));
	layer->addChild(panel);

	CCSprite *game_over = CCSprite::createWithSpriteFrameName("game_over.png");
	game_over->setPosition(ccp(winSize.width/2,winSize.height/2 + panel->getContentSize().height/2));
	layer->addChild(game_over);

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

	

	layer->addChild(menu);
	menu->setPosition(0,0);

	CCSprite *lbScore = CCSprite::createWithSpriteFrameName("score_lb.png");
	lbScore->setPosition(ccp(winSize.width *0.3,winSize.height/2));
	layer->addChild(lbScore);

	CCSprite *lbBest = CCSprite::createWithSpriteFrameName("best_lb.png");
	lbBest->setPosition(ccp(winSize.width *0.3,winSize.height/2 + 150));	
	layer->addChild(lbBest);

	CCLabelBMFont *lbcScore;
	switch(this->getMode()){
		case MODE_NORMAL:
			lbcScore = CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getCrtScore2())->getCString(),"UVNBanhMiRed.fnt");
			break;
		case MODE_ENDLESS:
			lbcScore = CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getCrtScore())->getCString(),"UVNBanhMiRed.fnt");
			break;
		default:
			lbcScore = CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getCrtScore())->getCString(),"UVNBanhMiRed.fnt");
			break;
	}
	
	lbcScore->setPosition(ccp(winSize.width *0.6,winSize.height/2 + 17));
	lbcScore->setScale(1.4f);
	layer->addChild(lbcScore);

	CCLabelBMFont *lbcBest;
	switch(this->getMode()){
	case MODE_NORMAL:
		lbcBest	= CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getBestScore2())->getCString(),"UVNBanhMiRed.fnt");
		break;
	case MODE_ENDLESS:
		lbcBest	= CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getBestScore())->getCString(),"UVNBanhMiRed.fnt");
		break;
	default:
		lbcBest	= CCLabelBMFont::create(CCString::createWithFormat("%d",User::Instance().getBestScore())->getCString(),"UVNBanhMiRed.fnt");
		break;
	}
	lbcBest->setScale(1.4f);
	lbcBest->setPosition(ccp(winSize.width *0.6,winSize.height/2 + 167));
	
	layer->addChild(lbcBest);

	this->addChild(layer);
	layer->setPosition(0,-winSize.height);
	layer->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCMoveTo::create(0.2f,ccp(0,0)),NULL));
    return true;
}

void EndScene::replay(CCObject *sender)
{
	CCScene *pScene;
	switch(this->getMode()){
	case MODE_NORMAL:
		pScene = NormalGameLayer::scene();		
		break;
		case MODE_ENDLESS:
			pScene = GameLayer::scene();		
		break;
		default:
			pScene = GameLayer::scene();		
			break;
	}
	 
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void EndScene::ranking(CCObject *sender)
{

}
void EndScene::close(CCObject *sender)
{

}
