/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(Knight* activer);	//按技能键时同时触发技能

 该部分为雕像
 ****************************************************************************/
#pragma once
#ifndef __STATUE_H__
#define __STATUE_H__

#include "NPC.h"
#include "Knight.h"
#include "Money.h"

enum StatueType
{
	WEREWOLF,	//增加移速
	PRIEST,		//瞬间回蓝
	KNIGHT,		//增加护盾
	THIEF,		//增加伤害
	ELF,
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

const int STATUE_COST = 20;		//激活雕像花费
const double STATUE_TIME = 5.0;	//持续性状态持续时间
const double SPEED_BUFF = 0.7;	//速度buff

const int DEFENCE_BUFF = 5;		//护盾buff
const double DAMAGE_BUFF = 0.3;	//伤害buff

class Statue : public NPC
{
public:
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(Knight* activer);	//按技能键时同时触发技能
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
