/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-23)

 �ò���ΪPotionҩˮ��
 ������
 �� ����ҩˮ
 �� ħ��ҩˮ
 �� Buffҩˮ(��Ҫ������
 ���ýӿڣ�
 �� Ӣ��HP��MP��أ���Ҫ�ӿڣ�
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"
class Potion : public Item
{
public:
protected:
	enum Scale
	{
		SMALL, LARGE
	}_scale;
private:
	//��_scale��ΪЧ��������SMALLΪ1��LARGEΪ2
	virtual bool init();
};

class HealPotion : public Potion
{
public:
private:
	int _healValue;
	virtual bool init();
	void Drink();
};

class ManaPotion : public Potion
{
public:
private:
	int _healValue;
	virtual bool init();
	void Drink();
};

class BuffPotion : public Potion
{
public:
private:
	//buff����
	enum _buffType
	{
		HEALTH_MAX_ADD,
		MANA_MAX_ADD,
		SHIELD_MAX_ADD,
		//������

	};
	virtual bool init();
	void Drink();
};



#endif // !__POTION_H__

