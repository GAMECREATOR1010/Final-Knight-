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
    void AddDefence(float addDefence);
    void AddMoveSpeed(float addMoveSpeed);
    void LevelUp();
    void AddEXP(int );
    void HPNowChange(float hpchange);
    void HPMaxChange(float hpchange);
    void EnergyMaxChange(float energychange);
    void EnergyNowChange(float energychange);
private:
    virtual bool init(int type=0, int rank=1);
    int energyMax=150;
    int energyNow=1000;
    int rank = 1;
    int EXP = 0;
};

#endif 
