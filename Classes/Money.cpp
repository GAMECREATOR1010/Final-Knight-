/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20c (2021-5-23).

 该部分为Money货币类，派生出局内金币，局外蓝币
 ****************************************************************************/

#include "Money.h"

#pragma region Money

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
/// <summary>
/// 获取当前账户余额
/// </summary>
/// <returns></returns>
int Money::getBalance()
{
	return _balance;
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
/// <summary>
/// 从存档中导入蓝币
/// </summary>
/// <param name="">存档路径</param>
/// <returns></returns>
bool BlueMoney::LoadMoneyFromFile(std::string)
{
	/* 打开文件等操作 */
	int value;



	this->SetBalance(value);

	return false;
}
/// <summary>
/// 将蓝币存储到存档中
/// </summary>
/// <param name="">存档路径</param>
/// <returns></returns>
bool BlueMoney::SaveMoneyToFile(std::string)
{
	/* 写入文件等操作 */




	return false;
}

#pragma endregion


void test()
{
	auto m = GoldMoney::create();
	m->ChangeBalance(0);

	return;
}
