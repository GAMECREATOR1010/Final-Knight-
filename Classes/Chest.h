/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
 WhiteChest
	static WhiteChest* create();	//生成一个宝箱
	virtual Item* open();			//打开宝箱

 该部分为宝箱类

  todo list:
 打开宝箱
 ****************************************************************************/
#pragma once

#ifndef __CHEST_H__
#define __CHEST_H__

#include "cocos2d.h"
#include "Const.h"
#include "Money.h"
#include "Potion.h"
#include "Weapon.h"

USING_NS_CC;

static const char* WHITE_CHEST_PATH = "/chests/WhiteChestInit.png";
static const char* BLUE_CHEST_PATH = "/chests/BlueChest.png";
static const char* BROWN_CHEST_PATH = "/chests/BrownChest.png";

enum ChestType
{
	WHITE_CHEST,
	BLUE_CHEST,
	BROWN_CHEST,

	CHEST_COUNT
};

class Chest : public Sprite
{
public:
	virtual Item* open(Knight* activer) = 0;
protected:
	virtual bool init();
	bool _isOpened = false;
private:
	const double _physicalRange = 80.0;
};

/* 白色宝箱，关卡结束、宝箱房间 */
class WhiteChest : public Chest
{
public:
	static WhiteChest* create();	//生成一个宝箱
	virtual Item* open(Knight* activer);//打开宝箱
private:
	virtual bool init();
};

#endif // !__CHEST_H__
