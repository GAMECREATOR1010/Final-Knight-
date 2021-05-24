/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 �ò���ΪPotionҩˮ��
 ****************************************************************************/
#include "Potion.h"

#pragma region Potion

/// <summary>
/// ��ȡҩˮ��ģ
/// </summary>
/// <returns></returns>
int Potion::GetScale()
{
	return _scale;
}

#pragma endregion

#pragma region HealPotion

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

#pragma endregion


#pragma region ManaPotion

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

#pragma endregion

/// <summary>
/// ʹ��ҩˮ
/// </summary>
void FullPotion::Drink()
{
	HealPotion::Drink(0.5);
	ManaPotion::Drink(0.5);

	return;
}


