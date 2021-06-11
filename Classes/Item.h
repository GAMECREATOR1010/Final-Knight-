/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���ΪItem���������ͷ�ļ����ݶ���
 ****************************************************************************/
#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

//#pragma region Item_Probability
///* 
//   �˴�Ϊ��Ʒ����Ʒ���ָ��� 
//   ���ʼ���Ӧ�����մ�ϡ�е���ͨ���μ���
//   ÿ�����ʲ���Ϊ���ֵĸ��ʣ������ڵ��μ��������ɵĸ���
//   Ҳ����˵��uncommon�Ľ������5��
//*/
//const int COMMON_PROBABILITY = 100;		//�ض����
//const int UNCOMMON_PROBABILITY = 50;
//const int RARE_PROBABILITY = 30;
//const int VERYRARE_PROBABILITY = 20;
//const int EPIC_PROBABILITY = 10;
//const int LEGENDARY_PROBABILITY = 0;	//�޷�ͨ��������/�̵���
//#pragma endregion

//��Ʒ����Ʒ���ָ���
//���ʼ���Ӧ�����մ�ϡ�е���ͨ���μ���
//ÿ�����ʲ���Ϊ���ֵĸ��ʣ������ڵ��μ��������ɵĸ���
//Ҳ����˵��uncommon�Ľ������5��
enum ItemProbability
{
	LEGENDARY = 0,		//�޷�ͨ��������/�̵���
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
	int GetRarity();
protected:
	virtual bool init();
private:
	int _id;
	int _value;
	int _rarity;
	static constexpr double _physicalRange = 80.0;
};
#endif // !__ITEMS_H__
