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
		/* 删除该对象，贴图？设置bool判断？ */
		/* 该对象作为普通对象交互，这样就不会重复购买了 */
		if (typeid(this) == typeid(Potion*))
		{
			this->setTag(potionChestTag);
		}
		else if (typeid(this) == typeid(Weapon*))
		{
			this->setTag(weaponChestTag);
		}
		//参考墙体消失的代码
		return true;
	}
	else
	{
		/* 没有足够的钱 */
		return false;
	}

	return false;
}

void Goods::SetGoods(Item* item)
{
	_pGoods = item;
	if (typeid(item) == typeid(Potion*))
	{
		this->setTag(potionGoodsTag);
	}
	else if (typeid(item) == typeid(Weapon*))
	{
		this->setTag(weaponGoodsTag);
	}
	else
	{
		throw("Goods::SetGoods set item failed");
	}
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
bool Shop::InitGoods(int curLevel)
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//两种药
	{
		if (SetPotion(HEAL,curLevel) && SetPotion(MANA, curLevel) && SetWeapon(curLevel))
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
bool Shop::SetPotion(Type type, int curLevel = 1)
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
	gd.SetPrice(potion->GetScale() * curLevel);

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
bool Shop::SetWeapon(int curLevel = 1)
{
	Goods gd;
	auto wp = static_cast <Item*> (RandomWeaponCreate());

	gd.SetGoods(wp);
	gd.SetPrice(wp->GetRarity() * curLevel);

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