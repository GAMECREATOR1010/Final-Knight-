#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "Actor.h"
#include "Const.h"

USING_NS_CC;



class Knight :public Actor
{
public:
    static Knight* create(int type=0,int rank=1);
    
private:
    virtual bool init(int type=0, int rank=1);
    int energy;
    

};

#endif 
