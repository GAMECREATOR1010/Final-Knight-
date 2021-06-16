/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪMoney�����࣬���������ڽ�ң���������

 �ӿ�:
 Money
	static int GetBalance();					//��ȡ���
	static void SetBalance(int setValue);		//�������
	static bool ChangeBalance(int changeValue);	//�ı����
 GoldMoney
	static void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
 ��Ҫ�ⲿȫ�ֺ궨��
 * �浵·��PATH

 To Do list:

 ****************************************************************************/
#pragma once

#ifndef __MONEY_H__
#define __MONEY_H__

#include "Const.h"

// ��Ǯ�˻�,�������
class Money
{
public:
	static int GetBalance();					//��ȡ���
	static void SetBalance(int setValue);		//�������
	static bool ChangeBalance(int changeValue);	//�ı����
	static bool create(int initValue=0);
private:
	static int _balance;
};

// ���ڽ���˻����̳���Money
static class GoldMoney :public Money
{
public:
	static void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
private:
};

// ���������˻����̳���Money
static class BlueMoney : public Money
{
public:
private:
};

#endif // !__MONEY_H__
