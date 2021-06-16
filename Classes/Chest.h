/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ӿڣ�
 WhiteChest
	static WhiteChest* create();	//����һ������
	virtual Item* open();			//�򿪱���

 �ò���Ϊ������

  todo list:
 �򿪱���
 ****************************************************************************/
#pragma once

#ifndef __CHEST_H__
#define __CHEST_H__

#include "cocos2d.h"
#include "Const.h"
#include "Money.h"
#include "Potion.h"
#include "Weapon.h"

USING_NS_CC;

const char* WHITE_CHEST_PATH = "/chests/WhiteChest.png";
const char* BLUE_CHEST_PATH  = "/chests/BlueChest.png";
const char* BROWN_CHEST_PATH = "/chests/BrownChest.png";

enum ChestType
{
	WHITE_CHEST,
	BLUE_CHEST,
	BROWN_CHEST,

	CHEST_COUNT
};

class Chest : public Sprite
{
public:
	virtual Item* open() = 0;
protected:
	virtual bool init();
private:
	static constexpr double _physicalRange = 80.0;
};

/* ��ɫ���䣬�ؿ����������䷿�� */
class WhiteChest : public Chest
{
public:
	static WhiteChest* create();	//����һ������
	virtual Item* open();			//�򿪱���
private:
	virtual bool init();
};

#endif // !__CHEST_H__

