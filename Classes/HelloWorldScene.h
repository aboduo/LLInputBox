#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "LLInputBox.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer, public LLInputBoxDelegate
{
//    CCNode* container;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    
    ////CCTextFieldDelegate
    virtual bool beforeInputBoxInsertText(LLInputBox * sender, const char * text, int nLen);
    virtual bool beforeInputBoxDeleteBackward(LLInputBox * sender, const char * delText, int nLen);
    virtual bool onInputBoxAttachWithIME(LLInputBox * sender);
    virtual bool onInputBoxDetachWithIME(LLInputBox * sender);
    
};

#endif // __HELLOWORLD_SCENE_H__
