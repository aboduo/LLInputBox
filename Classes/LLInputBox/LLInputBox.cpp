//
//  LLInputBox.cpp
//  Template
//
//  Created by Sheng on 10/1/14.
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
,_delegate(NULL)
,_maxStringLength(30)
{
//    m_beginPos = ccp(-1, -1);
    
}

LLInputBox* LLInputBox::createWithSize(const CCSize& size, const char *placeholder, const char *fontName, float fontSize)
{
    LLInputBox* pLayer = new LLInputBox();
    
#if (DEBUG_LLInputBox > 0)
    if( pLayer && pLayer->initWithColor(ccc4(100,200,50,100), size.width, size.height))
#else
    if( pLayer && pLayer->init())
#endif
    {
        pLayer->autorelease();
        pLayer->setContentSize(size);
        pLayer->_initContent(placeholder, fontName, fontSize);
        
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}


void LLInputBox::_initContent(const char *placeholder, const char *fontName, float fontSize)
{
    this->setTouchMode(kCCTouchesOneByOne);
//    this->setTouchEnabled(true);
    
    
    _textField = LLTextFieldTTF::textFieldWithPlaceHolder(placeholder, fontName, fontSize);
    _textField->setPosition(ccp(m_obContentSize.width/2, m_obContentSize.height/2));
    _textField->setLimitSize(m_obContentSize);
    _textField->setDelegate(this);
    this->addChild(_textField);
    
}

void LLInputBox::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(),false);

}

void LLInputBox::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void LLInputBox::openIME()
{
    if (_textField)
    {
        _textField->attachWithIME();
    }
}

void LLInputBox::closeIME()
{
    if (_textField)
    {
        _textField->detachWithIME();
    }
}

void LLInputBox::_onClick(bool inside)
{
    if (inside)
    {
        this->openIME();
    }
    else
        this->closeIME();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - get & set

void LLInputBox::setDelegate(LLInputBoxDelegate* delegate)
{
    _delegate = delegate;
}

void LLInputBox::setCursorColor(const ccColor3B &color)
{
    if (_textField)
    {
        _textField->setCursorColor(color);
    }
}

void LLInputBox::setString(const char *text)
{
    if (_textField)
    {
        _textField->setString(text);
    }
}

const char* LLInputBox::getString()
{
    if (_textField)
    {
        return _textField->getString();
    }
    
    return NULL;
}

void LLInputBox::setFontColor(const ccColor3B &color)
{
    if (_textField)
    {
        _textField->setColor(color);
    }
}

void LLInputBox::setBackgroudColor(const ccColor3B &color)
{
    CCLayerColor::setColor(color);
}

//void LLInputBox::setFontFillColor(const ccColor3B &tintColor, bool mustUpdateTexture)
//{
//    if (_textField)
//    {
//        _textField->setFontFillColor(tintColor, mustUpdateTexture);
//    }
//}


int LLInputBox::getCharCount()
{
    if (_textField)
    {
        return _textField->getCharCount();
    }
    
    return 0;
}


void LLInputBox::setMaxStringLength(const unsigned int length)
{
    _maxStringLength = length;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CCTouchDelegate

bool LLInputBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (this->isVisible())
    {
        _isMoved = false;
        return true;
    }
    else
        return false;
    
}

void LLInputBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    _isMoved = true;
}

void LLInputBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! _textField)
    {
        return;
    }
    
    
//    if (_isMoved)
//    {
//        _isMoved = false;
//        return;
//    }
    
    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpace(pTouch);
    CCLOG("LLInputBox:%s:clickedAt(%f,%f)", __FUNCTION__, point.x, point.y);
    
    rect.size = m_obContentSize;
    CCLOG("LLInputBox:%s:TrackNode at(origin:%.2f,%.2f, size:%.2f,%.2f)", __FUNCTION__,
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    CCLOG("LLInputBox:is inside:%d", rect.containsPoint(point));
    CCLOG("LLInputBox:is moved:%d",_isMoved);
    
//    this->_onClick(rect.containsPoint(point));
    CCLOG("----------------------------------");
    
    if (rect.containsPoint(point) && !_isMoved)
    {
        this->openIME();
    }
    else if(!rect.containsPoint(point))
    {
        this->closeIME();
    }
    
    _isMoved = false;
    
}





///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - CCTextFieldDelegate
bool LLInputBox::onTextFieldAttachWithIME(CCTextFieldTTF * sender)
{
    if (_delegate)
    {
        return _delegate->onInputBoxAttachWithIME(this);
    }
    
    return false;
}

bool LLInputBox::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    if (_delegate)
    {
        return _delegate->onInputBoxDetachWithIME(this);
    }
    
    return false;
}

bool LLInputBox::onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen)
{
    if ( (strlen(sender->getString()) + nLen) > _maxStringLength )
    {
        return true;
    }
    
    if (_delegate)
    {
        return _delegate->beforeInputBoxInsertText(this, text, nLen);
    }
    
    return false;
}

bool LLInputBox::onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen)
{
    if (_delegate)
    {
        return _delegate->beforeInputBoxDeleteBackward(this, delText, nLen);
    }
    
    return false;
}

bool LLInputBox::onDraw(CCTextFieldTTF * sender)
{
    if (_delegate)
    {
        return _delegate->onDraw(this);
    }
    
    return false;
}


