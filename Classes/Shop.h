/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

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
#include "Money.h"
#include <vector>
#include <memory>

using std::shared_ptr;
const int MAX_GOODS = 3;

class Goods
{
public:
	bool Buy();
	void SetGoods(Item*);
	void SetPrice(int);
	Item* GetGoods() const;
private:
	Item* _pGoods;
	int _price;
};

class Shop : public Room
{
public:
	bool InitGoods();
	std::vector <Goods>& GetGoodses();
private:
	std::vector <Goods> _goodses;
	virtual bool init();
	bool SetPotion(Type type);
	bool SetWeapon();
	NPC* SetShopKeeper();	//��Ҫ���Ķ�����ӵ��̵����ڲ�
};

#endif // !__SHOP_H__
