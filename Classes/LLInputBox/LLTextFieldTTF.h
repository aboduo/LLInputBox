//
//  LLTextFieldTTF.h
//  Template
//
//  Created by Sheng on 5/28/14.
//
//

#ifndef __Template__LLTextFieldTTF__
#define __Template__LLTextFieldTTF__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class LLTextFieldTTF: public CCTextFieldTTF
{
public:
    LLTextFieldTTF();
    
    static LLTextFieldTTF* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    
    virtual void setString(const char *text);
    
    virtual void setTexture(CCTexture2D *texture);
    
    virtual void draw(void);
    
    void setLimitSize(CCSize size);
    void setTransDis(float dis);
    
    /**
     @brief    Open keyboard and receive input text.
     */
    virtual bool attachWithIME();
    
    /**
     @brief    End text input and close keyboard.
     */
    virtual bool detachWithIME();
    
    
protected:
    virtual void updateBlendFunc(void);
    
    virtual void deleteBackward();
    
private:
    GLint       _nUniformLeft;
    GLint       _nUniformTransDis;
    
    CCSprite    *m_pCursorSprite;
    
    CCSize  _limitSize;
    float   _transDis;
    
    
    void _initCursorSprite(const int mHeight);
    
    
    void _initShader();

};


#endif /* defined(__Template__LLTextFieldTTF__) */
