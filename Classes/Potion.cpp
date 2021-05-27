/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21b (2021-5-27)

 �ò���ΪPotionҩˮ��
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

#pragma region FullPotion

/// <summary>
/// ʹ��ҩˮ
/// </summary>
void FullPotion::Drink()
{
	HealPotion::Drink(0.5);
	ManaPotion::Drink(0.5);

	return;
}

#pragma endregion
