/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪPotionҩˮ��
 ****************************************************************************/
#include "Items/Potion.h"

#pragma region Potion

 /// <summary>
 /// ��ȡҩˮ��ģ
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
/// ����ҩˮ��ģ
/// </summary>
/// <param name="scale">SMALL,LARGE</param>
/// <returns></returns>
bool Potion::initWithScale(Scale scale)
{
	_scale = scale;
	this->setGlobalZOrder(shadeOrder);
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
/// ʹ��ҩˮ��ʹ��֮��ǵ�ɾ������
/// </summary>
/// <param name="multi">���ӱ��ʣ���Сƿ��ģ���踽��</param>
void HealPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk && !_isFullPotion)
	{
		return;
	}
	_isDrunk = true;
	int heal = heal = _baseHealValue * GetScale() * multi;
	/* �������������ӿ� */
	auto beforeHp = drinker->GetHP();
	drinker->HPNowChange(heal);
	CCLOG("HealPotion::Drink: Before Hp %f, now Hp %f", beforeHp, drinker->GetHP());
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

	this->SetValue(healPotionValue * this->GetScale());

	/* �����ײ��Χ */
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
/// ʹ��ҩˮ��ʹ��֮��ǵ�ɾ������
/// </summary>
/// <param name="multi">���ӱ��ʣ���Сƿ��ģ���踽��</param>
void ManaPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk && !_isFullPotion)
	{
		return;
	}
	_isDrunk = true;
	int heal = _baseHealValue * GetScale() * multi;
	/* ��������ħ���ӿ� */
	auto beforeMp = drinker->GetEnergyNow();
	drinker->EnergyNowChange(heal);
	CCLOG("ManaPotion::Drink: Before Mp %f, now Mp %f", beforeMp, drinker->GetEnergyNow());
	this->setVisible(false);
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

	this->SetValue(manaPotionValue * this->GetScale());

	/* �����ײ��Χ */
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
/// ʹ��ҩˮ��ʹ��֮��ǵ�ɾ������
/// </summary>
void FullPotion::Drink(Knight* drinker, float multi)
{
	if (_isDrunk)
	{
		return;
	}
	HealPotion::Drink(drinker, multi);
	ManaPotion::Drink(drinker, multi);
	_isDrunk = true;
	CCLOG("FullPotion::Drink: HP++MP++");

	this->setVisible(false);

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

	this->_isFullPotion = true;
	this->SetValue(fullPotionValue * this->GetScale());

	/* �����ײ��Χ */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion

#pragma region BuffPotion

/// <summary>
/// ����Buffҩˮ
/// </summary>
/// <param name="buffType">ҩˮbuff��0=���</param>
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
/// ʹ��ҩˮ��ʹ��֮��ǵ�ɾ������
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
		buff = random(0, static_cast <int>(_buffType) - 1);
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
			CCLOG("BuffPotion::Drink; no this type %d", buff);
			break;
	}
}

bool BuffPotion::initWithBuffType(BuffType buffType)
{
	Potion::init();
	_buffType = buffType;
	initWithFile(BUFF_PATH);

	this->SetValue(buffPotionValue * this->GetScale());

	/* �����ײ��Χ */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}

#pragma endregion