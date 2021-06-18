/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Potion药水类
 ****************************************************************************/
#include "Potion.h"

#pragma region Potion

 /// <summary>
 /// 获取药水规模
 /// </summary>
 /// <returns></returns>
int Potion::GetScale() const
{
	return _scale;
}

int Potion::GetType() const
{
	return _type;
}

/// <summary>
/// 设置药水规模
/// </summary>
/// <param name="scale">SMALL,LARGE</param>
/// <returns></returns>
bool Potion::initWithScale(Scale scale)
{
	_scale = scale;
	Item::init();
	return true;
}

#pragma endregion

#pragma region HealPotion

HealPotion* HealPotion::create(Scale scale)
{
	auto pRet = new(std::nothrow) HealPotion();
	if (pRet && pRet->initWithScale(scale))
	{
		pRet->setGlobalZOrder(shadeOrder);
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
/// 使用药水，使用之后记得删除对象
/// </summary>
/// <param name="multi">附加倍率，大小瓶规模无需附加</param>
void HealPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk)
	{
		return;
	}
	_isDrunk = true;
	int heal = heal = _baseHealValue * GetScale() * multi;
	/* 调用增加生命接口 */
	drinker->HPNowChange(heal);
	this->setVisible(false);
	return;
}

bool HealPotion::initWithScale(Scale scale)
{
	Potion::initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile(HEALTH_SMALL_PATH);
			break;
		case LARGE:
			initWithFile(HEALTH_LARGE_PATH);
			break;
		default:
			return false;
			break;
	}

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion

#pragma region ManaPotion

ManaPotion* ManaPotion::create(Scale scale)
{
	auto pRet = new(std::nothrow) ManaPotion();
	if (pRet && pRet->initWithScale(scale))
	{
		pRet->setGlobalZOrder(shadeOrder);
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
/// 使用药水，使用之后记得删除对象
/// </summary>
/// <param name="multi">附加倍率，大小瓶规模无需附加</param>
void ManaPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk)
	{
		return;
	}
	_isDrunk = true;
	int heal = _baseHealValue * GetScale() * multi;
	/* 调用增加魔力接口 */
	drinker->EnergyNowChange(heal);

	return;
}

bool ManaPotion::initWithScale(Scale scale)
{
	Potion::initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile(MANA_SMALL_PATH);
			break;
		case LARGE:
			initWithFile(MANA_LARGE_PATH);
			break;
		default:
			return false;
			break;
	}

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion

#pragma region FullPotion

FullPotion* FullPotion::create(Scale scale)
{
	auto pRet = new(std::nothrow) FullPotion();
	if (pRet && pRet->initWithScale(scale))
	{
		pRet->setGlobalZOrder(shadeOrder);
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
/// 使用药水，使用之后记得删除对象
/// </summary>
void FullPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk)
	{
		return;
	}
	_isDrunk = true;
	HealPotion::Drink(drinker, multi);
	ManaPotion::Drink(drinker, multi);

	return;
}

bool FullPotion::initWithScale(Scale scale)
{
	Potion::initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile(FULL_SMALL_PATH);
			break;
		case LARGE:
			initWithFile(FULL_LARGE_PATH);
			break;
		default:
			return false;
			break;
	}

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion

#pragma region BuffPotion

/// <summary>
/// 创建Buff药水
/// </summary>
/// <param name="buffType">药水buff，0=随机</param>
/// <returns></returns>
BuffPotion* BuffPotion::create(BuffType buffType)
{
	auto pRet = new(std::nothrow) BuffPotion();
	if (pRet && pRet->initWithBuffType(buffType))
	{
		pRet->setGlobalZOrder(shadeOrder);
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
/// 使用药水，使用之后记得删除对象
/// </summary>
/// <param name="multi"></param>
void BuffPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk)
	{
		return;
	}
	_isDrunk = true;
	int buff = _buffType;
	if (buff == RANDOM)
	{
		buff = random(1, (int)_buffType);
	}
	switch (buff)
	{
		case HEALTH_MAX_ADD:
			drinker->HPMaxChange(HEALTH_MAXADD_BUFF);
			break;
		case MANA_MAX_ADD:
			drinker->EnergyMaxChange(MANA_MAXADD_BUFF);
			break;
		case SHIELD_MAX_ADD:
			drinker->DefenceNowChange(DEFENCE_BUFF);
			break;
		case SPEED_ADD:
			drinker->MoveSpeedMaxChange(SPEED_BUFF);
			break;
		case BUFF_COUNT:
		default:
			throw(ERROR_DOMAIN_LIMIT_EXCEEDED);
			break;
	}
}

bool BuffPotion::initWithBuffType(BuffType buffType)
{
	Potion::init();
	_buffType = buffType;
	initWithFile(BUFF_PATH);

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion