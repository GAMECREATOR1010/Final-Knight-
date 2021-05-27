/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:ÔÝÍ£ÄÚÈÝ
 ****************************************************************************/
#include "StopLayer.h"

#define StopFramePre     0.6f
#define StopButtonPre    0.075f
#define ButtonWidthGap   40
#define ButtonHeightGap  30

USING_NS_CC;


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

    auto stopItem = MenuItemImage::create(
        s_P_StopButton,
        s_P_StopButtonSelectedBG,
        CC_CALLBACK_1(StopLayer::StopCallBack, this));

    if (stopItem == nullptr ||
        stopItem->getContentSize().width <= 0 ||
        stopItem->getContentSize().height <= 0)
    {
        problemLoading("'s_P_StopButton' and ' s_P_StopButtonSelectedBG'");
    }
    else
    {
        float scaledPre = visibleSize.width * StopButtonPre / (stopItem->getContentSize().width);
        stopItem->setScale(scaledPre);
        float x = originSize.x + visibleSize.width - stopItem->getContentSize().width * scaledPre / 2- ButtonWidthGap;
        float y = originSize.y + visibleSize.height - stopItem->getContentSize().height * scaledPre / 2- ButtonHeightGap;
        stopItem->setPosition(Vec2(x, y));
        addChild(stopItem);
    }

    return true;
}

void StopLayer::StopCallBack(Ref* sendef)
{
   //auto visibleSize = Director::getInstance()->getVisibleSize();
   // auto originSize = Director::getInstance()->getVisibleOrigin();

    //float scaledPre = visibleSize.width * StopFramePre / (setupItem->getContentSize().width);
    //setupItem->setScale(scaledPre);
}
