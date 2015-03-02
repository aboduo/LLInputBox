//
//  LLTextFieldTTF.h
//  Template
//
//  Created by Sheng on 10/1/14.
//
//

#ifndef __Template__LLTextFieldTTF__
#define __Template__LLTextFieldTTF__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class LLTextFieldTTF: public CCTextFieldTTF
{
    friend class LLInputBox;
public:
    LLTextFieldTTF();
    ~LLTextFieldTTF();
    
    static LLTextFieldTTF* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    
    virtual void setString(const char *text);
    
    virtual void setTexture(CCTexture2D *texture);
    
    virtual void draw(void);
    
/////////////////////////////////////////////////CCIMEDelegate
    /**
     @brief    Open keyboard and receive input text.
     */
    virtual bool attachWithIME();
    
    /**
     @brief    End text input and close keyboard.
     */
    virtual bool detachWithIME();
    
    //////////////////////////////////////////////////////////////////////////
    // keyboard show/hide notification
    //////////////////////////////////////////////////////////////////////////
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardDidShow(CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardDidHide(CCIMEKeyboardNotificationInfo& info);
    
    
protected:
    virtual void updateBlendFunc(void);
    
    virtual void deleteBackward();
    
    void setLimitSize(CCSize size);
    void setTransDis(float dis);
    void setCursorColor(const ccColor3B &color);
    
private:
    GLint       _nUniformLeft;
    GLint       _nUniformTransDis;
    
    CCSprite    *m_pCursorSprite;
    
    CCSize  _limitSize;
    float   _transDis;
    
    ccColor3B   _cursorColor;
    
    void _initCursorSprite();
    
    void _initShader();

};


#endif /* defined(__Template__LLTextFieldTTF__) */
