/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:游戏前界面
 ****************************************************************************/


#include "PreScene.h"

USING_NS_CC;
using namespace cocos2d::ui;


void PreScene::problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* PreScene::createScene()
{
    return PreScene::create();
}


bool PreScene::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    {
        //显示背景图片
        auto back = Sprite::create(s_P_Start);
        if (back == nullptr)
        {
            problemLoading(s_P_Start);
        }
        else
        {
            float scaledPre = visibleSize.width / (back->getContentSize().width);
            back->setScale(scaledPre);
            back->setPosition(Vec2(visibleSize / 2) + originSize);
            this->addChild(back);
        }
    }


    //显示必读界面
    auto frame = Sprite::create(s_P_InfoFrameStart);
    if (frame == nullptr)
    {
        problemLoading(s_P_InfoFrameStart);
    }
    else
    {
        frame->setPosition(Vec2(visibleSize / 2) + originSize);
        this->addChild(frame);
    }


    float y = originSize.y + visibleSize.height / 2 - frame->getContentSize().height / 2 + ButtonHeightGapInStop;

    {
        //显示关闭按钮
        Button* closeButton = Button::create(s_P_CloseButton);
        closeButton->setAnchorPoint(Vec2(0.5, 0));

        closeButton->ignoreContentAdaptWithSize(false);
        closeButton->setScale9Enabled(true);
        closeButton->setPressedActionEnabled(false);
        closeButton->addTouchEventListener(CC_CALLBACK_2(PreScene::TouchEvent, this));

        float x = originSize.x + visibleSize.width / 2;
        closeButton->setPosition(Vec2(x, y));
        this->addChild(closeButton);
    }


    return true;
}


void PreScene::TouchEvent(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        se._audioID = se.play2d(s_M_ButtonSelected);
        Director::getInstance()->replaceScene(StartScene::create());
    }
    break;

    default:
        break;

    }
    return;
}

