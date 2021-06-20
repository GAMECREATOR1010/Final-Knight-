/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:ÑªÌõÄÚÈÝ

 ****************************************************************************/
#include "BloodLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool BloodLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();

	{
		//ÏÔÊ¾±³¾°Í¼Æ¬
		auto bloodFrame = Sprite::create(s_P_BloodFrame);
		float x = bloodFrame->getContentSize().width / 2 + originSize.x;
		float y = visibleSize.height - bloodFrame->getContentSize().height / 2 + originSize.y;
		bloodFrame->setPosition(x, y);
		bloodFrame->setGlobalZOrder(uiOrder);
		this->addChild(bloodFrame);
	}

	return true;
}