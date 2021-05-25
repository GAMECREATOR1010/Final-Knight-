#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "Item.h"

USING_NS_CC;

class Bullet :public Item
{
public:
    static Bullet* create(int bulletType );
    
private:
    virtual bool init(int bulletType);
    float damage;
    float speed;
    //Vec2 movement;
    PhysicsBody* trigger;//��ײ��⹥��
    void ShowEffect(int bulletType);//ײ��Ч��
    void RemoveBullet();
};

#endif 
