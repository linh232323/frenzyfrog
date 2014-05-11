#include "CCMenuItemSpriteCustom.h"
//
//CCMenuItemSpriteCustom
//

CCNode * CCMenuItemSpriteCustom::getNormalImage()
{
    return m_pNormalImage;
}

void CCMenuItemSpriteCustom::setNormalImage(CCNode* pImage)
{
    if (pImage != m_pNormalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kNormalTag);
            pImage->setAnchorPoint(ccp(0, 0));
        }

        if (m_pNormalImage)
        {
            removeChild(m_pNormalImage, true);
        }

        m_pNormalImage = pImage;
        this->setContentSize(m_pNormalImage->getContentSize());
        this->updateImagesVisibility();
    }
}

CCNode * CCMenuItemSpriteCustom::getSelectedImage()
{
    return m_pSelectedImage;
}

void CCMenuItemSpriteCustom::setSelectedImage(CCNode* pImage)
{
    if (pImage != m_pNormalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kSelectedTag);
            pImage->setAnchorPoint(ccp(0, 0));
        }

        if (m_pSelectedImage)
        {
            removeChild(m_pSelectedImage, true);
        }

        m_pSelectedImage = pImage;
        this->updateImagesVisibility();
    }
}

CCNode * CCMenuItemSpriteCustom::getDisabledImage()
{
    return m_pDisabledImage;
}

void CCMenuItemSpriteCustom::setDisabledImage(CCNode* pImage)
{
    if (pImage != m_pNormalImage)
    {
        if (pImage)
        {
            addChild(pImage, 0, kDisableTag);
            pImage->setAnchorPoint(ccp(0, 0));
        }

        if (m_pDisabledImage)
        {
            removeChild(m_pDisabledImage, true);
        }

        m_pDisabledImage = pImage;
        this->updateImagesVisibility();
    }
}

CCMenuItemSpriteCustom * CCMenuItemSpriteCustom::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite)
{
    return CCMenuItemSpriteCustom::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

CCMenuItemSpriteCustom * CCMenuItemSpriteCustom::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
    return CCMenuItemSpriteCustom::create(normalSprite, selectedSprite, NULL, target, selector);
}

CCMenuItemSpriteCustom * CCMenuItemSpriteCustom::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    CCMenuItemSpriteCustom *pRet = new CCMenuItemSpriteCustom();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
    pRet->autorelease();
    return pRet;
}

bool CCMenuItemSpriteCustom::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItem::initWithTarget(target, selector); 
    setNormalImage(normalSprite);
    setSelectedImage(selectedSprite);
    setDisabledImage(disabledSprite);

    if(m_pNormalImage)
    {
        this->setContentSize(m_pNormalImage->getContentSize());
    }
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    return true;
}


/**
 @since v0.99.5
 */
void CCMenuItemSpriteCustom::selected()
{
    CCMenuItem::selected();
	
	
    if (m_pNormalImage)
    {
        if (m_pDisabledImage)
        {
            m_pDisabledImage->setVisible(false);
        }

        if (m_pSelectedImage)
        {
            m_pNormalImage->setVisible(false);
            m_pSelectedImage->setVisible(true);
        }
        else
        {
            m_pNormalImage->setVisible(true);
        }
    }
	stopAllActions();
	runAction(CCScaleTo::create(0.01f,1.07f));
}

void CCMenuItemSpriteCustom::unselected()
{
    CCMenuItem::unselected();	
    if (m_pNormalImage)
    {
        m_pNormalImage->setVisible(true);

        if (m_pSelectedImage)
        {
            m_pSelectedImage->setVisible(false);
        }

        if (m_pDisabledImage)
        {
            m_pDisabledImage->setVisible(false);
        }
    }
	stopAllActions();
	runAction(CCScaleTo::create(0.01f,1.0f));
}
void CCMenuItemSpriteCustom::setEnabled(bool bEnabled)
{
    if( m_bEnabled != bEnabled ) 
    {
        CCMenuItem::setEnabled(bEnabled);
        this->updateImagesVisibility();
    }
}
void CCMenuItemSpriteCustom::updateImagesVisibility()
{
    if (m_bEnabled)
    {
        if (m_pNormalImage)   m_pNormalImage->setVisible(true);
        if (m_pSelectedImage) m_pSelectedImage->setVisible(false);
        if (m_pDisabledImage) m_pDisabledImage->setVisible(false);
    }
    else
    {
        if (m_pDisabledImage)
        {
            if (m_pNormalImage)   m_pNormalImage->setVisible(false);
            if (m_pSelectedImage) m_pSelectedImage->setVisible(false);
            if (m_pDisabledImage) m_pDisabledImage->setVisible(true);
        }
        else
        {
            if (m_pNormalImage)   m_pNormalImage->setVisible(true);
            if (m_pSelectedImage) m_pSelectedImage->setVisible(false);
            if (m_pDisabledImage) m_pDisabledImage->setVisible(false);
        }
    }
}