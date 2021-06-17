/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:ÔÝÍ£ÄÚÈÝ
 ****************************************************************************/
#include "StopLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



bool StopLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    //ÏÔÊ¾¿ò¼Ü
    auto sprite = Sprite::create(s_P_StopFrame);
    float scaledPre = visibleSize.width * StopFramePre / (sprite->getContentSize().width);
    sprite->setContentSize(Size(sprite->getContentSize().width * scaledPre, sprite->getContentSize().height * scaledPre));
    sprite->setPosition(Vec2(visibleSize / 2) + originSize);
    _stopLayer->addChild(sprite, stopLayerTag);

    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;

    {
        Button* resumeButton = Button::create(s_P_ResumeButton, s_P_ResumeButtonSelected);
        float scaledPre = visibleSize.width * ButtonPre / (resumeButton->getContentSize().width);
        resumeButton->setScale(scaledPre);
        resumeButton->setAnchorPoint(Vec2(0.5, 0));

        resumeButton->ignoreContentAdaptWithSize(false);
        resumeButton->setScale9Enabled(true);
        resumeButton->setPressedActionEnabled(false);
        resumeButton->addTouchEventListener(CC_CALLBACK_2(StopLayer::touchEventResumeButton, this));

        float x = originSize.x + visibleSize.width / 2;
        resumeButton->setPosition(Vec2(x, y));
        _stopLayer->addChild(resumeButton, stopLayerStuffTag);
    }

    {
        auto seButton = SEButton::create();
        seButton->setPostionStopLayer(sprite);
        _stopLayer->addChild(seButton, stopLayerStuffTag);
        auto bgmButton = BGMButton::create();
        bgmButton->setPostionStopLayer(sprite);
        _stopLayer->addChild(bgmButton, stopLayerStuffTag);
        auto infoButton = InfoButton::create();
        infoButton->setPostionStopLayer(sprite);
        _stopLayer->addChild(infoButton, stopLayerStuffTag);
    }

    {
        Button* homeButton = Button::create(s_P_HomeButton, s_P_HomeButtonSelected);
        float scaledPre = visibleSize.width * ButtonPre / (homeButton->getContentSize().width);
        homeButton->setScale(scaledPre);
        homeButton->setAnchorPoint(Vec2(0.5, 0));

        homeButton->ignoreContentAdaptWithSize(false);
        homeButton->setScale9Enabled(true);
        homeButton->setPressedActionEnabled(false);
        homeButton->addTouchEventListener(CC_CALLBACK_2(StopLayer::touchEventHomeButton, this));

        float x = originSize.x + visibleSize.width / 2 + homeButton->getContentSize().width * scaledPre + ButtonWidthGapInStop;
        homeButton->setPosition(Vec2(x, y));
        _stopLayer->addChild(homeButton, stopLayerStuffTag);
    }

    this->addChild(_stopLayer);
    return true;
}


void StopLayer::touchEventResumeButton(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        se._audioID = se.play2d(s_M_ButtonSelected);
        this->removeChild(_stopLayer);
    }
    break;

    default:
        break;

    }
    return;
}


void StopLayer::touchEventHomeButton(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        bgm.stopAll();
        se._audioID = se.play2d(s_M_ButtonSelected);
        Director::getInstance()->replaceScene(StartScene::createScene());
    }
    break;

    default:
        break;

    }
    return;
}




bool StopButton::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    {
        //ÉèÖÃ¼àÌýÆ÷
        auto listener = EventListenerTouchOneByOne::create();
        listener->setEnabled(true);
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [this](Touch* touch, Event* event) {

            auto target = static_cast<Sprite*>(event->getCurrentTarget());

            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode))
            {
                se._audioID = se.play2d(s_M_ButtonSelected);
                auto stopLayer = StopLayer::create();
                this->addChild(stopLayer);

                return true;
            }
            return false;
        };

        listener->onTouchMoved = [](Touch* touch, Event* event) {
        };

        listener->onTouchEnded = [=](Touch* touch, Event* event) {
        };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _stopButton);

        _listener = listener;

    }

    {
        //ÉèÖÃÎ»ÖÃ
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto originSize = Director::getInstance()->getVisibleOrigin();

        float scaledPre = visibleSize.width * ButtonPre / (_stopButton->getContentSize().width);
        _stopButton->setContentSize(Size(_stopButton->getContentSize().width * scaledPre, _stopButton->getContentSize().height * scaledPre));

        float x = originSize.x + visibleSize.width - _stopButton->getContentSize().width / 2 - ButtonWidthGap;
        float y = originSize.y + visibleSize.height - _stopButton->getContentSize().height / 2 - ButtonHeightGap;
        _stopButton->setPosition(Vec2(x, y));
        addChild(_stopButton);
    }

    return true;
}
