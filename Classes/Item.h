/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a.

 �ò���ΪItem���������ͷ�ļ����ݶ���
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
USING_NS_CC;

class Item:public Sprite
{
public:
	CREATE_FUNC(Item);

private:

	virtual bool init();

};
#endif // !__ITEMS_H__
