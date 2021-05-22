/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20b (2021-5-22).

 该部分为Item道具类基类头文件（暂定）
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
USING_NS_CC;

class Item:public Sprite
{
public:
	CREATE_FUNC(Item);

private:
	int _id;
	int _value;
	int _rarity;
	virtual bool init();
};
#endif // !__ITEMS_H__
