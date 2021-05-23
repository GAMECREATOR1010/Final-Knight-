/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20c (2021-5-23).

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
#include <string>
USING_NS_CC;

// ��Ǯ�˻�,�������
class Money :public Sprite
{
public:
	//�������
	void SetBalance(int setValue);
	//�ı����
	bool ChangeBalance(int changeValue);
private:
	int _balance;
	virtual bool init() = 0;
	int getBalance();
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
	//�Ӵ浵�е�������
	bool LoadMoneyFromFile(std::string);
	//�����Ҵ洢���浵��
	bool SaveMoneyToFile(std::string);
};


#endif // !__MONEY_H__

