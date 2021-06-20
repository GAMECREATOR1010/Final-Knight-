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
	virtual int GetBalance() = 0;					//��ȡ���
	virtual void SetBalance(int setValue) = 0;		//�������
	virtual bool ChangeBalance(int changeValue);	//�ı����
	bool create(int initValue = 0);

protected:
	int _balances;

private:
};

// ���ڽ���˻����̳���Money
static class GoldMoney :public Money
{
public:
	virtual int GetBalance();					//��ȡ���
	virtual bool ChangeBalance(int changeValue);	//�ı����
	virtual void SetBalance(int setValue);		//�������
	void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
private:
}goldMoney;

//// ���������˻����̳���Money
//static class BlueMoney : public Money
//{
//public:
//private:
//}blueMoney;

#endif // !__MONEY_H__
