/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ����
 ��ԭ��Ϸ��ͬ
 ****************************************************************************/
#pragma once
#ifndef __STATUE_H__
#define __STATUE_H__

enum StatueType
{
	WEREWOLF,	//˲���Ѫ
	PRIEST,		//˲�����
	KNIGHT,		//˲��ض�
	THIEF,		//�����˺�
	ELF,
	SORCERER,
	ASSASSIN,
	PALADIN,
	ENGINEER,
	BERSERKER,
	/* ������ */

	STATUECOUNT
};

const double STATUE_TIME = 5.0;	//������״̬����ʱ��

#include "NPC.h"
class Statue : public NPC
{
public:
	static Statue* create(StatueType);
	bool ActiveStatue(StatueType _type);	//�����ܼ�ʱͬʱ����
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
