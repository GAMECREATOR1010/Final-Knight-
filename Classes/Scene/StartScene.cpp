/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)
 
 Annotation:��ʼ����UI
 ****************************************************************************/


#include "StartScene.h"
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
        //��������
        bgm._audioID = bgm.play2d(s_M_StartBGM);
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    {
        //��ʾ����ͼƬ
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
        //��ʾPRESS TO START,����Ϊ��˸
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

    {   
        //��Ч��BGM���ð�ť
        auto BGMButton = BGMLayer::create();
        auto SEButton = SELayer::create();
        this->addChild(BGMButton);
        this->addChild(SEButton);
    }

    return true;
}

void StartScene::startCallback(Ref* sender)
{
    //�ص����������ùص����֣�����Ϸ�ؿ�
    bgm.stopAll();
    //��Ч
    se._audioID = se.play2d(s_M_ButtonSelected);
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

