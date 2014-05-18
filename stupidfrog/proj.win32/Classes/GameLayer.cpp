#include "CCLeaf.h"
#include "EndScene.h"
#include "CCFrog.h"
#include "GameLayer.h"
#include "UserModel.h"
#include "math.h"


#define MAX_LEAF_COUNT 30
#define HEIGHT_TO_PAUSE 200

#define MAX_FRESH_LEAF 10
#define MAX_DEAD_LEAF 40
#define MAX_VELOCITY 400

#define FRESH_LEAF 1
#define DEAD_LEAF 0
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

GameLayer::GameLayer():
	m_pLeafs(NULL), m_nScore(0),m_vec(2000)
{
    
}

GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(m_pLeafs);    
	
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	winSize = CCDirector::sharedDirector()->getWinSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();
	User::Instance().LoadData();

    srand(time(NULL));
    this->setTouchEnabled(true);
    this->initFrames();
    this->initBackground();    
	this->initCrocodile();
    this->initLeafs();
	this->initFrog();
    this->schedule(schedule_selector(GameLayer::updateGame), 0.01f);    
	
	this->initFinalLayer();

	isFollow = false;

	isReady = false;
	isPrepare = true;
	isPause = false;
	isReadyForNext = true;
	return true;
}

void GameLayer::initFrames()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist");
	

}
void GameLayer::initCrocodile(){
	m_crocodile = CCSprite::createWithSpriteFrameName("crocodile.png");
	m_pBatchNode->addChild(m_crocodile);
}
void GameLayer::initBackground()
{
	m_backgroundNode = CCParallaxNodeExtras::node();

	winSize = CCDirector::sharedDirector()->getWinSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite * main_bg = CCSprite::create("main_bg.png");
	main_bg->setPosition(ccp(origin.x + winSize.width/2,origin.y  +  winSize.height/2));
	this->addChild(main_bg,-2);
	

    this->addChild(m_backgroundNode,-1);
	
	CCPoint dustSpeed = ccp(0.1, 0.1);

	//water1 = CCSprite::create("water1.jpg");
    //water2 = CCSprite::create("water2.jpg");
	
	//m_backgroundNode->addChild(water1, 0, dustSpeed,	ccp(winSize.width/2,0) ); // 2
	//m_backgroundNode->addChild(water2, 0, dustSpeed,	ccp(winSize.width/2,water1->getContentSize().height));
	winSize = CCDirector::sharedDirector()->getWinSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("game.png");	
    this->setBatchNode(CCSpriteBatchNode::createWithTexture(texture));	
    this->addChild(m_pBatchNode);
	
}

void GameLayer::initFinalLayer()
{


	CCSprite * green_bg = CCSprite::create("green_bg.png");
	green_bg->setPosition(ccp(origin.x + winSize.width/2,origin.y  +  winSize.height/2));
	CCScaleTo *scaleOut = CCScaleTo::create(3.0f,1.02f,1.035f);
	CCScaleTo *scaleIn = CCScaleTo::create(3.0f,1.0f,1.0f);

	CCSequence *sqBG = CCSequence::create(scaleOut,scaleIn,NULL);
	CCRepeatForever *repeateBG = CCRepeatForever::create(sqBG);
	green_bg->runAction(repeateBG);
	this->addChild(green_bg);
	CCSprite *bubble_02 = CCSprite::createWithSpriteFrameName("bubble_02.png");
	bubble_02->setPosition(ccp(winSize.width/2,winSize.height/2 - green_bg->getContentSize().height/2 + bubble_02->getContentSize().height/2 ));
	this->addChild(bubble_02,-1);

	
	CCFadeTo *fadeIn = CCFadeTo::create(1.0f,127);
	CCFadeTo *fadeOut = CCFadeTo::create(1.0f,255);
    

	CCSequence *pulseSequence = CCSequence::create(fadeIn,fadeOut,NULL);
	CCRepeatForever *repeat = CCRepeatForever::create(pulseSequence);

	CCSprite *bubble_01 = CCSprite::createWithSpriteFrameName("bubble_01.png");
	bubble_01->setPosition(ccp(winSize.width/2,winSize.height/2 - green_bg->getContentSize().height/2 + bubble_02->getContentSize().height ));
	bubble_01->runAction(repeat);
	this->addChild(bubble_01,-1);


	CCSprite *shiny = CCSprite::createWithSpriteFrameName("shiny.png");
	shiny->setPosition(ccp(winSize.width/2,winSize.height/2 - green_bg->getContentSize().height/2 + bubble_02->getContentSize().height + bubble_01->getContentSize().height ));
	this->addChild(shiny);

	CCSprite *topLayer = CCSprite::create("black_screen.jpg");	
	topLayer->setPosition(ccp(winSize.width/2,winSize.height/2 + green_bg->getContentSize().height/2 + topLayer->getContentSize().height/2));
	this->addChild(topLayer);

	CCSprite *botLayer = CCSprite::create("black_screen.jpg");	
	botLayer->setPosition(ccp(winSize.width/2,winSize.height/2 - green_bg->getContentSize().height/2  - topLayer->getContentSize().height/2));
	this->addChild(botLayer);

	lbScore = CCLabelBMFont::create("Score: 0","UVNBanhMiRed.fnt");
	lbScore->setPosition(ccp(winSize.width/2 , winSize.height/2 + green_bg->getContentSize().height/2 - 100)); 
	lbScore->setColor(ccc3(255,196,0));
	this->addChild(lbScore);
}

