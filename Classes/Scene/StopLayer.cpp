/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:暂停内容

 API:在场景中添加暂停按钮请加入：
        #include "Layer/StopLayer.h"


        auto stopButton = StopButton::create();
        this->addChild(stopButton);
 ****************************************************************************/
#include "StopLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;




bool StopLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    //显示框架
    auto sprite = Sprite::create(s_P_StopFrame);
    float scaledPre = visibleSize.width * StopFramePre / (sprite->getContentSize().width);
    sprite->setContentSize(Size(sprite->getContentSize().width * scaledPre, sprite->getContentSize().height * scaledPre));
    sprite->setPosition(Vec2(visibleSize / 2) + originSize);
    sprite->setGlobalZOrder(uiOrder);
    _stopLayer->addChild(sprite);

    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;

    {
        Button* resumeButton = Button::create(s_P_ResumeButton, s_P_ResumeButtonSelected);
        float scaledPre = visibleSize.width * ButtonPre / (resumeButton->getContentSize().width);
        resumeButton->setScale(scaledPre);
        resumeButton->setAnchorPoint(Vec2(0.5, 0));

        resumeButton->ignoreContentAdaptWithSize(false);
        resumeButton->setScale9Enabled(true);
        resumeButton->setPressedActionEnabled(false);
        resumeButton->addTouchEventListener(CC_CALLBACK_2(StopLayer::TouchEventResumeButton, this));

        float x = originSize.x + visibleSize.width / 2;
        resumeButton->setPosition(Vec2(x, y));
        resumeButton->setGlobalZOrder(uiOrder);
        _stopLayer->addChild(resumeButton);
    }

    {
        auto seButton = SEButton::create();
        seButton->SetPostionStopLayer(sprite);
        _stopLayer->addChild(seButton);
        auto bgmButton = BGMButton::create();
        bgmButton->SetPostionStopLayer(sprite);
        _stopLayer->addChild(bgmButton);
        auto infoButton = InfoButton::create();
        infoButton->SetPostionStopLayer(sprite);
        _stopLayer->addChild(infoButton);
    }

    {
        Button* homeButton = Button::create(s_P_HomeButton, s_P_HomeButtonSelected);
        float scaledPre = visibleSize.width * ButtonPre / (homeButton->getContentSize().width);
        homeButton->setScale(scaledPre);
        homeButton->setAnchorPoint(Vec2(0.5, 0));

        homeButton->ignoreContentAdaptWithSize(false);
        homeButton->setScale9Enabled(true);
        homeButton->setPressedActionEnabled(false);
        homeButton->addTouchEventListener(CC_CALLBACK_2(StopLayer::TouchEventHomeButton, this));

        float x = originSize.x + visibleSize.width / 2 + homeButton->getContentSize().width * scaledPre + ButtonWidthGapInStop;
        homeButton->setPosition(Vec2(x, y));
        homeButton->setGlobalZOrder(uiOrder);
        _stopLayer->addChild(homeButton);
    }

    
    {
        float x = visibleSize.width / 2 + originSize.x;
        Slider* slider = Slider::create();
        slider->loadBarTexture(s_P_SliderTrack);
        slider->loadSlidBallTextures(s_P_SliderThumb, s_P_SliderThumb, "");
        slider->loadProgressBarTexture(s_P_SliderProgress);
        slider->setMaxPercent(100);
        int per = bgm.getVolume(bgm._audioID) * 100;
        slider->setPercent(per);
        slider->addEventListener(CC_CALLBACK_2(StopLayer::sliderEvent, this));
        slider->setAnchorPoint(Vec2(0.5, 0));
        slider->setPosition(Vec2(x + originSize.x, 30 + originSize.y));
        slider->setVisible(true);
        slider->setGlobalZOrder(uiOrder);
        _stopLayer->addChild(slider);
    }
    _stopLayer->setGlobalZOrder(uiOrder);
    this->addChild(_stopLayer);
    return true;
}


void StopLayer::sliderEvent(Ref* pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float volume = (float)percent / (float)maxPercent;
        bgm.setVolume(bgm._audioID, volume);
    }
}

void StopLayer::TouchEventResumeButton(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        se._audioID = se.play2d(s_M_ButtonSelected);
        Director::getInstance()->resume();
        _eventListener.setEnabled(true);
        this->removeChild(_stopLayer);
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
    }
    break;

    default:
        break;

    }
    return;
}


void StopLayer::TouchEventHomeButton(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        AudioEngine::stopAll();
        se._audioID = se.play2d(s_M_ButtonSelected);
        Director::getInstance()->resume();
        _eventListener.setEnabled(true);
        Director::getInstance()->replaceScene(StartScene::createScene());
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
    }
    break;

    default:
        break;

    }
    return;
}









bool StopButton::init(EventListenerKeyboard& eventListener, Node& node)
{
    if (!Sprite::init())
    {
        return false;
    }

    {
        //设置监听器
        auto listener = EventListenerTouchOneByOne::create();
        listener->setEnabled(true);
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [&,this](Touch* touch, Event* event) {

            auto target = static_cast<Sprite*>(event->getCurrentTarget());

            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode))
            {
                se._audioID = se.play2d(s_M_ButtonSelected);
                auto stopLayer = StopLayer::create(eventListener, node);
                eventListener.setEnabled(false);
                Director::getInstance()->getScheduler()->setTimeScale(0);
                Director::getInstance()->pause();
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
        //设置位置
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto originSize = Director::getInstance()->getVisibleOrigin();

        float scaledPre = visibleSize.width * ButtonPre / (_stopButton->getContentSize().width);
        _stopButton->setContentSize(Size(_stopButton->getContentSize().width * scaledPre, _stopButton->getContentSize().height * scaledPre));

        float x = originSize.x + visibleSize.width - _stopButton->getContentSize().width / 2 - ButtonWidthGap;
        float y = originSize.y + visibleSize.height - _stopButton->getContentSize().height / 2 - ButtonHeightGap;
        _stopButton->setPosition(Vec2(x, y));
        _stopButton->setGlobalZOrder(uiOrder);
        addChild(_stopButton);
    }

    return true;
}
