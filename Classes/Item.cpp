/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪItem��������ࣨ�ݶ���
 ****************************************************************************/

#include "Item.h"

bool Item::init()
{
	/* �����ײ��Χ */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}