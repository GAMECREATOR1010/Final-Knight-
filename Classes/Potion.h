/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 此部分尚未完成，请勿使用

 该部分为Potion药水类
 包括：
 · 生命药水 HP 2
 · 魔力药水 MP 80
 · 恢复药水 HP 1 MP 40
 · Buff药水(需要开发）
 调用接口：
 · 英雄HP、MP相关（需要接口/将Drink设为友元函数）
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

const int MAX_POTION_SCALE = 2;
enum Scale
{
	SMALL=1, LARGE
};
enum Type
{
	HEAL, MANA, FULL, BUFF
};

class Potion : public Item
{
public:
	CREATE_FUNC(Potion);
	static Potion* create(Scale);
	int GetScale();
	int GetType();
	virtual void Drink();
private:
	Scale _scale;
	Type _type;
	//以_scale作为效果倍数，SMALL为1，LARGE为2
	virtual bool init(Scale _scale=SMALL);
};

class HealPotion : public Potion
{
public:
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init(Scale _scale = SMALL);

};

class ManaPotion : public Potion
{
public:
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init(Scale _scale = SMALL);

};

class FullPotion :virtual public HealPotion, virtual public ManaPotion
{
public:
	virtual void Drink();
private:
	virtual bool init(Scale _scale = SMALL);

};

class BuffPotion : public Potion
{
public:
	virtual void Drink();
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
};


#endif // !__POTION_H__

