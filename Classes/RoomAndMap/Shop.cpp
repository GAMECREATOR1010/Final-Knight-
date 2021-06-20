/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为商店
 ****************************************************************************/

#include "RoomAndMap/Shop.h"

#pragma region Goods

void Goods::SetGoods(Item* item)
{
	_pGoods = item;
	if (item->getName() == "Potion")
	{
		item->setTag(potionGoodsTag);
	}
	else if (item->getName() == "Weapon")
	{
		item->setTag(weaponGoodsTag);
	}
	else
	{
		CCLOG("Goods::SetGoods set item failed");
	}
	return;
}

void Goods::SetPrice(int price)
{
	_price = price;
	return;
}
Item* Goods::GetGoods()
{
	return _pGoods;
}
#pragma endregion

#pragma region Shop

/// <summary>
/// 设置商店货物，然后需要调用GetGoodses语句来获得所有货物并添加到层内
/// </summary>
/// <returns></returns>
bool Shop::InitGoods(int curLevel)
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//两种药
	{
		if (SetPotion(HEAL, curLevel) && SetPotion(MANA, curLevel) && SetWeapon(curLevel))
		{
			return true;
		}
	}
	else if (ran == 1)	//一种药
	{
		if (SetPotion(FULL, curLevel) && SetWeapon(curLevel) && SetWeapon(curLevel))
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
bool Shop::SetPotion(Type type, int curLevel)
{
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
				potion = FullPotion::create(SMALL);
				break;
			case BUFF:
				potion = BuffPotion::create(RANDOM);
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
				potion = FullPotion::create(LARGE);
				break;
			case BUFF:
				potion = BuffPotion::create(RANDOM);
				break;
			default:
				return false;
				break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (goodses[i].GetGoods() == nullptr)
		{
			potion->setName("Potion");
			goodses[i].SetGoods(potion);
			goodses[i].SetPrice(potion->GetValue() * curLevel);

			return true;
		}
	}

	return false;
}

/// <summary>
/// 添加武器，并同时设置价格
/// </summary>
/// <returns></returns>
bool Shop::SetWeapon(int curLevel)
{
	for (int i = 0; i < 3; i++)
	{
		if (goodses[i].GetGoods() == nullptr)
		{
			auto wp = static_cast <Item*> (RandomWeaponCreate());
			wp->setName("Weapon");
			goodses[i].SetGoods(wp);
			goodses[i].SetPrice(wp->GetValue() * curLevel);

			return true;
		}
	}

	return false;
}

/// <summary>
/// 初始化一个NPC对象
/// </summary>
/// <returns>指向商人的指针</returns>
NPC* Shop::SetShopKeeper()
{
	auto skp = NPC::create(SHOPKEEPER);
	skp->setGlobalZOrder(shadeOrder);
	return skp;
}

/// <summary>
/// 创建一个货架，返回货架的指针
/// </summary>
/// <returns></returns>
Sprite* Shop::shelfCreate()
{
	auto shelf = Sprite::create(SHELF_PATH);
	shelf->setScale(0.5);
	shelf->setGlobalZOrder(shadeOrder);

	return shelf;
}

#pragma endregion