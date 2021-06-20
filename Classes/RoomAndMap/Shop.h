/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为商店

 接口：
 Goods
	bool Buy();	//购买商品
 Shop
	bool InitGoods();	//初始化商品
	std::vector <Goods>& GetGoodses();	//返回所有商品，用于显示
	NPC* SetShopKeeper();	//返回一个商人

	todo
	展示设置商店和物品
	购买后删除对象
 电视广告（待定）
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
	bool InitGoods(int curLevel);	//初始化商品
	NPC* SetShopKeeper();	//返回一个商人
	Goods goodses[3];
	Sprite* shelfCreate();
private:

	bool SetPotion(Type type, int curLevel = 1);
	bool SetWeapon(int curLevel = 1);
};

#endif // !__SHOP_H__
