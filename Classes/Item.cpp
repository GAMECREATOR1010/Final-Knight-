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

int Item::GetRarity()
{
	return _rarity;
}

bool Item::init()
{
	/* �����ײ��Χ */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}