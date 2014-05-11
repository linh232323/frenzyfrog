#ifndef _CCMENU_ITEM_SPRITE_CUSTOM_
#define _CCMENU_ITEM_SPRITE_CUSTOM_

#include "cocos2d.h"

using namespace cocos2d;

class CC_DLL CCMenuItemSpriteCustom : public CCMenuItem
{
    /** the image used when the item is not selected */
    CC_PROPERTY(CCNode*, m_pNormalImage, NormalImage);
    /** the image used when the item is selected */
    CC_PROPERTY(CCNode*, m_pSelectedImage, SelectedImage);
    /** the image used when the item is disabled */
    CC_PROPERTY(CCNode*, m_pDisabledImage, DisabledImage);
public:
    /**
     *  @js ctor
     */
    CCMenuItemSpriteCustom()
    :m_pNormalImage(NULL)
    ,m_pSelectedImage(NULL)
    ,m_pDisabledImage(NULL)
    {}

    /** creates a menu item with a normal, selected and disabled image*/
    static CCMenuItemSpriteCustom * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector 
     * @lua NA
     */
    static CCMenuItemSpriteCustom * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector 
     * @lua NA
     */
    static CCMenuItemSpriteCustom * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    
    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
protected:
    virtual void updateImagesVisibility();
};

#endif