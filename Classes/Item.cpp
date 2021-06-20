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

int Item::GetRarity() const
{
	return _rarity;
}

int Item::GetValue() const
{
	return _value;
}

void Item::SetValue(int value)
{
	_value = value;
	return;
}

bool Item::Buy()
{
	auto price = this->GetValue();
	/* 检测是否有足够的钱 */
	if (goldMoney.ChangeBalance(-price))
	{
		/* 该对象作为普通对象交互，这样就不会重复购买了 */
		if (this->getTag() == potionGoodsTag)
		{
			this->setTag(potionChestTag);
		}
		else if (this->getTag() == weaponGoodsTag)
		{
			this->setTag(weaponChestTag);
		}

		CCLOG("Item::Buy: Buy thing");
		return true;
	}
	else
	{
		/* 没有足够的钱 */
		CCLOG("Item::Buy: Can not buy, check money");
		return false;
	}

	return false;
}

bool Item::init()
{
	return true;
}