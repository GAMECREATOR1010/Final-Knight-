/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为宝箱类
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

const char* WHITE_CHEST_PATH = "/chests/WhiteChest.png";
const char* BLUE_CHEST_PATH = "/chests/BlueChest.png";
const char* BROWN_CHEST_PATH = "/chests/BrownChest.png";

enum ChestType
{
	WHITE_CHEST,
	BLUE_CHEST,
	BROWNCHEST,

	CHEST_COUNT
};

class Chest : public Sprite
{
public:
	virtual Item* open() = 0;
protected:
	virtual bool init();
private:
	static constexpr double _physicalRange = 80.0;
};

class WhiteChest : public Chest
{
public:
	static WhiteChest* create();
	virtual Item* open();
private:
	virtual bool init();
};

#endif // !__CHEST_H__
