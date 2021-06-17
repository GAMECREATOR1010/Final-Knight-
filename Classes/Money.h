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
	int GetBalance();					//��ȡ���
	void SetBalance(int setValue);		//�������
	bool ChangeBalance(int changeValue);	//�ı����
	bool create(int initValue=0);


private:
	int _balances;
};

// ���ڽ���˻����̳���Money
static class GoldMoney :public virtual Money
{
public:
	void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
private:
}goldMoney;

// ���������˻����̳���Money
static class BlueMoney : public virtual Money
{
public:
private:
}blueMoney;

#endif // !__MONEY_H__
