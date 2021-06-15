 /****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为宝箱类
 ****************************************************************************/
#include "Chest.h"

 /// <summary>
 /// 仅添加物理碰撞
 /// </summary>
 /// <returns></returns>
bool Chest::init()
{
	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

WhiteChest* WhiteChest::create()
{
	auto pRet = new(std::nothrow) WhiteChest();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}
	return nullptr;
}

/// <summary>
/// 打开宝箱，生成物品/金币能量，生成物品后需要将该对象加入层
/// </summary>
/// <returns>生成的物品对象指针，生成金币能量返回空</returns>
Item* WhiteChest::open()
{
	/* 动画效果（待定） */

	/* 改变材质 */

	/* 随机生成 */
	int type = random(1, 5);
	switch (type)
	{
		case 1:	//生成金币和能量

			return nullptr;
		case 2:	//生成HP药水
			auto hp = HealPotion::create(SMALL);
			return hp;
		case 3:	//生成MP药水
			auto mp = ManaPotion::create(SMALL);
			return mp;
		case 4:	//生成武器
			auto wp = RandomWeaponCreate();
			return wp;
		default:
			throw("No such type in chest");
			break;
	}
}

/// <summary>
/// 添加图片，添加碰撞范围
/// </summary>
/// <returns></returns>
bool WhiteChest::init()
{
	if (!initWithFile(WHITE_CHEST_PATH) && !Chest::init())
	{
		return false;
	}

	return true;
}