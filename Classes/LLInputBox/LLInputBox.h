//
//  LLInputBox.h
//  Template
//
//  Created by Sheng on 10/1/14.
//
//

/*
 CCTextFieldTTF 
 */

#ifndef __Template__LLInputBox__
#define __Template__LLInputBox__

#include <iostream>
#include "cocos2d.h"
#include "LLTextFieldTTF.h"

#define DEBUG_LLInputBox  1

using namespace cocos2d;

class LLInputBox;

class CC_DLL LLInputBoxDelegate
{
public:
    /**
     @brief    If the sender doesn't want to attach to the IME, return true;
     /////play some animation when keyboard openning
     */
    virtual bool onInputBoxAttachWithIME(LLInputBox * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
    
    /**
     @brief    If the sender doesn't want to detach from the IME, return true;
     /////play some animation when keyboard closing
     */
    virtual bool onInputBoxDetachWithIME(LLInputBox * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
    
    /**
     @brief    If the sender doesn't want to insert the text, return true;
     could check the input here.
     */
    virtual bool beforeInputBoxInsertText(LLInputBox * sender, const char * text, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }
    
    /**
     @brief    If the sender doesn't want to delete the delText, return true;
     */
    virtual bool beforeInputBoxDeleteBackward(LLInputBox * sender, const char * delText, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }
    
    /**
     @brief    If the sender doesn't want to draw, return true.
     */
    virtual bool onDraw(LLInputBox * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};



class LLInputBox: public CCLayerColor, public CCTextFieldDelegate
{
public:
    static LLInputBox* createWithSize(const CCSize& size, const char *placeholder, const char *fontName, float fontSize);
    
    LLInputBox();
    
    ////
    virtual void onEnter();
    virtual void onExit();
    
    /////////////CCTouchDelegate
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
    // 打开输入法
    void openIME();
    // 关闭输入法
    void closeIME();
        
    void setString(const char *text);
    const char* getString();
    
    /** set text tinting */
//    void setFontFillColor(const ccColor3B &tintColor, bool mustUpdateTexture = true);
    
    virtual void setFontColor(const ccColor3B &color);
    virtual void setBackgroudColor(const ccColor3B &color);
    virtual void setCursorColor(const ccColor3B &color);
    
//    virtual const ccColor3B& getColorSpaceHolder();
//    virtual void setColorSpaceHolder(const ccColor3B& color);
//    
//    virtual void setPlaceHolder(const char * text);
//    virtual const char * getPlaceHolder(void);
    
    int getCharCount();
    
    void setDelegate(LLInputBoxDelegate* delegate);
    
    void setMaxStringLength(const unsigned int length);
//    void setMaxCharCount(const unsigned int cout);
    
protected:
    LLInputBoxDelegate* _delegate;
    
    friend class LLTextFieldTTF;
//////////////////CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen);
    virtual bool onDraw(CCTextFieldTTF * sender);
    
    
private:
    LLTextFieldTTF* _textField;

    bool    _isMoved;
    unsigned int _maxStringLength;
    
    void _initContent(const char *placeholder, const char *fontName, float fontSize);
    
    void _onClick(bool inside);
    
    void setColor(){};
};



#endif /* defined(__Template__LLInputBox__) */
