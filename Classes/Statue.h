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
#include "Knight.h"
#include "Money.h"
#include "Buff.h"

enum StatueType
{
	WEREWOLF,	//��������
	PRIEST,		//������������
	KNIGHT,		//���ӻ���
	THIEF,		//�����˺�
	ELF,		//����Ѫ������
	SORCERER,
	ASSASSIN,
	PALADIN,
	ENGINEER,
	BERSERKER,
	/* ������ */

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
	static Statue* create(StatueType);		//��������
	bool ActiveStatue(Knight* activer);		//��������
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
