/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 �ò���Ϊ�̵�
 �̵�����NPC
 С�̵꣺һ�ֽ���ҩˮ��һ������ҩˮ��һ������������һƿ�ָ�ҩˮ����������
 ��Ʒ�ļ۸���������������
 ���ӹ�棨������
 ****************************************************************************/

#pragma once
#ifndef __SHOP_H__
#define __SHOP_H__

#include "Room.h"
#include "Potion.h"
#include "Weapon.h"
#include "CCVector.h"

const int MAX_GOODS = 3;

class Shop : public Room
{
public:
	bool SetGoods();
private:
	struct Goods
	{
		Item* item;
		int price;
	}goods;
	Vector<Goods> _goodses;
	//Vector<Item*> items;
	virtual bool init();
	bool SetPotion(Type type);
	bool SetWeapon();
};




#endif // !__SHOP_H__


