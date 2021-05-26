/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-24)
 
 Annotation:开始界面UI
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Layer/StopLayer.h"
#include "StartScene.h"
#include "source.h" 

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    {
        //背景音乐
        bg._audioIDBGM = bg.play2dBGM(s_M_StartBGM);
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    {
        //显示背景图片
        auto sprite = Sprite::create(s_P_Start);
        if (sprite == nullptr)
        {
            problemLoading(s_P_Start);
        }
        else
        {
            float scaledPre = visibleSize.width  / (sprite->getContentSize().width);
            sprite->setScale(scaledPre);
            sprite->setPosition(Vec2(visibleSize / 2) + originSize);
            this->addChild(sprite, 0);
        }
    }

    {
        //显示PRESS TO START,设置为闪烁
        MenuItemFont::setFontName("fonts/Pixeboy.ttf");
        auto startItem = MenuItemFont::create("PRESS TO START",
            CC_CALLBACK_1(StartScene::startCallback, this));
        startItem->setFontSizeObj(100);

        auto actionFade = FadeIn::create(1.0f);
        auto actionFadeBack = actionFade->reverse();
        auto seq = Sequence::create(actionFade, actionFadeBack, nullptr);
        startItem->setOpacity(0);
        startItem->runAction(RepeatForever::create(seq));

        auto menu = Menu::create(startItem, nullptr);

        addChild(menu);
        menu->setPosition(Vec2(visibleSize.width / 2 + originSize.x, visibleSize.height / 4 + originSize.y));
    }

    return true;
}

void StartScene::startCallback(Ref* sender)
{
    //音效
    bg._audioIDSE = bg.play2dSE(s_M_ButtonSelected);
    //回调函数，设置关掉音乐，打开游戏关卡
    bg.stopBGM();
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}
