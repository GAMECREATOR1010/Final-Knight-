/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 �˲�����δ��ɣ�����ʹ��

 �ò���ΪPotionҩˮ��
 ������
 �� ����ҩˮ HP 2
 �� ħ��ҩˮ MP 80
 �� �ָ�ҩˮ HP 1 MP 40
 �� Buffҩˮ(��Ҫ������
 ���ýӿڣ�
 �� Ӣ��HP��MP��أ���Ҫ�ӿ�/��Drink��Ϊ��Ԫ������
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

const int MAX_POTION_SCALE = 2;
enum Scale
{
	SMALL=1, LARGE
};
enum Type
{
	HEAL, MANA, FULL, BUFF
};

class Potion : public Item
{
public:
	CREATE_FUNC(Potion);
	static Potion* create(Scale);
	int GetScale();
	int GetType();
	virtual void Drink();
private:
	Scale _scale;
	Type _type;
	//��_scale��ΪЧ��������SMALLΪ1��LARGEΪ2
	virtual bool init(Scale _scale=SMALL);
};

class HealPotion : public Potion
{
public:
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init(Scale _scale = SMALL);

};

class ManaPotion : public Potion
{
public:
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool init(Scale _scale = SMALL);

};

class FullPotion :virtual public HealPotion, virtual public ManaPotion
{
public:
	virtual void Drink();
private:
	virtual bool init(Scale _scale = SMALL);

};

class BuffPotion : public Potion
{
public:
	virtual void Drink();
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
};


#endif // !__POTION_H__

