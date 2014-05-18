#include "BeginScene.h"
#include "MenuScene.h"


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
	

	m_frog = CCSprite::createWithSpriteFrameName("frog.png");
	m_leaf1 = CCSprite::createWithSpriteFrameName("leaf_01.png");
	m_leaf2 = CCSprite::createWithSpriteFrameName("leaf_00.png");

	CCArray * arrFrameJump = new CCArray();
	for(int i=0;i<3;i++)
	{
		arrFrameJump->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("frog_0%d.png",i)->getCString()));
	}	
	float duration = 0.2f;
	CCAnimation *animJump = CCAnimation::createWithSpriteFrames(arrFrameJump,duration);
	CCAnimate *actJump = CCAnimate::create(animJump);				
	m_frog->setRotation(90);
	m_frog->runAction(CCSequence::create(CCSpawn::createWithTwoActions(actJump,CCMoveBy::create(duration,ccp(winSize.width * 0.5,0))),							
		CCCallFunc::create(this, callfunc_selector(BeginScene::onComplete)),
	NULL));		

	m_frog->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.1));
	m_leaf1->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.1));
	m_leaf2->setPosition(ccp(winSize.width * 0.75, winSize.height * 0.1));
	
	this->addChild(m_leaf1);
	this->addChild(m_leaf2);
	this->addChild(m_frog);
    return true;
}

void BeginScene::onComplete(){
	m_leaf2->setVisible(false);
	CCArray *arrFrameWaterSplash = new CCArray();
	for(int i=1;i<7;i++)
	{
		arrFrameWaterSplash->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("water_0%d.png",i)->getCString()));
	}
	CCAnimation *animDead = CCAnimation::createWithSpriteFrames(arrFrameWaterSplash,0.1f);
	CCAnimate *actDead = CCAnimate::create(animDead);		
	m_frog->runAction(CCSequence::create(actDead,	CCCallFunc::create(this, callfunc_selector(BeginScene::changeScene)),NULL));	

}

void BeginScene::changeScene(){
	m_frog->setVisible(false);
	CCScene *pScene = MenuScene::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void BeginScene::replay(CCObject *sender)
{
	CCScene *pScene = MenuScene::scene();		
		
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void BeginScene::ranking(CCObject *sender)
{

}
void BeginScene::close(CCObject *sender)
{

}
