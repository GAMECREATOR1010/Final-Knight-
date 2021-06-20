/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:安全场景
 ****************************************************************************/

#include "SafeScene.h"
USING_NS_CC;

Scene* SafeScene::createScene()
{
    return SafeScene::create();
}

void SafeScene::problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SafeScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    {
        //显示背景图片
        auto back = Sprite::create(s_P_BackGround);
        if (back == nullptr)
        {
            problemLoading(s_P_BackGround);
        }
        else
        {
            float scaledPre = visibleSize.width / (back->getContentSize().width);
            back->setScale(scaledPre);
            back->setPosition(Vec2(visibleSize / 2) + originSize);
            this->addChild(back);
        }
    }

    {
        auto enemyFrame = Sprite::create(s_P_EnemyFrame);
        auto knightFrame = Sprite::create(s_P_KnightFrame);
        auto weaponFrame = Sprite::create(s_P_WeaponFrame);
        enemyFrame->setAnchorPoint(Vec2(0, 0.5));
        knightFrame->setAnchorPoint(Vec2(0, 0.5));
        weaponFrame->setAnchorPoint(Vec2(0, 0.5));
        float gap = (visibleSize.width - enemyFrame->getContentSize().width * 3) / 4;
        float x = gap + originSize.x;
        float y = visibleSize.height * 3 / 5 + originSize.y;
        enemyFrame->setPosition(x, y);
        knightFrame->setPosition(x+ enemyFrame->getContentSize().width+ gap, y );
        weaponFrame->setPosition(x + enemyFrame->getContentSize().width * 2 + gap * 2, y);
        addChild(enemyFrame);
        addChild(knightFrame);
        addChild(weaponFrame);
    }

    return true;
}