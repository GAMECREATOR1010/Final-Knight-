/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪMoney�����࣬���������ڽ�ң���������

 ��Ҫ�ⲿ�ӿ�

 ��Ҫ�ⲿȫ�ֺ궨��
 * �浵·��PATH

 To Do list:
 * ����������������� ��Ӧ���������������룺���˵ȼ��������Ѷȡ��ؿ����������������������(��ȻҲ���ܲ����ӣ�
 * ��Ӣ�����˱ص�
 * �����������������/���� ��Ӧ�����俪�������룺�����Ѷȡ��ؿ����������������������/��������
 ****************************************************************************/
#pragma once

#ifndef __MONEY_H__
#define __MONEY_H__

#include "cocos2d.h"
USING_NS_CC;

// ��Ǯ�˻�,�������
class Money :public Sprite
{
public:
	//��ȡ���
	static int GetBalance();
	//�������
	static void SetBalance(int setValue);
	//�ı����
	static bool ChangeBalance(int changeValue);
private:
	static int _balance;
	virtual bool init() = 0;
};

// ���ڽ���˻����̳���Money
class GoldMoney :public Money
{
public:
	CREATE_FUNC(GoldMoney)
private:
	virtual bool init();
	virtual bool init(int);
};

// ���������˻����̳���Money
class BlueMoney : public Money
{
public:
	CREATE_FUNC(BlueMoney)
private:
	virtual bool init();
	virtual bool init(int);
};

#endif // !__MONEY_H__
