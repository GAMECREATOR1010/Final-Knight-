/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 接口：
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(StatueType _type);	//按技能键时同时触发技能

 该部分为雕像
 ****************************************************************************/
#pragma once
#ifndef __STATUE_H__
#define __STATUE_H__

enum StatueType
{
	WEREWOLF,	//瞬间回血
	PRIEST,		//瞬间回蓝
	KNIGHT,		//瞬间回盾
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

const double STATUE_TIME = 5.0;	//持续性状态持续时间

#include "NPC.h"
class Statue : public NPC
{
public:
	static Statue* create(StatueType);		//创建雕像
	bool ActiveStatue(StatueType _type);	//按技能键时同时触发技能
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
