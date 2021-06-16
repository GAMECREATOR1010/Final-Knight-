/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ�̵�
 ****************************************************************************/

#include "Shop.h"

#pragma region Goods

bool Goods::Buy()
{
	/* ����Ƿ����㹻��Ǯ */
	if (GoldMoney::ChangeBalance(-_price))
	{
		/* ɾ���ö�����ͼ������bool�жϣ� */
		/* �ö�����Ϊ��ͨ���󽻻��������Ͳ����ظ������� */
		if (typeid(this) == typeid(Potion*))
		{
			this->setTag(potionChestTag);
		}
		else if (typeid(this) == typeid(Weapon*))
		{
			this->setTag(weaponChestTag);
		}
		//�ο�ǽ����ʧ�Ĵ���
		return true;
	}
	else
	{
		/* û���㹻��Ǯ */
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
/// �����̵���Ȼ����Ҫ����GetGoodses�����������л��ﲢ��ӵ�����
/// </summary>
/// <returns></returns>
bool Shop::InitGoods(int curLevel)
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//����ҩ
	{
		if (SetPotion(HEAL,curLevel) && SetPotion(MANA, curLevel) && SetWeapon(curLevel))
		{
			return true;
		}
	}
	else if (ran == 1)	//һ��ҩ
	{
		if (SetPotion(FULL, curLevel) && SetWeapon(curLevel) && SetWeapon(curLevel))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �����Ʒ��Goods�ڵ�Item*ָ��Ϊ��Ʒ����ָ��
/// </summary>
/// <returns></returns>
std::vector<Goods>& Shop::GetGoodses()
{
	return _goodses;
}

/// <summary>
/// ���ҩˮ����ͬʱ���ü۸�
/// </summary>
/// <param name="type">ҩˮ����</param>
/// <returns></returns>
bool Shop::SetPotion(Type type, int curLevel = 1)
{
	Potion* potion;
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//Сҩ
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
	else if (ran == 1)	//��ҩ
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

	/* ��ҩ��ӵ������� */
	if (_goodses.size() < MAX_GOODS)
	{
		_goodses.push_back(gd);
		return true;
	}

	return false;
}

/// <summary>
/// �����������ͬʱ���ü۸�
/// </summary>
/// <returns></returns>
bool Shop::SetWeapon(int curLevel = 1)
{
	Goods gd;
	auto wp = static_cast <Item*> (RandomWeaponCreate());

	gd.SetGoods(wp);
	gd.SetPrice(wp->GetRarity() * curLevel);

	/* ��ҩ��ӵ������� */
	if (_goodses.size() < MAX_GOODS)
	{
		_goodses.push_back(gd);
		return true;
	}

	return false;
}

/// <summary>
/// ��ʼ��һ��NPC����
/// </summary>
/// <returns>ָ�����˵�ָ��</returns>
NPC* Shop::SetShopKeeper()
{
	auto skp = NPC::create(SHOPKEEPER);
	return skp;
}

#pragma endregion