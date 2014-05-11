#include "Utils.h"

#define DEFAULT_ID "1"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "IOSHelp-Interface.h"
#endif
CCRenderTexture* Utils::createStroke(CCSprite* label, int size, ccColor3B color, GLubyte opacity){
	
	CCRenderTexture* rt = CCRenderTexture::create(label->getTexture()->getContentSize().width + size * 2.f,
                                                      label->getTexture()->getContentSize().height+size * 2.f);
    CCPoint originalPos = label->getPosition();

    ccColor3B originalColor = label->getColor();

    GLubyte originalOpacity = label->getOpacity();

	bool originalVisibility = label->isVisible();

    label->setColor(color);

    label->setOpacity(opacity);

	label->setVisible(true);
	
    ccBlendFunc originalBlend = label->getBlendFunc();

    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE};

    label->setBlendFunc(bf);

    CCPoint bottomLeft = ccp(
        label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size, 
        label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);

  

   
    rt->begin();

    for (int i=0; i<360; i+= 15) // you should optimize that for your needs
    {
        label->setPosition(
            ccp(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*size, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*size)
            );
        label->visit();
    }
    rt->end();

    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    label->setOpacity(originalOpacity);
	label->setVisible(originalVisibility);
    rt->setPosition(originalPos);

    return rt;
}

int Utils::verify(std::string mSeri,std::string mCode,std::string id,std::string  resultText){
	rapidjson::Document document;	
	if (document.Parse<0>(resultText.c_str()).HasParseError() == false)
	{
			const int errorCode = document["error"].GetInt();
			

			CCLOG("%d",errorCode);
			if( errorCode != 200)
			{
				return 0;
			}
			else
			{
				const int coin = document["coin"].GetInt();
				//const char* auth = document["auth"].GetString();	
				//if(strcmp (auth,"1") != 0)
				{
				//	return 0;
				}
				//else
				{
					
					return coin;
				}
			}	
	}        		 
	return 0;
}
std::string  Utils::makeParams(std::string mSeri,std::string mCode,std::string provider){
	return "";
}
std::string Utils::getUniqueId(){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
        
		if(JniHelper::getStaticMethodInfo(minfo, "com/zinzin/stupidfrog/stupidfrog", 
			"getDeviceUniqueId",
			 "()Ljava/lang/String;"))
		{			
			jstring return_value = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
			string ret = JniHelper::jstring2string(return_value);	
			CCLOG("ID %s",ret.c_str());
			return ret;
		}

	}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    std::string udid = getUDID();
    char rmchar[] = "][\/. ";
    std::replace(udid.begin(),udid.end(),'-',' ');
	return udid;
#endif
	return DEFAULT_ID;
}
bool Utils::checkConnection(){
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;

		if(JniHelper::getStaticMethodInfo(minfo, "com/game3979/stupidfrog/stupidfrog", 
			"checkNetworkConnectivity",
			"()Z"))
		{						
			return (bool)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		}
	}
#endif
#if CC_TARGET_PLATFORM==CC_PLATFORM_IOS
	{
		return false;
	}
#endif
	return true;
}
long Utils::millisecondNow()
{
   struct cc_timeval now;
   CCTime::gettimeofdayCocos2d(&now, NULL);
   return (now.tv_sec * 1000 + now.tv_usec / 1000);
	
}

bool Utils::showAdmob(int isShow = 0){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
		if(isShow == 1){
			if(JniHelper::getStaticMethodInfo(minfo, "com/game3979/stupidfrog/stupidfrog", 
				"showAdmobJNI",
				"()Ljava/lang/String;"))
			{				
				 minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
				return true;
			}
		}
		else{
			if(JniHelper::getStaticMethodInfo(minfo, "com/game3979/stupidfrog/stupidfrog", 
				"hideAdmobJNI",
				"()Ljava/lang/String;"))
			{						
				minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
				return true;
			}
		}
	}
#endif
#if CC_TARGET_PLATFORM==CC_PLATFORM_IOS
	{
		return false;
	}
#endif
	return true;
}