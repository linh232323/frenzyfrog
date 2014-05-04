//
//  GameLayer.h
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#ifndef __GameLayer__
#define __GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
#include "SimpleAudioEngine.h"


class GameLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    GameLayer();
    virtual ~GameLayer();
    virtual bool init();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);    
	CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode2, BatchNode2);    
	CC_SYNTHESIZE(int, m_crtLeaf, CrtLeaf);    
	CC_SYNTHESIZE(int, m_nextLeft, NextLeaf);    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pLeafs, Leafs);
	CC_SYNTHESIZE(int , m_vec, Velocity);
	
	CC_SYNTHESIZE(CCArray *, arrFrameJump,FramesJump);

	//std::vector<CCLeaf *> Leafs;
	
private:    

	CCSize winSize;
	CCPoint origin;

    int m_nScore;
    void initFishes();
    void initBackground();    
    void initFrames();
	void initLeafs();
	void initFrog();
	void initFinalLayer();
    void updateGame(float dt);  
	void updateFrog(float dt);
	void updateLeaf(float dt);
	void changeEndSceneResult();
	void onTheLeaf();
    void addLeaf();

	
	CCParallaxNodeExtras * m_backgroundNode;
    CCSprite * water1;
	CCSprite * water2;
	CCSprite * m_frog;
	CCPoint  crtLeaf;
	CCObject * crtLeafObj;

	int crtDepth;
	int crtGenDepth;
	bool isFollow;

	void completeJump();
	bool isPrepare;
	bool isReady;
	bool isReadyForNext;
	bool isPause;

	CCLabelBMFont *lbScore;

	
};

#endif /* defined(__FishingJoy__GameLayer__) */
