/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Money货币类，派生出局内金币，局外蓝币
 ****************************************************************************/

#include "Money.h"

#pragma region Money

 /// <summary>
 /// 获取金额
 /// </summary>
 /// <returns></returns>
int Money::GetBalance()
{
	return _balances;
}

/// <summary>
/// 设置余额
/// </summary>
/// <param name="setValue">设置余额值</param>
void Money::SetBalance(int setValue)
{
	_balances = setValue;

	return;
}

/// <summary>
/// 改变余额
/// </summary>
/// <param name="changeValue">改变余额值，正加负减</param>
/// <returns>是否改变成功</returns>
bool Money::ChangeBalance(int changeValue)
{
	auto beforeBalance =this->_balances;
	if (this->_balances + changeValue >= 0)
	{
		this->_balances = _balances + changeValue;
		CCLOG("Money::ChangeBalance: from %d to %d", beforeBalance, _balances);
		return true;
	}
	CCLOG("Money::ChangeBalance: from %d to %d", beforeBalance, _balances);
	return false;
}

bool Money::create(int initValue)
{
	_balances = initValue;
	return true;
}

#pragma endregion

#pragma region GoldMoney
int GoldMoney::GetBalance()
{
	return goldMoney._balances;
}
bool GoldMoney::ChangeBalance(int changeValue)
{
	auto beforeBalance = goldMoney._balances;
	if (goldMoney._balances + changeValue >= 0)
	{
		goldMoney._balances = goldMoney._balances + changeValue;
		CCLOG("Money::ChangeBalance: from %d to %d", beforeBalance, goldMoney._balances);
		return true;
	}
	CCLOG("Money::ChangeBalance: from %d to %d，false", beforeBalance, goldMoney._balances + changeValue);
	return false;
}
void GoldMoney::SetBalance(int setValue)
{
	goldMoney._balances = setValue;
	return;
}

/// <summary>
/// 怪物死时概率加金币，精英怪必加
/// </summary>
/// <param name="roomLevel">当前层数</param>
/// <param name="enemyLevel">敌人等级</param>
/// <param name="difficult">难度系数</param>
/// <param name="isElite">是否为精英怪</param>
void GoldMoney::ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel, int difficult, bool isElite)
{
	if (!isElite)
	{
		if (random(1, 5) != 1)	//1/5几率掉
		{
			return;
		}
	}
	goldMoney.ChangeBalance(MONEY_EVERY_ENEMY * roomLevel * enemyLevel * difficult * (isElite ? 3 : 1));
	return;
}


#pragma endregion

#pragma region BlueMoney

//#pragma endregion

