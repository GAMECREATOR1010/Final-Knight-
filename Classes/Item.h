/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ӿڣ�
	int GetRarity() const;	//��ȡƷ��

 �ò���ΪItem���������

 todo
 ��Ա������ʼ��
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

//��Ʒ����Ʒ���ָ���
//���ʼ���Ӧ�����մ�ϡ�е���ͨ���μ���
//ÿ�����ʲ���Ϊ���ֵĸ��ʣ������ڵ��μ��������ɵĸ���
//Ҳ����˵��uncommon�Ľ������5��
enum ItemProbability
{
	LEGENDARY = -1,		//�޷�ͨ��������/�̵���
	EPIC      = 10,
	VERYRARE  = 20,
	RARE      = 30,
	UNCOMMON  = 50,
	COMMON    = 100		//�ض����
};

ItemProbability RandomItemRarity();

class Item :public Sprite
{
public:
	CREATE_FUNC(Item);
	int GetRarity() const;	//��ȡƷ��
	int GetNowValue(int curLevel = 1);
protected:
	virtual bool init();
	static constexpr double _physicalRange = 80.0;
private:
	int _id;
	int _value;
	int _rarity;
};
#endif // !__ITEMS_H__
