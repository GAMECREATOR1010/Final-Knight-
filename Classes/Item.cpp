/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

 该部分为Item道具类基类（暂定）
 ****************************************************************************/

#include "Item.h"

int Item::GetID()
{
	return _id;
}

int Item::GetValue()
{
	return _value;
}

int Item::GetRarity()
{
	return _rarity;
}

bool Item::init()
{
	return true;
}
