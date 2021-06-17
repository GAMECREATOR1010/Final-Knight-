/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Money货币类，派生出局内金币，局外蓝币

 接口:
 Money
	static int GetBalance();					//获取金额
	static void SetBalance(int setValue);		//设置余额
	static bool ChangeBalance(int changeValue);	//改变余额
 GoldMoney
	static void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
 需要外部全局宏定义
 * 存档路径PATH

 To Do list:

 ****************************************************************************/
#pragma once

#ifndef __MONEY_H__
#define __MONEY_H__

#include "Const.h"

// 金钱账户,抽象基类
class Money
{
public:
	int GetBalance();					//获取金额
	void SetBalance(int setValue);		//设置余额
	bool ChangeBalance(int changeValue);	//改变余额
	bool create(int initValue=0);


private:
	int _balances;
};

// 局内金币账户，继承自Money
static class GoldMoney :public virtual Money
{
public:
	void ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel = 1, int difficult = 1, bool isElite = false);
private:
}goldMoney;

// 局外蓝币账户，继承自Money
static class BlueMoney : public virtual Money
{
public:
private:
}blueMoney;

#endif // !__MONEY_H__
