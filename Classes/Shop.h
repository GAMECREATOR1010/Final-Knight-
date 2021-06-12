/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �˲�����δ��ɣ�����ʹ��

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
#include "NPC.h"
#include <vector>

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
	std::vector <Goods> _goodses;
	virtual bool init();
	bool SetPotion(Type type);
	bool SetWeapon();
	NPC* SetShopKeeper();	//��Ҫ���Ķ�����ӵ��̵����ڲ�
};

#endif // !__SHOP_H__
