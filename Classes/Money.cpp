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

#pragma endregion

#pragma region GoldMoney

/// <summary>
/// Ĭ�ϳ�ʼ�����������Ϊ0
/// </summary>
/// <returns></returns>
bool GoldMoney::init()
{
	SetBalance(0);

	return true;
}

/// <summary>
/// ��ʼ�������ý��
/// </summary>
/// <param name="value">���</param>
/// <returns></returns>
bool GoldMoney::init(int value)
{
	this->SetBalance(value);

	return true;
}

#pragma endregion

#pragma region BlueMoney

/// <summary>
/// Ĭ�ϳ�ʼ�����������Ϊ0
/// </summary>
/// <returns></returns>
bool BlueMoney::init()
{
	SetBalance(0);

	return true;
}

/// <summary>
/// ��ʼ�������ý��
/// </summary>
/// <param name="value">���</param>
/// <returns></returns>
bool BlueMoney::init(int value)
{
	this->SetBalance(value);

	return true;
}

#pragma endregion