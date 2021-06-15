/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ӿڣ�
	static Statue* create(StatueType);		//��������
	bool ActiveStatue(Knight* activer);	//�����ܼ�ʱͬʱ��������

 �ò���Ϊ����
 ****************************************************************************/
#pragma once
#ifndef __STATUE_H__
#define __STATUE_H__

#include "NPC.h"
#include "Knight.h"
#include "Money.h"

enum StatueType
{
	WEREWOLF,	//��������
	PRIEST,		//˲�����
	KNIGHT,		//���ӻ���
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

const char* WEREWOLF_PATH = "/statues/WerewolfStatue.png";
const char* PRIEST_PATH = "/statues/PriestStatue.png";
const char* KNIGHT_PATH = "/statues/KnightStatue.png";
const char* THIEF_PATH = "/statues/ThiefStatue.png";
const char* ELF_PATH = "/statues/ElfStatue.png";

const int STATUE_COST = 20;		//������񻨷�
const double STATUE_TIME = 5.0;	//������״̬����ʱ��
const double SPEED_BUFF = 0.7;	//�ٶ�buff

const int DEFENCE_BUFF = 5;		//����buff
const double DAMAGE_BUFF = 0.3;	//�˺�buff

class Statue : public NPC
{
public:
	static Statue* create(StatueType);		//��������
	bool ActiveStatue(Knight* activer);	//�����ܼ�ʱͬʱ��������
protected:
	virtual bool init(StatueType);
private:
	StatueType _type;
};

#endif // !__STATUE_H__
