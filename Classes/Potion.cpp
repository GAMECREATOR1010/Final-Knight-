/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-23)

 �ò���ΪPotionҩˮ��
 ****************************************************************************/
#include "Potion.h"

#pragma region HealPotion

 /// <summary>
 /// ʹ��ҩˮ
 /// </summary>
void HealPotion::Drink()
{
	int heal = _healValue * _scale;
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

#pragma endregion


#pragma region ManaPotion

/// <summary>
/// ʹ��ҩˮ
/// </summary>
void ManaPotion::Drink()
{
	int heal = _healValue * _scale;
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

#pragma endregion

