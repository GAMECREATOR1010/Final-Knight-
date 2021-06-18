/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:交互与提示

 API:

auto cache = AnimationCache::getInstance();
 cache->addAnimationsWithFile("animations/animations-2.plist");
 auto animation2 = cache->getAnimation("dance_1");

 auto action2 = Animate::create(animation2);
 
 ****************************************************************************/

#include "ContactLayer.h"


USING_NS_CC;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



bool LackOfCoinLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    {
        auto sprite = Sprite::create(s_P_LackOfCoin);

        if (sprite == nullptr)
        {
            problemLoading("s_P_LackOfCoin");
        }
        else
        {
            Vec2& knightPosition = Vec2(0, 0);
            Size& knightSize = Size(0, 0);
            //knightPosition = myKnightForever->getPosition();
           // knightSize = myKnightForever->getContentSize();
            sprite->setPosition(visibleSize / 2);
            sprite->runAction(
                    Sequence::create(
                        FadeTo::create(2, 0),
                        nullptr));
            sprite->setGlobalZOrder(uiOrder);
            this->addChild(sprite);
        }
    }

    return true;
}



bool SuccessBugLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    {
        auto sprite = Sprite::create(s_P_SuccessBug);

        if (sprite == nullptr)
        {
            problemLoading("s_P_SuccessBug");
        }
        else
        {
            Vec2& knightPosition = Vec2(0, 0);
            Size& knightSize = Size(0, 0);
            //knightPosition = myKnightForever->getPosition();
           // knightSize = myKnightForever->getContentSize();
            sprite->setPosition(visibleSize / 2);
            sprite->runAction(
                Sequence::create(
                    FadeTo::create(2, 0),
                    nullptr));
            sprite->setGlobalZOrder(uiOrder);
            this->addChild(sprite);
        }
    }
    return true;
}