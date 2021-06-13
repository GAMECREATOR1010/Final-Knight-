/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-26)

 �˲�����δ��ɣ�����ʹ��

 �ò���ΪNPC
 ��ͬ��NPC�в�ͬ�Ĺ���
 ���ݲ�ͬ��idֵ������ͬ��npc
 ****************************************************************************/

#pragma once

#ifndef __NPC_H__
#define __NPC_H__

enum NpcId
{
	SHOPKEEPER,

	//������
	NPCCOUNT
};

const char* SHOPKEEPER_PATH = "/NPC/Shopkeeper.png";

#include "cocos2d.h"
USING_NS_CC;

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
