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
void HealPotion::Drink()
{
	int heal = _healValue * _scale;
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
void ManaPotion::Drink()
{
	int heal = _healValue * _scale;
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

