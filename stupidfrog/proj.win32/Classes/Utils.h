#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/rapidjson.h"
#include "UserModel.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "jni.h"
#include "platform/CCCommon.h"
#endif
//#include "../libs/cocos2dx/platform/android/jni/JniHelper.h"


using namespace cocos2d;

class Utils{
public:
	static CCRenderTexture*		createStroke(CCSprite* label, int size, ccColor3B color, GLubyte opacity); 
	static int					verify(std::string mSeri,std::string mCode,std::string id,std::string  resultText);
	static std::string			makeParams(std::string mSeri,std::string mCode,std::string provider);
	static bool					checkConnection();
	static bool					showAdmob(int isShow);
	static std::string			getUniqueId();
	static long					millisecondNow();

	
	//static std::string base64_decode(std::string const& encoded_string);
	//static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) ;
};
#endif