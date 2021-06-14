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

private:
    virtual bool init(int type=0, int rank=1);
    int energy=150;
    

};

#endif 
