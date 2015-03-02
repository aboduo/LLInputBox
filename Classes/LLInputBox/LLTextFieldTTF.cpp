//
//  LLTextFieldTTF.cpp
//  Template
//
//  Created by Sheng on 10/1/14.
//
//

#include "LLTextFieldTTF.h"

static const int  kWidth_Cursor = 4;

LLTextFieldTTF::LLTextFieldTTF()
:_limitSize(CCSize(100, 100))
,_transDis(20)
,m_pCursorSprite(NULL)
,_cursorColor(ccWHITE)
{
    _nUniformLeft = -1;
    _nUniformTransDis = -1;
    
//    _cursorColor = ccRED;
    
}

LLTextFieldTTF::~LLTextFieldTTF()
{
}

LLTextFieldTTF* LLTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    LLTextFieldTTF* pRet = new LLTextFieldTTF();
    if (pRet && pRet->initWithPlaceHolder("", fontName, fontSize))
    {
        pRet->autorelease();
        pRet->_initCursorSprite();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        
        
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void LLTextFieldTTF::_initCursorSprite()
{
    if (m_pCursorSprite)
    {
        m_pCursorSprite->removeFromParent();
        m_pCursorSprite = NULL;
    }
    
    int color = 0xff000000;
    color += _cursorColor.r << 0;
    color += _cursorColor.g << 8;
    color += _cursorColor.b << 16;

    
    ///// init cursor
    int column = kWidth_Cursor;
    int height = m_fFontSize;
    unsigned int pixels[height][column];
    for (int i=0; i<height; ++i) {
        for (int j=0; j<column; ++j) {
//            pixels[i][j] = 0xffffffff;
            pixels[i][j] = color;
        }
    }
    
    CCTexture2D *texture = new CCTexture2D();
    texture->initWithData(pixels, kCCTexture2DPixelFormat_RGB888, 1, 1, CCSizeMake(column, height));
    m_pCursorSprite = CCSprite::createWithTexture(texture);
    m_pCursorSprite->setPosition(ccp(m_obContentSize.width, m_obContentSize.height / 2));
    this->addChild(m_pCursorSprite);
    m_pCursorSprite->setVisible(false);
    
    CCRepeatForever* m_pCursorAction = CCRepeatForever::create((CCActionInterval *) CCSequence::create(CCFadeOut::create(0.25f), CCFadeIn::create(0.25f), NULL));
    m_pCursorSprite->runAction(m_pCursorAction);
    texture->release();
}

void LLTextFieldTTF::setCursorColor(const ccColor3B &color)
{
    _cursorColor = color;
    this->_initCursorSprite();
}

void LLTextFieldTTF::deleteBackward()
{
    int nStrLen = m_pInputText->length();
    if (! nStrLen)
    {
        // there is no string
        return;
    }
    
    // get the delete byte number
    int nDeleteLen = 1;    // default, erase 1 byte
    
    while(0x80 == (0xC0 & m_pInputText->at(nStrLen - nDeleteLen)))
    {
        ++nDeleteLen;
    }
    
    if (m_pDelegate && m_pDelegate->onTextFieldDeleteBackward(this, m_pInputText->c_str() + nStrLen - nDeleteLen, nDeleteLen))
    {
        // delegate doesn't wan't to delete backwards
        return;
    }
    
    // if all text deleted, show placeholder string
    if (nStrLen <= nDeleteLen)
    {
        CC_SAFE_DELETE(m_pInputText);
        m_pInputText = new std::string;
        m_nCharCount = 0;
    }
    
    // set new input text
    std::string sText(m_pInputText->c_str(), nStrLen - nDeleteLen);
    setString(sText.c_str());
}


void LLTextFieldTTF::setString(const char *text)
{
    CCTextFieldTTF::setString(text);
    
    if (m_pCursorSprite)
    {
        
        if (m_pInputText && m_pInputText->length())
        {
            m_pCursorSprite->setPosition(ccp(m_obContentSize.width, m_obContentSize.height/2));
        }
        else
            m_pCursorSprite->setPosition(ccp(0, m_obContentSize.height/2));
    }
    
    if ( (m_obContentSize.width) > _limitSize.width)
    {
        this->setAnchorPoint(ccp(1.0, 0.5));
        this->setPositionX(_limitSize.width );
        
    }
    else
    {
        this->setAnchorPoint(ccp(0.5, 0.5));
        this->setPositionX(_limitSize.width/2);
    }
    
    
}

void LLTextFieldTTF::setLimitSize(cocos2d::CCSize size)
{
    if (_limitSize.width != size.width || _limitSize.height != size.height)
    {
        _limitSize = size;
        this->setString(this->getString());
    }
}

void LLTextFieldTTF::setTransDis(float dis)
{
    _transDis = dis;
}


void LLTextFieldTTF::_initShader()
{
    //    GLchar * vertSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/leftTransparent.vsh").c_str())->getCString();
    //    GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/leftTransparent.fsh").c_str())->getCString();
    //    pProgram->initWithVertexShaderByteArray(vertSource, fragSource);
    
    
    CCGLProgram* pProgram = new CCGLProgram();
    
    ////// compile v and f shader
    pProgram->initWithVertexShaderFilename("leftTransparent.vsh", "leftTransparent.fsh");
    
    //bind attribute
    pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    //link  (must after bindAttribute)
    pProgram->link();
    //get cocos2d-x build-in uniforms
    pProgram->updateUniforms();
    
    //get my own uniforms
    _nUniformLeft = glGetUniformLocation( pProgram->getProgram(), "u_left");
    _nUniformTransDis = glGetUniformLocation( pProgram->getProgram(), "u_transDis");
    
    //set program
    setShaderProgram(pProgram);
    
    //check gl error
    CHECK_GL_ERROR_DEBUG();
    
    pProgram->release();
}


void LLTextFieldTTF::updateBlendFunc(void)
{
    CCAssert (! m_pobBatchNode, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a CCSpriteBatchNode");
    
    // it is possible to have an untextured sprite
    //    if (! m_pobTexture || ! m_pobTexture->hasPremultipliedAlpha())
    {
        m_sBlendFunc.src = GL_SRC_ALPHA;
        m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(false);
    }
    
}

void LLTextFieldTTF::setTexture(CCTexture2D *texture)
{
    // If batchnode, then texture id should be the same
    CCAssert(! m_pobBatchNode || texture->getName() == m_pobBatchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
    // accept texture==nil as argument
    CCAssert( !texture || dynamic_cast<CCTexture2D*>(texture), "setTexture expects a CCTexture2D. Invalid argument");
    
    // shader program
    if (texture)
    {
        //        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
        this->_initShader();
    }
    else
    {
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    }
    
    if (!m_pobBatchNode && m_pobTexture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(m_pobTexture);
        m_pobTexture = texture;
        updateBlendFunc();
    }
}


void LLTextFieldTTF::draw(void)
{
    
    if (m_pDelegate && m_pDelegate->onDraw(this))
    {
        return;
    }
    
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
    
    ccColor3B color = getColor();
    if (!m_pInputText || !m_pInputText->length())
    {
        // draw placeholder
        setColor(m_ColorSpaceHolder);
    }
    
    CC_NODE_DRAW_SETUP();
    
    ////必须这么取得位置，因为本身的大小是变化的，要根据锚点来计算
    CCPoint lb(-_limitSize.width, 0);
    lb = this->convertToWorldSpaceAR(lb);
//    CCLOG("lb.x = %f, lb.y = %f", lb.x, lb.y);
    
//    CCPoint lb1 = CCDirector::sharedDirector()->convertToUI(lb);
//    CCLOG("lb1.x = %f, lb1.y = %f", lb1.x, lb1.y);
//    
//    CCPoint lb2 = CCDirector::sharedDirector()->convertToGL(lb);
//    CCLOG("lb2.x = %f, lb2.y = %f", lb2.x, lb2.y);
    
    float s = CCEGLView::sharedOpenGLView()->getScaleX();
    float left_x = lb.x * s;
//    CCLOG("left_x = %f",left_x);
    
//    getShaderProgram()->setUniformLocationWith1f(_nUniformLeft, lb.x);
    getShaderProgram()->setUniformLocationWith1f(_nUniformLeft, left_x);
    getShaderProgram()->setUniformLocationWith1f(_nUniformTransDis, _transDis);
    
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    ccGLBindTexture2D( m_pobTexture->getName() );
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
    long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
    
#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCPoint vertices[4]={
        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    CCSize s = this->getTextureRect().size;
    CCPoint offsetPix = this->getOffsetPosition();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
    
    CC_INCREMENT_GL_DRAWS(1);
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
    ////恢复原来的颜色
    setColor(color);
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#pragma mark - CCIMEDelegate

bool LLTextFieldTTF::attachWithIME()
{
    bool bRet = CCIMEDelegate::attachWithIME();
    if (bRet)
    {
        // open keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(true);
        }
        m_pCursorSprite->setVisible(true);
    }
    
    return bRet;
}


bool LLTextFieldTTF::detachWithIME()
{
    bool bRet = CCIMEDelegate::detachWithIME();
    if (bRet)
    {
        // close keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(false);
        }
        
    }
    
    if (CCIMEDispatcher::sharedDispatcher()->getCurrentIMEDelegate() != this)
    {
        m_pCursorSprite->setVisible(false);
    }
    
    return bRet;
}

void LLTextFieldTTF::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    
}

void LLTextFieldTTF::keyboardDidShow(CCIMEKeyboardNotificationInfo& info)
{
//    if (CCIMEDispatcher::sharedDispatcher()->getCurrentIMEDelegate() == this)
//    {
//        m_pCursorSprite->setVisible(true);
//    }
}

void LLTextFieldTTF::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
//    if (CCIMEDispatcher::sharedDispatcher()->getCurrentIMEDelegate() == this)
//    {
//        m_pCursorSprite->setVisible(false);
//    }
    
    m_pCursorSprite->setVisible(false);
}

void LLTextFieldTTF::keyboardDidHide(CCIMEKeyboardNotificationInfo& info)
{
//    m_pCursorSprite->setVisible(false);
}

