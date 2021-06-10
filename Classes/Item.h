/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Item道具类基类头文件（暂定）
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

//#pragma region Item_Probability
///* 
//   此处为各品质物品出现概率 
//   概率计算应当按照从稀有到普通依次计算
//   每个概率并非为出现的概率，而是在单次计算中生成的概率
//   也就是说，uncommon的将会计算5次
//*/
//const int COMMON_PROBABILITY = 100;		//必定获得
//const int UNCOMMON_PROBABILITY = 50;
//const int RARE_PROBABILITY = 30;
//const int VERYRARE_PROBABILITY = 20;
//const int EPIC_PROBABILITY = 10;
//const int LEGENDARY_PROBABILITY = 0;	//无法通过开宝箱/商店获得
//#pragma endregion

//各品质物品出现概率
//概率计算应当按照从稀有到普通依次计算
//每个概率并非为出现的概率，而是在单次计算中生成的概率
//也就是说，uncommon的将会计算5次
enum ItemProbability
{
	LEGENDARY = 0,		//无法通过开宝箱/商店获得
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
	int GetRarity();
protected:
	virtual bool init();
private:
	int _id;
	int _value;
	int _rarity;
	static constexpr double _physicalRange = 80.0;
};
#endif // !__ITEMS_H__
