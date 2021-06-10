/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:开始界面UI
 ****************************************************************************/

#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "BGM.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "HelloWorldScene.h"
#include "Layer/BGMButtonsLayer.h"
#include "source.h" 

class StartScene :public cocos2d::Scene
{
private:
    BGM bgm;

public:
    virtual bool init() override;

    static cocos2d::Scene* createScene();

    void startCallback(Ref* sender);

    CREATE_FUNC(StartScene);
};

#endif  __START_SCENE_H__
