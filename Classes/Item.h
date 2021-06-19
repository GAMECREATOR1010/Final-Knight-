/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
	int GetRarity() const;	//获取品质

 该部分为Item道具类基类

 todo
 成员变量初始化
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

//各品质物品出现概率
//概率计算应当按照从稀有到普通依次计算
//每个概率并非为出现的概率，而是在单次计算中生成的概率
//也就是说，uncommon的将会计算5次
enum ItemProbability
{
	LEGENDARY = -1,		//无法通过开宝箱/商店获得
	EPIC      = 10,
	VERYRARE  = 20,
	RARE      = 30,
	UNCOMMON  = 50,
	COMMON    = 100		//必定获得
};

ItemProbability RandomItemRarity();

class Item :public Sprite
{
public:
	CREATE_FUNC(Item);
	int GetRarity() const;	//获取品质
	int GetNowValue(int curLevel = 1);
protected:
	virtual bool init();
	static constexpr double _physicalRange = 80.0;
private:
	int _id;
	int _value;
	int _rarity;
};
#endif // !__ITEMS_H__
