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

//buff����
enum BuffType
{
	RANDOM,
	HEALTH_MAX_ADD,
	MANA_MAX_ADD,
	SHIELD_MAX_ADD,
	ATTACK_DAMAGE_ADD,

	//������
	BUFF_COUNT	//������
};

class Potion : public Item
{
public:
	int GetScale();
	int GetType();
	virtual void Drink(float multi = 1)=0;
protected:
	bool initWithScale(Scale scale);
private:
	Scale _scale;
	Type _type;
	//��_scale��ΪЧ��������SMALLΪ1��LARGEΪ2
};

class HealPotion : virtual public Potion
{
public:
	static HealPotion* create(Scale);
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);

};

class ManaPotion : virtual public Potion
{
public:
	static ManaPotion* create(Scale);
	virtual void Drink(float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);

};

class FullPotion :public HealPotion,public ManaPotion
{
public:
	static FullPotion* create(Scale);
	virtual void Drink(float multi = 0.5);
private:
	virtual bool initWithScale(Scale _scale = SMALL);

};

class BuffPotion : public Potion
{
public:
	static BuffPotion* create(BuffType buffType);
	virtual void Drink(float multi = 1);
private:
	BuffType _buffType;
	virtual bool initWithBuffType(BuffType buffType);
};


#endif // !__POTION_H__

