//
//  LLInputBox.cpp
//  Template
//
//  Created by Sheng on 5/28/14.
//
//

#include "LLInputBox.h"

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();

    return rc;
}

LLInputBox::LLInputBox()
:_isMoved(false)
,_textField(NULL)
{
//    m_beginPos = ccp(-1, -1);
    
}

LLInputBox* LLInputBox::createWithSize(const CCSize& size, const char *placeholder, const char *fontName, float fontSize)
{
    LLInputBox* pLayer = new LLInputBox();
    if( pLayer && pLayer->initWithColor(ccc4(100,200,50,200), size.width, size.height))
    {
        pLayer->autorelease();
        
        pLayer->_initContent(placeholder, fontName, fontSize);
        
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}


void LLInputBox::_initContent(const char *placeholder, const char *fontName, float fontSize)
{
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    
    
    _textField = LLTextFieldTTF::textFieldWithPlaceHolder(placeholder, fontName, fontSize);
    _textField->setPosition(ccp(m_obContentSize.width/2, m_obContentSize.height/2));
    _textField->setLimitSize(m_obContentSize);
    this->addChild(_textField);
    
}

void LLInputBox::setDelegate(cocos2d::CCTextFieldDelegate *delegate)
{
    if (_textField)
    {
        _textField->setDelegate(delegate);
    }
}

void LLInputBox::setFontFillColor(const ccColor3B &tintColor, bool mustUpdateTexture)
{
    if (_textField)
    {
        _textField->setFontFillColor(tintColor, mustUpdateTexture);
    }
}


bool LLInputBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint p = this->convertTouchToNodeSpace(pTouch);
    
    CCRect bBox= CCRect(0, 0, m_obContentSize.width, m_obContentSize.height);
    
    if (this->isVisible() && bBox.containsPoint(p) )
    {
        _isMoved = false;
        return true;
    }
    return false;
}

void LLInputBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("%s", __FUNCTION__);
    
    _isMoved = true;
}

void LLInputBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! _textField)
    {
        return;
    }
    
//    CCPoint endPos = pTouch->getLocation();
//    
//    float delta = 20.0f;
//    if (::abs(endPos.x - m_beginPos.x) > delta
//        || ::abs(endPos.y - m_beginPos.y) > delta )
//    {
//        // not click
//        m_beginPos.x = m_beginPos.y = -1;
//        return;
//    }
    
    if (_isMoved)
    {
        _isMoved = false;
        return;
    }
    
    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpace(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    rect.size = m_obContentSize;
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    
    this->_onClick(rect.containsPoint(point));
    CCLOG("----------------------------------");
    
    _isMoved = false;
    
}


void LLInputBox::_onClick(bool inside)
{
    if (inside) {
        _textField->attachWithIME();
    }
    else
        _textField->detachWithIME();
}






