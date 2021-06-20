/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪMoney�����࣬���������ڽ�ң���������
 ****************************************************************************/

#include "Money.h"

#pragma region Money

 /// <summary>
 /// ��ȡ���
 /// </summary>
 /// <returns></returns>
int Money::GetBalance()
{
	return _balances;
}

/// <summary>
/// �������
/// </summary>
/// <param name="setValue">�������ֵ</param>
void Money::SetBalance(int setValue)
{
	_balances = setValue;

	return;
}

/// <summary>
/// �ı����
/// </summary>
/// <param name="changeValue">�ı����ֵ�����Ӹ���</param>
/// <returns>�Ƿ�ı�ɹ�</returns>
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
	CCLOG("Money::ChangeBalance: from %d to %d��false", beforeBalance, goldMoney._balances + changeValue);
	return false;
}
void GoldMoney::SetBalance(int setValue)
{
	goldMoney._balances = setValue;
	return;
}

/// <summary>
/// ������ʱ���ʼӽ�ң���Ӣ�ֱؼ�
/// </summary>
/// <param name="roomLevel">��ǰ����</param>
/// <param name="enemyLevel">���˵ȼ�</param>
/// <param name="difficult">�Ѷ�ϵ��</param>
/// <param name="isElite">�Ƿ�Ϊ��Ӣ��</param>
void GoldMoney::ChangeBalanceWhileEnemyDied(int roomLevel, int enemyLevel, int difficult, bool isElite)
{
	if (!isElite)
	{
		if (random(1, 5) != 1)	//1/5���ʵ�
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

