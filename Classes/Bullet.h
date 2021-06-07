#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "Item.h"

USING_NS_CC;

class Bullet :public Item
{
    friend class Weapon;
public:
    static Bullet* create(int bulletType, Vec2 dir,int cate = KnightCate, float range=1, float damage=1,float delayTime=1.0);
    void ShowEffect();
private:
    virtual bool init(int bulletType, Vec2 dir,  int cate=KnightCate,  float range = 1,float damage=1, float delayTime = 1.0);
    float damage;
    float range;
    int type;
    PhysicsBody* trigger;//Åö×²¼ì²â¹¥»÷
   //×²»÷Ð§¹û
};

#endif 
