/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ�̵�
 ****************************************************************************/

#include "Shop.h"
#include <ctime>

/// <summary>
/// �����̵����
/// </summary>
/// <returns></returns>
bool Shop::SetGoods()
{
	srand(time(0));
	int ran = rand() % MAX_POTION_SCALE;
	if (ran == 0)	//����ҩ
	{
		if (SetPotion(HEAL) && SetPotion(MANA) && SetWeapon( some type ))
		{
			return true;
		}
	}
	else if (ran == 1)	//һ��ҩ
	{
		if (SetPotion(FULL) && SetWeapon(some type) && SetWeapon(some type))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// ���ҩˮ����ͬʱ���ü۸�
/// </summary>
/// <param name="type">ҩˮ����</param>
/// <returns></returns>
bool Shop::SetPotion(Type type)
{
	Goods goods = { 0 };
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
	goods.item = potion;
	goods.price = potion->GetScale() * THISLEVEL;

	/* ��ҩ��ӵ������� */
	if (_goodses.size() <MAX_GOODS)
	{
		_goodses.push_back(goods);
		return true;
	}

	return false;
}

bool Shop::SetWeapon()
{
	/* ���� */
	return false;
}

