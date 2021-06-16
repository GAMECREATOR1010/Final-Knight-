/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Potion药水类
 包括：
 · 生命药水 HP 2
 · 魔力药水 MP 80
 · 恢复药水 HP 1 MP 40
 · Buff药水

 接口：
	virtual void Drink(float multi = 1) = 0;	//使用药水

todo
喝药水的效果
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"
#include "Knight.h"
#include "Buff.h"

const int MAX_POTION_SCALE = 2;

const char* HEALTH_SMALL_PATH = "/potions/HealthSmall.png";
const char* HEALTH_LARGE_PATH = "/potions/HealthLarge.png";
const char* MANA_SMALL_PATH = "/potions/ManaSmall.png";
const char* MANA_LARGE_PATH = "/potions/ManaLarge.png";
const char* FULL_SMALL_PATH = "/potions/FullSmall.png";
const char* FULL_LARGE_PATH = "/potions/FullLarge.png";
const char* BUFF_PATH = "/potions/Buff.png";

enum Scale
{
	SMALL = 1, LARGE
};
enum Type
{
	HEAL, MANA, FULL, BUFF
};
//buff种类
enum BuffType
{
	RANDOM,
	HEALTH_MAX_ADD,
	MANA_MAX_ADD,
	SHIELD_MAX_ADD,
	SPEED_ADD,

	//待开发
	BUFF_COUNT	//计数用
};

class Potion : public Item
{
public:
	int GetScale() const;
	int GetType() const;
	virtual void Drink(Knight* drinker,float multi = 1) = 0;	//使用药水
protected:
	bool initWithScale(Scale scale);
private:
	Scale _scale;
	Type _type;
	//以_scale作为效果倍数，SMALL为1，LARGE为2
};

class HealPotion : virtual public Potion
{
public:
	static HealPotion* create(Scale);
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);
};

class ManaPotion : virtual public Potion
{
public:
	static ManaPotion* create(Scale);
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);
};

class FullPotion :public HealPotion, public ManaPotion
{
public:
	static FullPotion* create(Scale);
	virtual void Drink(Knight* drinker,float multi = 0.5);
private:
	virtual bool initWithScale(Scale _scale = SMALL);
};

class BuffPotion : public Potion
{
public:
	static BuffPotion* create(BuffType buffType);
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	BuffType _buffType;
	virtual bool initWithBuffType(BuffType buffType);
};

#endif // !__POTION_H__
