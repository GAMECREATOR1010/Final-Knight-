#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

USING_NS_CC;
class Weapon :public Item
{
public:
    static Weapon* create(int id = 0);
    void GenerateBullet();
    void MeleeStart();
    void MeleeEnd();
private:
    virtual bool init(int id = 0);
    int bulletType;
    int attackMode;
    int costEnergy;
    Point shotPoint;
    PhysicsBody* trigger;//¼ñÆð¼ì²â
    PhysicsBody* meleeEffect;//½üÕ½¹¥»÷·¶Î§
};

#endif 