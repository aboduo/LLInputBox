#include "HelloWorldScene.h"
#include "LLInputBox.h"


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
    
    
    LLInputBox* input = LLInputBox::createWithSize(CCSize(300, 100), "姓名", FONT_NAME, FONT_SIZE);
    input->cocos2d::CCNode::setPosition( (visibleSize.width-300)/2, visibleSize.height - 200);
    input->setTouchPriority(-1000);
    input->setDelegate(this);
    this->addChild(input);
    
    
    return true;
}

/**
 @brief    If the sender doesn't want to insert the text, return true;
 */
bool HelloWorld::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
{
    CCLOG("::::::::: input %d count", pSender->getCharCount());
    CCLOG("::::::::: input %s", pSender->getString());
    
    if (pSender->getCharCount() > 30)
    {
        return true;
    }
    
    return false;
}


bool HelloWorld::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
{

    CCLOG("::::::::: input %d count", pSender->getCharCount());
    
    return false;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
