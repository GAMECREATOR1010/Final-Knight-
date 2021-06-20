/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:°²È«³¡¾°
 ****************************************************************************/
#pragma once
#ifndef __SAFE_SCENE_H__
#define __SAFE_SCENE_H__

#include "Global/source.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Global/Const.h"
#include "RoomAndMap/Gaming.h"

class SafeScene :public cocos2d::Scene
{
public:
	virtual bool init() override;

	void problemLoading(const char* filename);

	static cocos2d::Scene* createScene();

	void TouchEventEnemyButton(Ref* pSender, Widget::TouchEventType type);
	void TouchEventKnightButton(Ref* pSender, Widget::TouchEventType type);
	void TouchEventWeaponButton(Ref* pSender, Widget::TouchEventType type);

	CREATE_FUNC(SafeScene);
};

class KnightScene :public cocos2d::Scene
{
public:
	virtual bool init() override;

	CREATE_FUNC(KnightScene);

	void StartGame0(Ref* sender);
	void StartGame1(Ref* sender);
	void StartGame2(Ref* sender);
	void StartGame3(Ref* sender);
	void StartGame4(Ref* sender);
	void StartGame5(Ref* sender);
	void StartGame6(Ref* sender);
	void StartGame7(Ref* sender);

	void TouchEventOutButton(Ref* pSender, Widget::TouchEventType type);
};

class EnemyScene :public cocos2d::Scene
{
public:
	virtual bool init() override;

	CREATE_FUNC(EnemyScene);

	void TouchEventOutButton(Ref* pSender, Widget::TouchEventType type);
};

class WeaponScene :public cocos2d::Scene
{
protected:
	Sprite* _sprite;
public:
	virtual bool init() override;
	CREATE_FUNC(WeaponScene);

	void TouchEventOutButton(Ref* pSender, Widget::TouchEventType type);
};
#endif  __SAFE_SCENE_H__