/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/
#pragma once

#include "Global/General.h"
#include "Global/Money.h"
#include "Layer/BloodLayer.h"
#include "Layer/ContactLayer.h"
#include "Layer/StopLayer.h"

class MainUILayer : public cocos2d::Layer
{
public:

	virtual bool init();

	static MainUILayer* create()
	{
		auto ret = new (std::nothrow) MainUILayer();
		if (ret && ret->init())
		{
			ret->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(ret);
		}
		return ret;
	}
	void AddStuff(EventListenerKeyboard& eventListener, Node& node, Knight& kinght);
};
