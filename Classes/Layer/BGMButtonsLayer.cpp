#include "BGMButtonsLayer.h"


#define ButtonPre    0.075f
#define ButtonWidthGap   40
#define ButtonHeightGap  30

USING_NS_CC;
using namespace cocos2d::ui;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BGMLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    Button* BGMButton = Button::create(s_P_BGMButton);

    if (BGMButton == nullptr ||
        BGMButton->getContentSize().width <= 0 ||
        BGMButton->getContentSize().height <= 0)
    {
        problemLoading("'s_P_BGMButton' and 's_P_BGMButtonSelected'");
    }
    else
    {
        BGMButton->ignoreContentAdaptWithSize(false);
        BGMButton->setScale9Enabled(true);
        BGMButton->setPressedActionEnabled(false);
        BGMButton->addTouchEventListener(CC_CALLBACK_2(BGMLayer::touchEvent, this));
        float scaledPre = visibleSize.width * ButtonPre / (BGMButton->getContentSize().width);
        BGMButton->setScale(scaledPre);
        float x = originSize.x + BGMButton->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
        float y = originSize.y + BGMButton->getContentSize().height * scaledPre / 2 + ButtonHeightGap;
        BGMButton->setPosition(Vec2(x, y));
        addChild(BGMButton);
    }
    return true;
}


void BGMLayer::SetPostionStartLayer(Button* BGMButton)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    BGMButton->ignoreContentAdaptWithSize(false);
    BGMButton->setScale9Enabled(true);
    BGMButton->setPressedActionEnabled(false);
    BGMButton->addTouchEventListener(CC_CALLBACK_2(BGMLayer::touchEvent, this));
    float scaledPre = visibleSize.width * ButtonPre / (BGMButton->getContentSize().width);
    BGMButton->setScale(scaledPre);
    float x = originSize.x + BGMButton->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
    float y = originSize.y + BGMButton->getContentSize().height * scaledPre / 2 + ButtonHeightGap;
    BGMButton->setPosition(Vec2(x, y));
    addChild(BGMButton);
}


void  BGMLayer::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        se._audioID = se.play2d(s_M_ButtonSelected);
        Button* btn = (Button*)pSender;
        if (bgm.getIfon() == false)//如果BGM没有播放，则继续BGM
        {
            bgm.resumeAll();
            bgm.change();
        }
        else//如果BGM有在播放，则暂停BGM
        {
            bgm.pauseAll();
            bgm.change();
        }
    }
    break;

    case Widget::TouchEventType::ENDED:
    {
        Button* btn = (Button*)pSender;

        if (bgm.getIfon() == false)//如果BGM没有播放，则设置按钮为按下
        {
            btn->loadTextureNormal(s_P_BGMButtonSelected);
        }
        else//如果BGM有在播放，则设置按钮为正常
        {
            btn->loadTextureNormal(s_P_BGMButton);
        }

    }
    break;

    default:
        break;

    }
    return;
}





bool SELayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    Button* SEButton = Button::create(s_P_SEButton);

    if (SEButton == nullptr ||
        SEButton->getContentSize().width <= 0 ||
        SEButton->getContentSize().height <= 0)
    {
        problemLoading("'s_P_SEButton' and 's_P_SEButtonSelected'");
    }
    else
    {
        SEButton->ignoreContentAdaptWithSize(false);
        SEButton->setScale9Enabled(true);
        SEButton->setPressedActionEnabled(false);
        SEButton->addTouchEventListener(CC_CALLBACK_2(SELayer::touchEvent, this));
        float scaledPre = visibleSize.width * ButtonPre / (SEButton->getContentSize().width);
        SEButton->setScale(scaledPre);
        float x = originSize.x + SEButton->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
        float y = originSize.y + SEButton->getContentSize().height * scaledPre * 3 / 2 + ButtonHeightGap * 2;
        SEButton->setPosition(Vec2(x, y));
        addChild(SEButton);
    }
    return true;
}


void SELayer::SetPostionStartLayer(Button* SEButton)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    SEButton->ignoreContentAdaptWithSize(false);
    SEButton->setScale9Enabled(true);
    SEButton->setPressedActionEnabled(false);
    SEButton->addTouchEventListener(CC_CALLBACK_2(SELayer::touchEvent, this));
    float scaledPre = visibleSize.width * ButtonPre / (SEButton->getContentSize().width);
    SEButton->setScale(scaledPre);
    float x = originSize.x + SEButton->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
    float y = originSize.y + SEButton->getContentSize().height * scaledPre * 3 / 2 + ButtonHeightGap * 2;
    SEButton->setPosition(Vec2(x, y));
    addChild(SEButton);
}


void  SELayer::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        Button* btn = (Button*)pSender;
        if (se.getIfon() == false)//如果SE没有播放，则改变状态
        {
            se.change();
        }
        else//如果SE有在播放，则关闭SE，改变状态
        {
            se.change();
        }
    }
    break;

    case Widget::TouchEventType::ENDED:
    {
        Button* btn = (Button*)pSender;

        if (se.getIfon() == false)//如果SE没有播放，则设置按钮为按下
        {
            btn->loadTextureNormal(s_P_SEButtonSelected);
        }
        else//如果SE有在播放，则设置按钮为正常，播放SE
        {
            btn->loadTextureNormal(s_P_SEButton);
            se._audioID = se.play2d(s_M_ButtonSelected);
        }

    }
    break;

    default:
        break;

    }
    return;
}

