/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-23)

 该部分为Potion药水类
 包括：
 · 生命药水
 · 魔力药水
 · Buff药水(需要开发）
 调用接口：
 · 英雄HP、MP相关（需要接口）
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"
class Potion : public Item
{
public:
protected:
	enum Scale
	{
		SMALL, LARGE
	}_scale;
private:
	//以_scale作为效果倍数，SMALL为1，LARGE为2
	virtual bool init();
};

class HealPotion : public Potion
{
public:
private:
	int _healValue;
	virtual bool init();
	void Drink();
};

class ManaPotion : public Potion
{
public:
private:
	int _healValue;
	virtual bool init();
	void Drink();
};

class BuffPotion : public Potion
{
public:
private:
	//buff种类
	enum _buffType
	{
		HEALTH_MAX_ADD,
		MANA_MAX_ADD,
		SHIELD_MAX_ADD,
		//待开发

	};
	virtual bool init();
	void Drink();
};



#endif // !__POTION_H__

