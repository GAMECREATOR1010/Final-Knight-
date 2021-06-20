#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "Actor.h"

USING_NS_CC;

class Knight :public Actor
{
public:
	static Knight* create(int type = 0, int rank = 1);
	KnightState state;
	void MyAttack();
	void LevelUp();
	void AddEXP(int);

	void EnergyNowChange(float);
	void EnergyMaxChange(float);

	float GetEnergyNow();
	float GetEnergyMax();
	int  GetRank();

	void LaunchSkillTime();

private:
	virtual bool init(int type = 0, int rank = 1);
	float  energyMax = 150;
	float  energyNow = 150;
	float  tempEnergy = 150;
	int rank = 1;
	int EXP = 0;
	int knightType = 0;
	float skillTime = 5.0f;
	float skillCostEnergy = 10;
	bool launchSkill = false;
	Sprite* diceSpriteOne;
	Sprite* diceSpriteTwo;
};
static Knight* myKnightForever;
#endif
