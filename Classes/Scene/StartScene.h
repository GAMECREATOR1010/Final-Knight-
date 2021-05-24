/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-24)

 Annotation:开始界面UI
 ****************************************************************************/

#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class StartScene :public cocos2d::Scene
{
private:
    int _audioID;

public:
    virtual bool init() override;

    static cocos2d::Scene* createScene();

    void startCallback(Ref* sender);

    CREATE_FUNC(StartScene);
};

#endif  __START_SCENE_H__
