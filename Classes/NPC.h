/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为NPC
 不同的NPC有不同的功能
 根据不同的id值创建不同的npc
 ****************************************************************************/

#pragma once

#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
USING_NS_CC;

const char* SHOPKEEPER_PATH = "/NPC/Shopkeeper.png";

enum NpcId
{
	SHOPKEEPER,

	//待完善
	NPCCOUNT
};

class NPC : public Sprite
{
public:
	/* 创建一个NPC对象 */
	static NPC* create(NpcId id);
protected:
	virtual bool init(NpcId);
private:
	NpcId _id;
};

#endif // !__NPC_H__
