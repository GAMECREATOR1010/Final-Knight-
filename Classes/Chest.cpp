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

	/* 动画效果 */
	auto frames = GetAnim("WhiteChest%02d.png", 4);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);

	auto recovery = CallFunc::create([&]() {
		this->removeFromParent();
		});
	auto seq = Sequence::create(Animate::create(animation), recovery, nullptr);
	this->runAction(seq);

	int ran = random(1, 100);
	if (ran >= 95)
	{
		auto wp = Weapon::create();
	}
	else if (ran >= 85)
	{
		auto potion = FullPotion::create(SMALL);
	}

	goldMoney.ChangeBalance(MONEY_EVERY_ROOM * MONEY_LEVEL_MUTI);
	activer->EnergyNowChange(MANA_EVERY_ROOM * MANA_LEVEL_MUTI);
	CCLOG("WhiteChest::open get gold %d", MONEY_EVERY_ROOM * MONEY_LEVEL_MUTI);

	return nullptr;
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