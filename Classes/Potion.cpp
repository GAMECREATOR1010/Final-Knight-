/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21b (2021-5-27)

 该部分为Potion药水类
 ****************************************************************************/
#include "Potion.h"

#pragma region Potion

Potion* Potion::create(Scale scale)
{
	auto pRet = new(std::nothrow) Potion();
	if (pRet && pRet->init(scale))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	return nullptr;
}

/// <summary>
/// 获取药水规模
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

#pragma endregion

#pragma region HealPotion

 /// <summary>
 /// 使用药水
 /// </summary>
 /// <param name="multi">附加倍率，大小瓶规模无需附加</param>
void HealPotion::Drink(float multi)
{
	int heal = heal = _baseHealValue * GetScale() * multi;
	/* 调用增加生命接口 */
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

#pragma endregion

#pragma region ManaPotion

/// <summary>
/// 使用药水
/// </summary>
/// <param name="multi">附加倍率，大小瓶规模无需附加</param>
void ManaPotion::Drink(float multi)
{
	int heal = _baseHealValue * GetScale() * multi;
	/* 调用增加魔力接口 */
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

#pragma endregion

#pragma region FullPotion

/// <summary>
/// 使用药水
/// </summary>
void FullPotion::Drink()
{
	HealPotion::Drink(0.5);
	ManaPotion::Drink(0.5);

	return;
}

#pragma endregion
