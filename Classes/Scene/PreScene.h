/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:游戏前界面
 ****************************************************************************/

#pragma once

#ifndef __PRE_SCENE_H__
#define __PRE_SCENE_H__

#include "General.h"
#include "Scene/StartScene.h"

class PreScene :public cocos2d::Scene
{

public:
    virtual bool init() override;

    void problemLoading(const char* filename);

    static cocos2d::Scene* createScene();

    void TouchEvent(Ref* pSender, Widget::TouchEventType type);

    CREATE_FUNC(PreScene);
};

#endif  __PRE_SCENE_H__