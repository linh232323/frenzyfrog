#include "CCFrog.h"

CCFrog::~CCFrog(){

}

void CCFrog::updateFrame(float dt)
{
	
	if(isFollow == true)
	{
		
		if(this->getTargetLeaf().getDistance(this->getSprite()->getPosition()) > 2)
		{
			if(this->getTargetLeaf().getDistance(this->getSprite()->getPosition()) > 50)
			{
			//	this->setTexture(CCTextureCache::sharedTextureCache()->addImage("frog_01.png"));
				
			}
			else
			{
			//	this->setTexture(CCTextureCache::sharedTextureCache()->addImage("frog_02.png"));
				
			}
			if(!isFollow)
			{
				
				
			}
			
		}
		else
		{
			//this->setTexture(CCTextureCache::sharedTextureCache()->addImage("frog.png"));			
			isFollow = false;
		}

		
	}
}



CCFrog *CCFrog::create( CCSpriteBatchNode *pBatchNode)
{
    CCFrog *frog = new CCFrog();
    if(frog && frog->init( pBatchNode))
    {
        frog->autorelease();
        return frog;
    }
    else
    {
        delete frog;
        return NULL;
    }
}


bool CCFrog::init( CCSpriteBatchNode *pBatchNode)
{	    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();	
	isFollow  = false;
	this->setBatchNode(pBatchNode);	

    this->getBatchNode()->addChild(CCSprite::createWithSpriteFrameName("frog.png"),9999);

	this->setPosition(ccp(winSize.width/2 , winSize.height/2));

	
    return true;
}
void CCFrog::moveToLeaf(CCPoint _leaf)
{	
	//this->setTargetLeaf(_leaf);
	this->setPosition(ccp(200,200));
	//this->runAction(CCMoveTo::create(0.5f, _leaf));
	//isFollow  = true;
}
