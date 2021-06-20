/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ�̵�

 �ӿڣ�
 Goods
	bool Buy();	//������Ʒ
 Shop
	bool InitGoods();	//��ʼ����Ʒ
	std::vector <Goods>& GetGoodses();	//����������Ʒ��������ʾ
	NPC* SetShopKeeper();	//����һ������

	todo
	չʾ�����̵����Ʒ
	�����ɾ������
 ���ӹ�棨������
 ****************************************************************************/

#pragma once
#ifndef __SHOP_H__
#define __SHOP_H__

#include "RoomAndMap/Room.h"
#include "Items/Potion.h"
#include "Items/Weapon.h"
#include "NPC.h"
#include "Global/Money.h"
#include "RoomAndMap/BattleMap.h"
#include <vector>
#include <memory>
#include <typeinfo>

using std::shared_ptr;
const int MAX_GOODS = 3;
static const char* SHELF_PATH = "/shop/shelf.png";

class Goods : public Sprite
{
public:
	void SetGoods(Item*);
	void SetPrice(int);
	Item* GetGoods();
private:
	Item* _pGoods = nullptr;
	int _price;
};

class Shop : public Room
{
public:
	bool InitGoods(int curLevel);	//��ʼ����Ʒ
	NPC* SetShopKeeper();	//����һ������
	Goods goodses[3];
	Sprite* shelfCreate();
private:

	bool SetPotion(Type type, int curLevel = 1);
	bool SetWeapon(int curLevel = 1);
};

#endif // !__SHOP_H__
