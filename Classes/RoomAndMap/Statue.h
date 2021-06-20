/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ӿڣ�
	static Statue* create(StatueType);		//��������
	bool ActiveStatue(Knight* activer);		//��������

 �ò���Ϊ����

 todo
 չʾ����
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
	WEREWOLF,	//��������
	PRIEST,		//������������
	KNIGHT,		//���ӻ���
	THIEF,		//�����˺�
	ELF,		//����Ѫ������
	//SORCERER,
	//ASSASSIN,
	//PALADIN,
	//ENGINEER,
	//BERSERKER,
	/* ������ */

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
	static Statue* create(StatueType type);		//��������
	bool ActiveStatue(Knight* activer);		//��������
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
	const double _physicalRange = 80.0;
	bool isActived = false;
};

#endif // !__STATUE_H__
