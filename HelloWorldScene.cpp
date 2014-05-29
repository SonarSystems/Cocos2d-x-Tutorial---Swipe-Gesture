#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{
    if (true == isTouchDown)
    {
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED LEFT");
            
            isTouchDown = false;
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED RIGHT");
            
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            
            isTouchDown = false;
        }
    }
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
