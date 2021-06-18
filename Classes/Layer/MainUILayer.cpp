/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/


#include "MainUILayer.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainUILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    bgm._audioID = bgm.play2d(s_M_StartBGM);

    {
        auto stopButton = StopButton::create();
        stopButton->setGlobalZOrder(uiOrder);
        this->addChild(stopButton);
    }
    {
        auto bloodLayer = BloodLayer::create();
        bloodLayer->setGlobalZOrder(uiOrder);
        this->addChild(bloodLayer);
    }
    {
        auto coinFrame = Sprite::create(s_P_CoinFrame);
        float x = visibleSize.width - coinFrame->getContentSize().width * 2 + originSize.x;
        float y = visibleSize.height - coinFrame->getContentSize().height + originSize.y;
        coinFrame->setPosition(x, y);
        coinFrame->setGlobalZOrder(uiOrder);
        this->addChild(coinFrame);
    }
    return true;
}