#ifndef __BEGIN_SCENE_H__
#define __BEGIN_SCENE_H__

#include "cocos2d.h"

class BeginScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(BeginScene);

	cocos2d::CCSprite *m_frog;
	cocos2d::CCSprite *m_leaf1;
	cocos2d::CCSprite *m_leaf2;

private :
	void replay(CCObject *sender);
	void ranking(CCObject *sender);
	void close(CCObject *sender);
	void onComplete();
	void changeScene();
	

};

#endif // __HELLOWORLD_SCENE_H__
