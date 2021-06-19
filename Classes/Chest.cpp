/****************************************************************************
Copyright (c) 2021 Final-Knight- Group.

该部分为宝箱类
****************************************************************************/
#include "Chest.h"

bool Chest::init()
{
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
Item* WhiteChest::open(Knight* activer)
{
	if (_isOpened)
	{
		return nullptr;
	}
	_isOpened = true;
	this->setVisible(false);
	/* 动画效果（待定） */

	/* 改变材质 */

	/* 随机生成 */
	int type = random(1, 4);
	switch (type)
	{
		case 1:	//生成金币和能量
			goldMoney.ChangeBalance(MONEY_EVERY_ROOM * MONEY_LEVEL_MUTI);
			activer->EnergyNowChange(MANA_EVERY_ROOM * MANA_LEVEL_MUTI);
			CCLOG("WhiteChest::open get gold");
			return nullptr;
		case 2:	//生成HP药水
		{
			auto hp = HealPotion::create(SMALL);
			hp->setTag(potionChestTag);
			CCLOG("WhiteChest::open get hp, position at %f %f",this->getPositionX(),this->getPositionY());
			return hp;
		}
		case 3:	//生成MP药水
		{
			auto mp = ManaPotion::create(SMALL);
			mp->setTag(potionChestTag);
			CCLOG("WhiteChest::open get mp, position at %f %f", this->getPositionX(), this->getPositionY());
			return mp;
		}
		case 4:	//生成武器
		{
			auto wp = RandomWeaponCreate();
			wp->setTag(weaponChestTag);
			CCLOG("WhiteChest::open get wp, position at %f %f", this->getPositionX(), this->getPositionY());
			return wp;
		}
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

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(80.0);
	SetBody(phy, ItemCate);
	this->addComponent(phy);

	this->setTag(chestTag);
	this->setGlobalZOrder(shadeOrder);
	return true;
}