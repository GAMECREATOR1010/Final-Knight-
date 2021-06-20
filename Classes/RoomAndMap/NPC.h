/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ӿڣ�
	static NPC* create(NpcId id);	//����һ��NPC����

 �ò���ΪNPC
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

	//������
	NPCCOUNT
};

class NPC : public Sprite
{
public:
	static NPC* create(NpcId id);	//����һ��NPC����
protected:
	virtual bool init(NpcId);
private:
	NpcId _id;
};

#endif // !__NPC_H__
