/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:游戏前界面
 ****************************************************************************/

#pragma once

#ifndef __PRE_SCENE_H__
#define __PRE_SCENE_H__

#include "BGM.h"
#include "StartScene.h"
#include "source.h" 
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PreScene :public cocos2d::Scene
{

public:
    virtual bool init() override;

    static cocos2d::Scene* createScene();

    void touchEvent(Ref* pSender, Widget::TouchEventType type);

    CREATE_FUNC(PreScene);
};

#endif  __PRE_SCENE_H__