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
#include "PlayerAndMonster/Knight.h"
#include "Global/Money.h"
#include "Global/Buff.h"

enum StatueType
{
	WEREWOLF,	//增加移速
	PRIEST,		//增加蓝量上限
	KNIGHT,		//增加护盾
	THIEF,		//增加伤害
	ELF,		//增加血量上限
	//SORCERER,
	//ASSASSIN,
	//PALADIN,
	//ENGINEER,
	//BERSERKER,
	/* 待完善 */

	STATUECOUNT
};

static const char* WEREWOLF_PATH = "/statues/WerewolfStatue.png";
static const char* PRIEST_PATH = "/statues/PriestStatue.png";
static const char* KNIGHT_PATH = "/statues/KnightStatue.png";
static const char* THIEF_PATH = "/statues/ThiefStatue.png";
static const char* ELF_PATH = "/statues/ElfStatue.png";

class Statue : public NPC
{
public:
	static Statue* create(StatueType type);		//创建雕像
	bool ActiveStatue(Knight* activer);		//触发技能
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
	const double _physicalRange = 80.0;
	bool isActived = false;
};

#endif // !__STATUE_H__
