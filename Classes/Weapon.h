#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

USING_NS_CC;
class Weapon :public Item
{
public:
    static Weapon* create(int id = 0,int cate=KnightCate);
    void GenerateBullet();
    void MeleeStart();
    void MeleeEnd();
private:
    virtual bool init(int id = 0,int cate= KnightCate);
    Sequence* meleeAttack;
    Sprite* attackEffect;
    int bulletType;
    attackModeEnum attackMode;
    int costEnergy;
    Vec2 bindPoint;
    float firstRotation;
    Point shotPoint;
    PhysicsBody* trigger;//¼ñÆð¼ì²â
    PhysicsBody* meleeEffect;//½üÕ½¹¥»÷·¶Î§
};

#endif 