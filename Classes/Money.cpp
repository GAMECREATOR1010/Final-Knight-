/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a.

 �ò���ΪMoney�����࣬���������ڽ�ң���������
 ****************************************************************************/

#include "Money.h"
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
/// <summary>
/// �Ӵ浵�е�������
/// </summary>
/// <param name="">�浵·��</param>
/// <returns></returns>
bool BlueMoney::LoadMoneyFromFile(std::string)
{
	/* ���ļ��Ȳ��� */
	int value;



	this->SetBalance(value);

	return false;
}
/// <summary>
/// �����Ҵ洢���浵��
/// </summary>
/// <param name="">�浵·��</param>
/// <returns></returns>
bool BlueMoney::SaveMoneyToFile(std::string)
{
	/* д���ļ��Ȳ��� */




	return false;
}





void test()
{
	auto m = GoldMoney::create();
	m->ChangeBalance(0);

	return;
}