void GameLayer::initLeafs()
{
	
    this->setLeafs(CCArray::createWithCapacity(MAX_FRESH_LEAF + MAX_DEAD_LEAF));            
	
	//m_pBatchNode->setPosition(ccp(origin.x - winSize.width/2,origin.y  -  winSize.height/2));
    m_pLeafs->removeAllObjects();
	
	for(int i=0;i<MAX_FRESH_LEAF;i++)
	{
		this->getLeafs()->addObject(CCLeaf::createWithLeafType(FRESH_LEAF,m_pBatchNode,1,0));
		
	}
	for(int i=0;i<MAX_DEAD_LEAF;i++)
	{
		this->getLeafs()->addObject(CCLeaf::createWithLeafType(DEAD_LEAF,m_pBatchNode,1,0));
	}

	this->setNextLeaf(0);
	this->setCrtLeaf(-1);
	crtGenDepth = 0;
	crtDepth = 0;
}
void GameLayer::initFrog()
{
	m_frog= CCSprite::createWithSpriteFrameName("frog.png");
	arrFrameJump = new CCArray();
	for(int i=0;i<3;i++)
	{
		arrFrameJump->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("frog_0%d.png",i)->getCString()));
	}	
	m_frog->setPosition(ccp(m_frog->getContentSize().width/2, 9999));	

	arrFrameWaterSplash = new CCArray();
	for(int i=1;i<7;i++)
	{
		arrFrameWaterSplash->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("water_0%d.png",i)->getCString()));
	}
	m_pBatchNode->addChild(m_frog,9999);
}

void GameLayer::addLeaf()
{
        int freshLeaf = rand() % 4;		
		
		for(int i = 0;i < 4 ; i++)
		{
			CCObject *pLeafObj = NULL;		
			CCARRAY_FOREACH(m_pLeafs, pLeafObj){
				CCLeaf *pLeaf = (CCLeaf *)pLeafObj;
				
				if(!pLeaf->getEnable() ){
					if(freshLeaf == i)
					{
						if(pLeaf->getLeafType() == FRESH_LEAF){
							pLeaf->refresh(i,crtGenDepth);
							if(crtGenDepth == 0)
							{
								//CCLOG("Pos %d ",pLeaf->getSprite()->getPosition().y);
								m_frog->setPosition(ccp( (i + 1)* winSize.width / 5,winSize.height));
							}
							break;
						}
					}
					else
					{
						if(pLeaf->getLeafType() == DEAD_LEAF){
							pLeaf->refresh(i,crtGenDepth);
							break;
						}
					}
					
				}
			}		
		}		
		crtGenDepth ++ ;
		return;	
    
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 	CCSetIterator it = pTouches->begin();
	for(; it != pTouches->end(); it++)
    {
		CCTouch *pTouch = (CCTouch*)*it;
		CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
  
        break;
	}   
	
	
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    while(it != pTouches->end())
    {
        CCTouch *pTouch = (CCTouch *)*it;
        CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		
		CCObject *pLeafObj = NULL;
		if(isReadyForNext){
		CCARRAY_FOREACH(m_pLeafs, pLeafObj)
		{
			CCLeaf *pLeaf = (CCLeaf *)pLeafObj;

			if(pLeaf->getSprite()->boundingBox().containsPoint(pt)){					
			/*	CCScaleTo *scaleOutAction = CCScaleTo::create(0.0f,1.1f);
				CCScaleTo *scaleInAction = CCScaleTo::create(0.2f,1.00f);
				CCSequence *sq = CCSequence::create(scaleOutAction,scaleInAction,NULL);
				pLeaf->getSprite()->runAction(sq);*/

				m_frog->stopAllActions();
				crtLeaf = pLeaf->getSprite()->getPosition();
				int depth = pLeaf->getDepth(); 
				int typeLeaf = pLeaf->getLeafType();
				if(depth > crtDepth + 1 )
				{
					crtLeaf.y -= pLeaf->getSprite()->getContentSize().width/2;
					isReadyForNext = false;
				}
				if(depth != crtDepth + 1 || typeLeaf == 0)
				{
					isReadyForNext = false;
				}
				crtLeafObj = pLeafObj;
				int speed = 5000;
				float duration = crtLeaf.getDistance(m_frog->getPosition()) / speed;					
				
				float angle = atan2f(crtLeaf.y - m_frog->getPosition().y, crtLeaf.x - m_frog->getPosition().x) / M_PI * 180.0f;
				m_frog->setRotation(90.0f - angle);
				
				CCAnimation *animJump = CCAnimation::createWithSpriteFrames(arrFrameJump,duration);
				CCAnimate *actJump = CCAnimate::create(animJump);				

				m_frog->runAction(CCSequence::create(CCSpawn::createWithTwoActions(actJump,CCMoveTo::create(duration,crtLeaf)),					
					CCCallFunc::create(this, callfunc_selector(GameLayer::onTheLeaf)),
					CCRotateTo::create(0.01f,0),
					CCCallFunc::create(this, callfunc_selector(GameLayer::completeJump)),
					NULL));								

				if(isReadyForNext){
					crtDepth += 1;
					m_nScore += 10;
					lbScore->setString(CCString::createWithFormat("Score: %d",m_nScore)->getCString());
					
					int vec = 200;
								
					float a = 25;
					float b = 0.05;
					float c = 200;

					float fVec = a*exp(b*crtDepth) + c;
					vec = int(fVec);
					if(vec > MAX_VELOCITY)
						vec = MAX_VELOCITY;
					
					this->setVelocity(vec);
					
				}
				isReady = true;
				isPause = false;
				
				return;
			}}
		}    

        break;
    }
}


