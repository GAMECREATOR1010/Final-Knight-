/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:°²È«³¡¾°
 ****************************************************************************/
#pragma once
#ifndef __SAFE_SCENE_H__
#define __SAFE_SCENE_H__

#include "source.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Const.h"
#include "Gaming.h"


class SafeScene :public cocos2d::Scene
{

public:
    virtual bool init() override;

    void problemLoading(const char* filename);

    static cocos2d::Scene* createScene();

    void startCallback(Ref* sender);

    CREATE_FUNC(SafeScene);
};



#endif  __SAFE_SCENE_H__