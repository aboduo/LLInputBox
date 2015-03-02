#include "HelloWorldScene.h"



USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
//    if ( !CCLayerColor::initWithColor(ccc4(0,0,255,255)));
//    {
//        return false;
//    }
    
    
    CCLayerColor* layer_c = CCLayerColor::create(ccc4(0, 0, 150, 255));
    this->addChild(layer_c);
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(HelloWorld::menuCloseCallback));
//    
//	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
//                                origin.y + pCloseItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//    pMenu->setPosition(CCPointZero);
//    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 44);
    ccBlendFunc blendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
    pLabel->setBlendFunc(blendFunc);
    
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    
//    CCLabelTTF* pLabel1 = CCLabelTTF::create("Hello World, Fuck you!", "Arial", 44);
    
    CCLabelTTF* pLabel1 = CCLabelTTF::create("Hello World Fwe !", "Arial", 44, CCSize(0, 0), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
    
    CCSize cs = pLabel1->getContentSize();
//    pLabel1->setDimensions(CCSize(200, 100));
    
    // position the label on the center of the screen
    pLabel1->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height
                             - 180));
    

    
#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       48
    
//    CCTextFieldTTF* m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
//                                                            FONT_NAME,
//                                                            FONT_SIZE);
//    m_pTextField->cocos2d::CCNode::setPosition(visibleSize.width/2, visibleSize.height - 200);
//    addChild(m_pTextField);
    

    
//    LLShaderSprite* sp = LLShaderSprite::create("Mudi_Box.png");
//    sp->setPosition(CCPoint(100, 100));
//    this->addChild(sp);

    
    CCSize inputSize(480, 100);
    
    LLInputBox* input = LLInputBox::createWithSize(inputSize, "姓名", FONT_NAME, FONT_SIZE);
    input->setMaxStringLength(10*3); //
    input->setFontColor(ccORANGE);
    input->setCursorColor(ccGRAY);
    input->cocos2d::CCNode::setPosition( ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 60 + 200) );
    input->setTouchPriority(-1000);
    input->setDelegate(this);
    
    input->ignoreAnchorPointForPosition(false);
    input->setAnchorPoint(ccp(0.5, 0.5));
    
    this->addChild(input);
    
    
    LLInputBox* input1 = LLInputBox::createWithSize(inputSize, "密码", FONT_NAME, FONT_SIZE);
    input1->setMaxStringLength(10*3); //
    input1->setFontColor(ccGREEN);
    input1->setCursorColor(ccGRAY);
    input1->cocos2d::CCNode::setPosition( ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 60 + 200) );
    input1->setTouchPriority(-1000);
    input1->setDelegate(this);
    input1->ignoreAnchorPointForPosition(false);
    input1->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(input1);
    
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - LLInputBoxDelegate

bool HelloWorld::onInputBoxAttachWithIME(LLInputBox * sender)
{
   /////play some animation when keyboard openning
    return false;
}


bool HelloWorld::onInputBoxDetachWithIME(LLInputBox * sender)
{
    /////play some animation when keyboard closing
    return false;
}

/**
 @brief    If the sender doesn't want to insert the text, return true;
 */
bool HelloWorld::beforeInputBoxInsertText(LLInputBox *pSender, const char *text, int nLen)
{
    ////could check the input here.
    return false;
}


bool HelloWorld::beforeInputBoxDeleteBackward(LLInputBox * sender, const char * delText, int nLen)
{    
    return false;
}

