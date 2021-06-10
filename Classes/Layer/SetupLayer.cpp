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
using namespace cocos2d::ui;


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
