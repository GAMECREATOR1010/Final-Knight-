/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:ÉèÖÃÄÚÈÝ
 ****************************************************************************/
#include "SetupLayer.h"
#include "source.h" 


USING_NS_CC;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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

void SetupLayer::StopCallBack(Ref* sendef)
{
}

void SetupLayer::StopCallBackBGM(Ref* sendef)
{
}

void SetupLayer::StopCallBackSE(Ref* sendef)
{
}