void GameLayer::updateGame(float dt)
{
	if(isPause)
		return;

    winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCPoint backgroundScrollVert = ccp(0,- this->getVelocity());
	
	m_backgroundNode->setPosition(ccpAdd(m_backgroundNode->getPosition()
		, ccpMult(backgroundScrollVert, dt)));
	
	this->setNextLeaf(- m_backgroundNode->getPosition().y / 100 + 1);
		
	if(this->getNextLeaf() % 2 == 0 && this->getNextLeaf() != this->getCrtLeaf() )
	{
		this->addLeaf();
		this->setCrtLeaf(this->getNextLeaf());		
	}
	
	//if(isReady) 
	updateFrog(dt);
	updateLeaf(dt);	
}
void GameLayer::updateLeaf(float dt)
{
	CCPoint backgroundScrollVert = ccp(0,- this->getVelocity());
	
	CCObject *pLeafObj = NULL;
	CCARRAY_FOREACH(m_pLeafs, pLeafObj)
	{
		CCLeaf *pLeaf = (CCLeaf *)pLeafObj;
		pLeaf->updateSelf(dt,backgroundScrollVert);		
		if(isPrepare && m_frog->getPositionY() < HEIGHT_TO_PAUSE)
		{
			this->setVelocity(0);			
			isPrepare = false;


		}
	}
}
void GameLayer::updateFrog(float dt)
{
	CCPoint backgroundScrollVert = ccp(0,- this->getVelocity());
	m_frog->setPosition(ccpAdd(m_frog->getPosition()
		, ccpMult(backgroundScrollVert, dt)));	
	
	if(m_frog->getPositionY() < 0)
	{
		changeEndSceneResult(RESULT_W);
	}
}
void GameLayer::onTheLeaf()
{	
	if(crtLeafObj != NULL)
	{
		int depth = ((CCLeaf *)crtLeafObj)->getDepth();
		int typeLeaf = ((CCLeaf *)crtLeafObj)->getLeafType();
		if(!isReadyForNext)
		{
			((CCLeaf *)crtLeafObj)->getSprite()->setVisible(false);
			changeEndSceneResult(RESULT_C);
		}
		else
		{
		
		}
		

		CCScaleTo *scaleOutAction = CCScaleTo::create(0.0f,1.1f);
		CCScaleTo *scaleInAction = CCScaleTo::create(0.2f,1.00f);
		CCSequence *sq = CCSequence::create(scaleOutAction,scaleInAction,NULL);
		((CCLeaf *)crtLeafObj)->getSprite()->runAction(sq);
	}
}
void GameLayer::changeEndSceneResult(int type_result)
{
	this->setResultType(type_result);	
	isPause = true;
	if(type_result == RESULT_W){
		
		changeAction();
	}
	else{		
		m_frog->stopAllActions();
		CCAnimation *animWater = CCAnimation::createWithSpriteFrames(arrFrameWaterSplash,0.1f);
		CCAnimate *actWaterSplash = CCAnimate::create(animWater);				

		m_frog->runAction(CCSequence::create(actWaterSplash,
					CCCallFunc::create(this, callfunc_selector(GameLayer::changeAction)),					
					NULL));										
	}
	
}
void GameLayer::changeAction(){
	User::Instance().setCrtScore(m_nScore);
	if(User::Instance().getBestScore() < User::Instance().getCrtScore()){
		User::Instance().setBestScore(User::Instance().getCrtScore());
		User::Instance().SaveData();
	}
	CCScene *endScene = EndScene::scene(MODE_ENDLESS,this->getResultType());				
	CCDirector::sharedDirector()->replaceScene(endScene);
	
	
}
void GameLayer::completeJump()
{
	
}