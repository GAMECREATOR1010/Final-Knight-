/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ�̵�
 ****************************************************************************/

#include "Shop.h"

#pragma region Goods

bool Goods::Buy()
{
	/* ����Ƿ����㹻��Ǯ */
	if (goldMoney.ChangeBalance(-_price))
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
	if (item->getName()=="Potion")
	{
		this->setTag(potionGoodsTag);
	}
	else if (item->getName()=="Weapon")
	{
		this->setTag(weaponGoodsTag);
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
/// ���ҩˮ����ͬʱ���ü۸�
/// </summary>
/// <param name="type">ҩˮ����</param>
/// <returns></returns>
bool Shop::SetPotion(Type type, int curLevel)
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

	for (int i = 0; i < 3; i++)
	{
		if (goodses[i].GetGoods() == nullptr)
		{
			potion->setName("Potion");
			goodses[i].SetGoods(potion);
			goodses[i].SetPrice(potion->GetScale() * curLevel);

			return true;
		}
	}

	return false;
}

/// <summary>
/// �����������ͬʱ���ü۸�
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
			goodses[i].SetPrice(wp->GetRarity() * curLevel);

			return true;
		}
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
	skp->setGlobalZOrder(shadeOrder);
	return skp;
}

/// <summary>
/// ����һ�����ܣ����ػ��ܵ�ָ��
/// </summary>
/// <returns></returns>
Sprite* Shop::shelfCreate()
{
	auto shelf = Sprite::create(SHELF_PATH);
	shelf->setScale(0.4);
	shelf->setGlobalZOrder(shadeOrder);

	return shelf;
}

#pragma endregion