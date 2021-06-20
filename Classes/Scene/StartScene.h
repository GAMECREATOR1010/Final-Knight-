/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:开始界面UI
 ****************************************************************************/

#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "source.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Const.h"
#include "Gaming.h"
#include "SafeScene.h"
#include "Layer/TwoUseButtonsLayer.h"

class StartScene :public cocos2d::Scene
{
public:
	virtual bool init() override;

	void problemLoading(const char* filename);

	static cocos2d::Scene* createScene();

	void StartCallback(Ref* sender);

	void sliderEvent(Ref* pSender, Slider::EventType type);

	CREATE_FUNC(StartScene);
};

#endif  __START_SCENE_H__
