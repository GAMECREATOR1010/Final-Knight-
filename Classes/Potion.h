/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 该部分为Potion药水类
 包括：
 · 生命药水 HP 2
 · 魔力药水 MP 80
 · 恢复药水 HP 1 MP 40
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
	int GetScale();
private:
	enum Scale
	{
		SMALL, LARGE
	}_scale;
	//以_scale作为效果倍数，SMALL为1，LARGE为2
	virtual bool init();
};

class HealPotion : public Potion
{
public:
	void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init();

};

class ManaPotion : public Potion
{
public:
	void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init();

};

class FullPotion :virtual public HealPotion, virtual public ManaPotion
{
public:
	void Drink();
private:
	virtual bool init();

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

