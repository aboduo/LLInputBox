//
//  LLInputBox.h
//  Template
//
//  Created by Sheng on 5/28/14.
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

using namespace cocos2d;

class LLInputBox: public CCLayerColor
{
public:
    static LLInputBox* createWithSize(const CCSize& size, const char *placeholder, const char *fontName, float fontSize);
    
    LLInputBox();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void setDelegate(CCTextFieldDelegate* delegate);
    
    /** set text tinting */
    void setFontFillColor(const ccColor3B &tintColor, bool mustUpdateTexture = true);
    
private:
    LLTextFieldTTF* _textField;

    bool    _isMoved;
    
    void _initContent(const char *placeholder, const char *fontName, float fontSize);
    
    void _onClick(bool inside);
    
};



#endif /* defined(__Template__LLInputBox__) */
