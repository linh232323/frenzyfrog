#ifndef _CCFROG_H_
#define _CCFROG_H_
#include "cocos2d.h"
using namespace cocos2d;
class CCFrog:public cocos2d::CCSprite{
public:
	virtual ~CCFrog();

	void updateFrame(float dt);
	static CCFrog* create(CCSpriteBatchNode *pBatchNode);		
	CC_SYNTHESIZE(CCSprite *,m_sprite,Sprite);	
	CC_SYNTHESIZE(CCPoint, m_targetLeaf,TargetLeaf);
	
	void moveToLeaf(CCPoint  _pts);
private:
	bool init(CCSpriteBatchNode *pBatchNode);
	
	bool isFollow;
};

#endif