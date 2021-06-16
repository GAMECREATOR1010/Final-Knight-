/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪPotionҩˮ��
 ������
 �� ����ҩˮ HP 2
 �� ħ��ҩˮ MP 80
 �� �ָ�ҩˮ HP 1 MP 40
 �� Buffҩˮ

 �ӿڣ�
	virtual void Drink(float multi = 1) = 0;	//ʹ��ҩˮ

todo
��ҩˮ��Ч��
 ****************************************************************************/
#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"
#include "Knight.h"
#include "Buff.h"

const int MAX_POTION_SCALE = 2;

const char* HEALTH_SMALL_PATH = "/potions/HealthSmall.png";
const char* HEALTH_LARGE_PATH = "/potions/HealthLarge.png";
const char* MANA_SMALL_PATH = "/potions/ManaSmall.png";
const char* MANA_LARGE_PATH = "/potions/ManaLarge.png";
const char* FULL_SMALL_PATH = "/potions/FullSmall.png";
const char* FULL_LARGE_PATH = "/potions/FullLarge.png";
const char* BUFF_PATH = "/potions/Buff.png";

enum Scale
{
	SMALL = 1, LARGE
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
	SPEED_ADD,

	//������
	BUFF_COUNT	//������
};

class Potion : public Item
{
public:
	int GetScale() const;
	int GetType() const;
	virtual void Drink(Knight* drinker,float multi = 1) = 0;	//ʹ��ҩˮ
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
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);
};

class ManaPotion : virtual public Potion
{
public:
	static ManaPotion* create(Scale);
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	int _baseHealValue;
	virtual bool initWithScale(Scale _scale = SMALL);
};

class FullPotion :public HealPotion, public ManaPotion
{
public:
	static FullPotion* create(Scale);
	virtual void Drink(Knight* drinker,float multi = 0.5);
private:
	virtual bool initWithScale(Scale _scale = SMALL);
};

class BuffPotion : public Potion
{
public:
	static BuffPotion* create(BuffType buffType);
	virtual void Drink(Knight* drinker, float multi = 1);
private:
	BuffType _buffType;
	virtual bool initWithBuffType(BuffType buffType);
};

#endif // !__POTION_H__
