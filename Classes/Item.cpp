/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.
 Code version 21w21a (2021-5-27).
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