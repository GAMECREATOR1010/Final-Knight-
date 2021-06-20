/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
	static NPC* create(NpcId id);	//创建一个NPC对象

 该部分为NPC
 ****************************************************************************/

#pragma once

#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
USING_NS_CC;

static const char* SHOPKEEPER_PATH = "/NPC/Shopkeeper.png";

enum NpcId
{
	SHOPKEEPER,

	//待完善
	NPCCOUNT
};

class NPC : public Sprite
{
public:
	static NPC* create(NpcId id);	//创建一个NPC对象
protected:
	virtual bool init(NpcId);
private:
	NpcId _id;
};

#endif // !__NPC_H__
