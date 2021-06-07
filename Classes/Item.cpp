/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Item道具类基类（暂定）
 ****************************************************************************/

#include "Item.h"

bool Item::init()
{
	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}