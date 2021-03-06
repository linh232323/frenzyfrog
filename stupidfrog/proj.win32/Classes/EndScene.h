#ifndef __END_SCENE_H__
#define __END_SCENE_H__


#define RESULT_C 0
#define RESULT_W 1

#define MODE_NORMAL 0
#define MODE_ENDLESS 1
#include "cocos2d.h"

class EndScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithResult(int mode,int result);  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene(int mode,int result);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
	static EndScene* createWithResult(int mode,int result);
    //CREATE_FUNC(EndScene);

	CC_SYNTHESIZE(int , mode, Mode);
private :
	void replay(CCObject *sender);
	void ranking(CCObject *sender);
	void close(CCObject *sender);
};

#endif // __HELLOWORLD_SCENE_H__
