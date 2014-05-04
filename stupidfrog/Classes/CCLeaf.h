#ifndef  _LEAF_OBJ_H_
#define  _LEAF_OBJ_H_
#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  CCLeaf : public cocos2d:: CCObject
{
public:
	CCLeaf();
	virtual ~CCLeaf();
    static CCLeaf *createWithLeafType(int leafType,  cocos2d::CCSpriteBatchNode *pBatchNode,int posType,int depth);
   
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(int, m_nLeafType, LeafType);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);    	    
	CC_SYNTHESIZE(float, m_velocity, Velocity);
	CC_SYNTHESIZE(int , m_posType, PosType);
	CC_SYNTHESIZE(int , m_depth, Depth);
	CC_SYNTHESIZE(bool, m_enable,Enable);

	bool jumpIn();
	void refresh(int pos,int depth);
	void updateSelf(float dt, cocos2d::CCPoint backgroundScrollVert);

private:
	bool initWithLeafType(int leafType,  cocos2d::CCSpriteBatchNode *pBatchNode, int posType,int depth);
	void getPath(cocos2d::CCMoveTo *&moveto, int posType);
	void removeSelf();
	void setVelocityLeaf(float vec);


};

#endif // _APP_DELEGATE_H_

