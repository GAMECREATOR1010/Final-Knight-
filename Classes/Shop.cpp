/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)
 ****************************************************************************/

#include "Shop.h"
#include <ctime>

/// <summary>
/// 设置商店货物
/// </summary>
/// <returns></returns>
bool Shop::SetGoods()
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//两种药
	{
		if (SetPotion(HEAL) && SetPotion(MANA) && SetWeapon( some type ))
		{
			return true;
		}
	}
	else if (ran == 1)	//一种药
	{
		if (SetPotion(FULL) && SetWeapon(some type) && SetWeapon(some type))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 添加药水，并同时设置价格
/// </summary>
/// <param name="type">药水类型</param>
/// <returns></returns>
bool Shop::SetPotion(Type type)
{
	Goods goods = { 0 };
	Potion* potion;
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//小药
	{
		switch (type)
		{
			case HEAL:
				potion = HealPotion::create(SMALL);
				break;
			case MANA:
				potion = ManaPotion::create(SMALL);
				break;
			case FULL:
				potion = FullPotion::Potion::create(SMALL);
				break;
			case BUFF:
				potion = BuffPotion::create(SMALL);
				break;
			default:
				return false;
				break;
		}
	}
	else if (ran == 1)	//大药
	{
		switch (type)
		{
			case HEAL:
				potion = HealPotion::create(LARGE);
				break;
			case MANA:
				potion = ManaPotion::create(LARGE);
				break;
			case FULL:
				potion = FullPotion::Potion::create(LARGE);
				break;
			case BUFF:
				potion = BuffPotion::create(LARGE);
				break;
			default:
				return false;
				break;
		}
	}
	goods.item = potion;
	goods.price = potion->GetValue() * THISLEVEL;

	/* 将药添加到货物内 */
	if (_goodses.size() <MAX_GOODS)
	{
		_goodses.pushBack(goods);
		return true;
	}

	return false;
}

bool Shop::SetWeapon()
{
	/* 类似 */
	return false;
}

