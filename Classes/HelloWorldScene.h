#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer, public CCTextFieldDelegate
{
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
    virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen);
//    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * sender);
//    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
    
};

#endif // __HELLOWORLD_SCENE_H__
