/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(Knight* activer);		//触发技能

 该部分为雕像

 todo
 展示雕像
 ****************************************************************************/
#pragma once
#ifndef __STATUE_H__
#define __STATUE_H__

#include "NPC.h"
#include "Knight.h"
#include "Money.h"
#include "Buff.h"

enum StatueType
{
	WEREWOLF,	//增加移速
	PRIEST,		//增加蓝量上限
	KNIGHT,		//增加护盾
	THIEF,		//增加伤害
	ELF,		//增加血量上限
	SORCERER,
	ASSASSIN,
	PALADIN,
	ENGINEER,
	BERSERKER,
	/* 待完善 */

	STATUECOUNT
};

const char* WEREWOLF_PATH = "/statues/WerewolfStatue.png";
const char* PRIEST_PATH = "/statues/PriestStatue.png";
const char* KNIGHT_PATH = "/statues/KnightStatue.png";
const char* THIEF_PATH = "/statues/ThiefStatue.png";
const char* ELF_PATH = "/statues/ElfStatue.png";

class Statue : public NPC
{
public:
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(Knight* activer);		//触发技能
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
