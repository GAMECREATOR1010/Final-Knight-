/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-23)

 该部分为Potion药水类
 ****************************************************************************/
#include "Potion.h"

#pragma region HealPotion

 /// <summary>
 /// 使用药水
 /// </summary>
 /// <param name="multi">附加倍率，大小瓶规模无需附加</param>
void HealPotion::Drink(float multi)
{
	int heal = heal = _baseHealValue * _scale * multi;
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
	int heal = _baseHealValue * _scale * multi;
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

/// <summary>
/// 使用药水
/// </summary>
void FullPotion::Drink()
{
	HealPotion::Drink(0.5);
	ManaPotion::Drink(0.5);

	return;
}
