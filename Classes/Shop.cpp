/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为商店
 ****************************************************************************/

#include "Shop.h"

#pragma region Goods
bool Goods::Buy()
{
	/* 检测是否有足够的钱 */
	if (GoldMoney::ChangeBalance(-_price))
	{
		/* 替换武器 */

		/* 删除该对象 */
		//参考墙体消失的代码
	}
	else
	{
		/* 提示没有足够的钱 */
	}

	return false;
}

void Goods::SetGoods(Item* item)
{
	_pGoods = item;
	return;
}

void Goods::SetPrice(int price)
{
	_price = price;
	return;
}
Item* Goods::GetGoods() const
{
	return _pGoods;
}
#pragma endregion

#pragma region Shop

/// <summary>
/// 设置商店货物，然后需要调用GetGoodses语句来获得所有货物并添加到层内
/// </summary>
/// <returns></returns>
bool Shop::InitGoods()
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//两种药
	{
		if (SetPotion(HEAL) && SetPotion(MANA) && SetWeapon())
		{
			return true;
		}
	}
	else if (ran == 1)	//一种药
	{
		if (SetPotion(FULL) && SetWeapon() && SetWeapon())
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 获得商品，Goods内的Item*指针为商品对象指针
/// </summary>
/// <returns></returns>
std::vector<Goods>& Shop::GetGoodses()
{
	return _goodses;
}

/// <summary>
/// 添加药水，并同时设置价格
/// </summary>
/// <param name="type">药水类型</param>
/// <returns></returns>
bool Shop::SetPotion(Type type)
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
	Goods gd;
	gd.SetGoods(static_cast <Item*> (potion));
	gd.SetPrice(potion->GetScale() * THISLEVEL);

	/* 将药添加到货物内 */
	if (_goodses.size() < MAX_GOODS)
	{
		_goodses.push_back(gd);
		return true;
	}

	return false;
}

/// <summary>
/// 添加武器，并同时设置价格
/// </summary>
/// <returns></returns>
bool Shop::SetWeapon()
{
	Goods gd;
	auto wp = static_cast <Item*> (RandomWeaponCreate());

	gd.SetGoods(wp);
	gd.SetPrice(wp->GetRarity() * THISLEVEL);

	/* 将药添加到货物内 */
	if (_goodses.size() < MAX_GOODS)
	{
		_goodses.push_back(gd);
		return true;
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
	return skp;
}

#pragma endregion