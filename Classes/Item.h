/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪItem���������ͷ�ļ����ݶ���
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Const.h"
USING_NS_CC;

class Item :public Sprite
{
public:
	CREATE_FUNC(Item);
protected:
	virtual bool init();
private:
	int _id;
	int _value;
	int _rarity;
	const double _physicalRange = 80 ;
};
#endif // !__ITEMS_H__
