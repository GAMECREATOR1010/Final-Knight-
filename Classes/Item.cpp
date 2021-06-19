/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪItem��������ࣨ�ݶ���
 ****************************************************************************/

#include "Item.h"

 /// <summary>
 /// �������һ��ϡ�жȣ�����������
 /// </summary>
 /// <returns>enum ��Ʒϡ�жȸ���</returns>
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

int Item::GetNowValue(int curLevel)
{
	return _value*curLevel;
}

bool Item::Buy()
{
	auto price=this->GetNowValue();
		/* ����Ƿ����㹻��Ǯ */
		if (goldMoney.ChangeBalance(-price))
		{
			/* �ö�����Ϊ��ͨ���󽻻��������Ͳ����ظ������� */
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
			/* û���㹻��Ǯ */
			CCLOG("Item::Buy: Can not buy, check money");
			return false;
		}

	return false;
}

bool Item::init()
{
	return true;
}