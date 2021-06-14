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
		/* �滻���� */

		/* ɾ���ö��� */
		//�ο�ǽ����ʧ�Ĵ���
	}
	else
	{
		/* ��ʾû���㹻��Ǯ */
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
/// �����̵���Ȼ����Ҫ����GetGoodses�����������л��ﲢ��ӵ�����
/// </summary>
/// <returns></returns>
bool Shop::InitGoods()
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//����ҩ
	{
		if (SetPotion(HEAL) && SetPotion(MANA) && SetWeapon())
		{
			return true;
		}
	}
	else if (ran == 1)	//һ��ҩ
	{
		if (SetPotion(FULL) && SetWeapon() && SetWeapon())
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
bool Shop::SetPotion(Type type)
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
	gd.SetPrice(potion->GetScale() * THISLEVEL);

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
bool Shop::SetWeapon()
{
	Goods gd;
	auto wp = static_cast <Item*> (RandomWeaponCreate());

	gd.SetGoods(wp);
	gd.SetPrice(wp->GetRarity() * THISLEVEL);

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