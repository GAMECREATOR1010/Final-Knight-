#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "Actor.h"

USING_NS_CC;

class Knight :public Actor
{
public:
    static Knight* create(int type=0,int rank=1);
    KnightState state;
    void MyAttack();
    void LevelUp();
    void AddEXP(int);

    

    void HPNowChange(float,float continueTime= -1.0f);
    void HPMaxChange(float);

    void DefenceNowChange(float, float continueTime = -1.0f);
    void DefenceMaxChange(float);
  
    void MoveSpeedNowChange(float, float continueTime = -1.0f);
    void MoveSpeedMaxChange(float );

    void DamageNowChange(float, float continueTime = -1.0f);
    void DamageMaxChange(float);

    void AttackSpeedChange(float, float continueTime = -1.0f);
    void AttackSpeedMaxChange(float);

    void AttackRangeChange(float, float continueTime = -1.0f);
    void AttackRangeMaxChange(float);

    void AttackDistanceChange(float, float continueTime = -1.0f);
    void AttackDistanceMaxChange(float);

    void EnergyNowChange(float);
    void EnergyMaxChange(float);

    float GetEnergyNow();
    float GetEnergyMax();
    int  GetRank();

private:
    virtual bool init(int type=0, int rank=1);
    float  energyMax=150;
    float  energyNow=150;

    float tempHP, tempEnergy, tempDefence, tempMoveSpeed,tempDamage,
        tempAttackSpeed, tempAttackRange,  tempAttackDistance;

    int rank = 1;
    int EXP = 0;
};
static Knight* myKnightForever ;
#endif 
