/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:ÉèÖÃÄÚÈÝ
 ****************************************************************************/
#include "SetupLayer.h"


#define ButtonPre    0.075f
#define ButtonWidthGap   40
#define ButtonHeightGap  30

USING_NS_CC;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SetupLayerStart::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    auto setupLayerStartItem = MenuItemImage::create(
        s_P_SetupButton,
        s_P_SetupButtonSelectedBG,
        CC_CALLBACK_1(SetupLayerStart::StopCallBack, this));

    if (setupLayerStartItem == nullptr ||
        setupLayerStartItem->getContentSize().width <= 0 ||
        setupLayerStartItem->getContentSize().height <= 0)
    {
        problemLoading("'s_P_SetupButton' and 's_P_SetupButtonSelectedBG'");
    }
    else
    {
        float scaledPre = visibleSize.width * ButtonPre / (setupLayerStartItem->getContentSize().width);
        setupLayerStartItem->setScale(scaledPre);
        float x = originSize.x + setupLayerStartItem->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
        float y = originSize.y + setupLayerStartItem->getContentSize().height * scaledPre / 2 + ButtonHeightGap;
        setupLayerStartItem->setPosition(Vec2(x, y));
        addChild(setupLayerStartItem);
    }

    return true;
}


bool SetupLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    return true;
}


bool BGMLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    return true;
}


void SetupLayerStart::StopCallBack(Ref* sendef)
{
    BGMLayer::create();
}

void  BGMLayer::StopCallBackBGM(Ref* sendef)
{
}

void  BGMLayer::StopCallBackSE(Ref* sendef)
{
}
