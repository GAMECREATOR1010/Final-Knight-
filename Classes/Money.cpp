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
	return _balance;
}

/// <summary>
/// �������
/// </summary>
/// <param name="setValue">�������ֵ</param>
void Money::SetBalance(int setValue)
{
	_balance = setValue;

	return;
}

/// <summary>
/// �ı����
/// </summary>
/// <param name="changeValue">�ı����ֵ�����Ӹ���</param>
/// <returns>�Ƿ�ı�ɹ�</returns>
bool Money::ChangeBalance(int changeValue)
{
	if (_balance + changeValue >= 0)
	{
		_balance = _balance + changeValue;
		return true;
	}

	return false;
}

bool Money::create(int initValue)
{
	_balance = initValue;
	return true;
}

#pragma endregion

#pragma region GoldMoney
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
	ChangeBalance(MONEY_EVERY_ENEMY * roomLevel * enemyLevel * difficult * (isElite ? 3 : 1));
	return;
}


#pragma endregion

#pragma region BlueMoney

#pragma endregion

