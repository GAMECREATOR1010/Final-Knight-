/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21b (2021-5-27)

 �ò���ΪPotionҩˮ��
 ****************************************************************************/
#include "Potion.h"
#include <stdexcept>

#pragma region Potion

/// <summary>
/// ��ȡҩˮ��ģ
/// </summary>
/// <returns></returns>
int Potion::GetScale()
{
	return _scale;
}

int Potion::GetType()
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
/// ʹ��ҩˮ
/// </summary>
/// <param name="multi">���ӱ��ʣ���Сƿ��ģ���踽��</param>
void HealPotion::Drink(float multi)
{
	int heal = heal = _baseHealValue * GetScale() * multi;
	/* �������������ӿ� */
	if (curHP + heal >= maxHP)
	{
		curHP = maxHP;
	}
	else
	{
		curHP += heal;
	}
	return;
}

bool HealPotion::initWithScale(Scale scale)
{
	initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile("/potions/HealthSmall.png");
			break;
		case LARGE:
			initWithFile("/potions/HealthLarge.png");
			break;
		default:
			return false;
			break;
	}
	return true;
}

#pragma endregion

#pragma region ManaPotion

ManaPotion* ManaPotion::create(Scale scale)
{
	auto pRet = new(std::nothrow) ManaPotion();
	if (pRet && pRet->initWithScale(scale))
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
/// ʹ��ҩˮ
/// </summary>
/// <param name="multi">���ӱ��ʣ���Сƿ��ģ���踽��</param>
void ManaPotion::Drink(float multi)
{
	int heal = _baseHealValue * GetScale() * multi;
	/* ��������ħ���ӿ� */
	if (curMP + heal >= maxMP)
	{
		curMP = maxMP;
	}
	else
	{
		curMP += heal;
	}

	return;
}

bool ManaPotion::initWithScale(Scale scale)
{
	initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile("/potions/ManaSmall.png");
			break;
		case LARGE:
			initWithFile("/potions/ManaLarge.png");
			break;
		default:
			return false;
			break;
	}
	return true;
}

#pragma endregion

#pragma region FullPotion

FullPotion* FullPotion::create(Scale scale)
{
	auto pRet = new(std::nothrow) FullPotion();
	if (pRet && pRet->initWithScale(scale))
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
/// ʹ��ҩˮ
/// </summary>
void FullPotion::Drink(float multi = 0.5)
{
	HealPotion::Drink(multi);
	ManaPotion::Drink(multi);

	return;
}

bool FullPotion::initWithScale(Scale scale)
{
	initWithScale(scale);
	switch (scale)
	{
		case SMALL:
			initWithFile("/potions/FullSmall.png");
			break;
		case LARGE:
			initWithFile("/potions/FullLarge.png");
			break;
		default:
			return false;
			break;
	}
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
/// ʹ��ҩˮ
/// </summary>
/// <param name="multi"></param>
void BuffPotion::Drink(float multi = 1)
{
	int buff = _buffType;
	if (buff == RANDOM)
	{
		buff = random(1, (int)_buffType);
	}
	switch (buff)
	{
		case HEALTH_MAX_ADD:
			break;
		case MANA_MAX_ADD:
			break;
		case SHIELD_MAX_ADD:
			break;
		case ATTACK_DAMAGE_ADD:
			break;
		case BUFF_COUNT:
			throw(ERROR_DOMAIN_LIMIT_EXCEEDED);
			break;
		default:
			break;
	}
}

bool BuffPotion::initWithBuffType(BuffType buffType)
{
	_buffType = buffType;
	initWithFile("/potions/Buff.png");
	return true;
}

#pragma endregion


