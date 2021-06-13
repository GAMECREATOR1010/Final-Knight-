/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为Money货币类，派生出局内金币，局外蓝币

 需要外部接口

 需要外部全局宏定义
 * 存档路径PATH

 To Do list:
 * 打死敌人随机掉落金币 响应：怪物死亡；输入：敌人等级、总体难度、关卡层数；输出：金币随机增加(当然也可能不增加）
 * 精英怪死了必掉
 * 开启宝箱随机掉落金币/道具 响应：宝箱开启；输入：总体难度、关卡层数；输出：金币随机增加/道具增加
 ****************************************************************************/
#pragma once

#ifndef __MONEY_H__
#define __MONEY_H__

#include "cocos2d.h"
USING_NS_CC;

// 金钱账户,抽象基类
class Money :public Sprite
{
public:
	//获取金额
	static int GetBalance();
	//设置余额
	static void SetBalance(int setValue);
	//改变余额
	static bool ChangeBalance(int changeValue);
private:
	static int _balance;
	virtual bool init() = 0;
};

// 局内金币账户，继承自Money
class GoldMoney :public Money
{
public:
	CREATE_FUNC(GoldMoney)
private:
	virtual bool init();
	virtual bool init(int);
};

// 局外蓝币账户，继承自Money
class BlueMoney : public Money
{
public:
	CREATE_FUNC(BlueMoney)
private:
	virtual bool init();
	virtual bool init(int);
};

#endif // !__MONEY_H__
