/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-26)

 此部分尚未完成，请勿使用

 该部分为NPC
 不同的NPC有不同的功能
 根据不同的id值创建不同的npc
 ****************************************************************************/



#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
USING_NS_CC;

class NPC : public Sprite
{
public:
	static NPC* create(int id);
protected:
	virtual bool init(int id = 0);
private:
	int _id;
};


#endif // !__NPC_H__



