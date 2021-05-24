/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 该部分为商店
 商店内有NPC
 小商店：一种健康药水，一种能量药水和一种武器，或者一瓶恢复药水和两件武器
 物品的价格或随层数上升上涨
 电视广告（待定）
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



