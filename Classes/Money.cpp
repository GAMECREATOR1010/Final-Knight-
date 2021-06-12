/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-24)

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

void test()
{
	auto m = GoldMoney::create();
	m->ChangeBalance(0);

	return;
}