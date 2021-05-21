/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a.

 该部分为Money货币类，派生出局内金币，局外蓝币
 ****************************************************************************/

#include "Money.h"
 /// <summary>
/// 设置余额
/// </summary>
/// <param name="setValue">设置余额值</param>
void Money::setBalance(int setValue)
{
	_balance = setValue;

	return;
}
/// <summary>
/// 改变余额
/// </summary>
/// <param name="changeValue">改变余额值，正加负减</param>
/// <returns>是否改变成功</returns>
bool Money::changeBalance(int changeValue)
{
	if (_balance + changeValue >= 0)
	{
		_balance = _balance + changeValue;
		return true;
	}

	return false;
}

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
	this->setBalance(value);

	return true;
}

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
	this->setBalance(value);

	return true;
}
/// <summary>
/// 从存档中导入蓝币
/// </summary>
/// <param name="">存档路径</param>
/// <returns></returns>
bool BlueMoney::loadMoneyFromFile(std::string)
{
	/* 打开文件等操作 */
	int value;



	this->setBalance(value);

	return false;
}

void test()
{
	auto m = GoldMoney::create();
	m->changeBalance(0);

	return;
}
