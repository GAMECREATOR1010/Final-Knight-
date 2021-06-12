/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

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
	return _balance;
}

/// <summary>
/// 设置余额
/// </summary>
/// <param name="setValue">设置余额值</param>
void Money::SetBalance(int setValue)
{
	_balance = setValue;

	return;
}
/// <summary>
/// 改变余额
/// </summary>
/// <param name="changeValue">改变余额值，正加负减</param>
/// <returns>是否改变成功</returns>
bool Money::ChangeBalance(int changeValue)
{
	if (_balance + changeValue >= 0)
	{
		_balance = _balance + changeValue;
		return true;
	}

	return false;
}

#pragma endregion

#pragma region GoldMoney

/// <summary>
/// 默认初始化，金币设置为0
/// </summary>
/// <returns></returns>
bool GoldMoney::init()
{
	return true;
}
/// <summary>
/// 初始化并设置金币
/// </summary>
/// <param name="value">金币</param>
/// <returns></returns>
bool GoldMoney::init(int value)
{
	this->SetBalance(value);

	return true;
}

#pragma endregion

#pragma region BlueMoney

/// <summary>
/// 默认初始化，金币设置为0
/// </summary>
/// <returns></returns>
bool BlueMoney::init()
{
	return true;
}
/// <summary>
/// 初始化并设置金币
/// </summary>
/// <param name="value">金币</param>
/// <returns></returns>
bool BlueMoney::init(int value)
{
	this->SetBalance(value);

	return true;
}

#pragma endregion

void test()
{
	auto m = GoldMoney::create();
	m->ChangeBalance(0);

	return;
}