//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

//#include "GameLayer.h"
#include "CCLeaf.h"

using namespace cocos2d;
CCLeaf::CCLeaf():
	m_enable(false)
{
}
CCLeaf::~CCLeaf()
{
    CCLOG("destruct fish %d", m_nLeafType);
}

CCLeaf *CCLeaf::createWithLeafType(int leafType,  CCSpriteBatchNode *pBatchNode,int posType,int depth)
{
    CCLeaf *leaf = new CCLeaf();
    if(leaf && leaf->initWithLeafType(leafType, pBatchNode,posType,depth))
    {
        leaf->autorelease();
        return leaf;
    }
    else
    {
        delete leaf;
        return NULL;
    }
}


bool CCLeaf::initWithLeafType(int leafType,  CCSpriteBatchNode *pBatchNode,int posType,int depth)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    this->setLeafType(leafType);	
  
    this->setBatchNode(pBatchNode);
	this->setPosType(posType);
	this->setDepth(depth);
    CCArray *frames = CCArray::create();
	
    
    CCString *originalFrameName = CCString::createWithFormat("leaf_0%d.png", leafType);
    
    m_pSprite = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());    
    
     
	m_pSprite->setPosition(ccp(origin.x + (this->getPosType() + 1 )* winSize.width / 5,origin.y + winSize.height));		
	m_pSprite->setVisible(false);
	this->setVelocityLeaf(100);
    
    //this->getGame()->getLeafs()->addObject(this);
    this->getBatchNode()->addChild(m_pSprite);

    return true;
}

void offsetPoint(CCPoint& pt, float offsetX, float offsetY)
{
    pt.x += offsetX;
    pt.y += offsetY;
}

void CCLeaf::setVelocityLeaf(float vec)
{

	
	
}
void CCLeaf::updateSelf(float dt,CCPoint backgroundScrollVert)
{
	if(this->getEnable() && m_pSprite != NULL){

		if(this->getSprite()->getPositionY() - this->getSprite()->getContentSize().width/2 < 0 )
		{
			removeSelf();
		}
		else
		{
			this->getSprite()->setPosition(ccpAdd(this->getSprite()->getPosition()
				, ccpMult(backgroundScrollVert, dt)));	
		}
	}


}
void CCLeaf::removeSelf()
{
	//m_pSprite->removeFromParentAndCleanup(false);
    //this->getGame()->getLeafs()->removeObject(this);	    
	this->setEnable(false);
	this->getSprite()->setVisible(false);
}
bool CCLeaf::jumpIn()
{
	switch(this->getLeafType())
	{
		case 0:
			this->removeSelf();
			return false;
		case 1:
			return true;
		default:
			return true;
	}
}

void CCLeaf::refresh(int pos,int depth)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->setEnable(true);
	this->getSprite()->setVisible(true);
	this->setPosType(pos);
	this->setDepth(depth);
	this->getSprite()->setPosition(ccp(origin.x + (this->getPosType() + 1 )* winSize.width / 5,origin.y + winSize.height));			
}