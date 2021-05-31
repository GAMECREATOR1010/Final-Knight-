/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w22a (2021-5-31)

 �ò���Ϊ����
 ****************************************************************************/
#ifndef __STATUE_H__
#define __STATUE_H__

enum StatueType
{
	THIEF,
	ELF,
	SORCERER,
	PRIEST,
	ASSASSIN,
	KNIGHT,
	PALADIN,
	ENGINEER,
	BERSERKER,
	WEREWOLF,
	/* ������ */

	STATUECOUNT
};

#pragma once
#include "NPC.h"
class Statue : public NPC
{
public:
	static Statue* create(StatueType);
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
