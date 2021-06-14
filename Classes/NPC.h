/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪNPC
 ��ͬ��NPC�в�ͬ�Ĺ���
 ���ݲ�ͬ��idֵ������ͬ��npc
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

	//������
	NPCCOUNT
};

class NPC : public Sprite
{
public:
	/* ����һ��NPC���� */
	static NPC* create(NpcId id);
protected:
	virtual bool init(NpcId);
private:
	NpcId _id;
};

#endif // !__NPC_H__
