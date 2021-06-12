/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Item道具类基类（暂定）
 ****************************************************************************/

#include "Item.h"

 /// <summary>
 /// 随机返回一个稀有度（不创建对象）
 /// </summary>
 /// <returns>enum 物品稀有度概率</returns>
ItemProbability RandomItemRarity()
{
	if (rand() % 100 <= LEGENDARY)
	{
		return LEGENDARY;
	}
	else if (rand() % 100 <= EPIC)
	{
		return EPIC;
	}
	else if (rand() % 100 <= VERYRARE)
	{
		return VERYRARE;
	}
	else if (rand() % 100 <= RARE)
	{
		return RARE;
	}
	else if (rand() % 100 <= UNCOMMON)
	{
		return UNCOMMON;
	}
	else if (rand() % 100 <= COMMON)
	{
		return COMMON;
	}
	else
	{
		throw("Item rarity random failed , in func randomItemRarity");
	}
}

int Item::GetRarity()
{
	return _rarity;
}

bool Item::init()
{
	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}