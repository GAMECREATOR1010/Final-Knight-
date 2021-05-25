#pragma once
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;
class Actor :public Node
{
public:
    static Actor* create();
	
	~Actor();
	Actor();
protected:
	Sprite* pic;
	Sprite* weapon;
	Sprite* shade;
	int state;
	virtual bool init();
	void AddShade(const Vec2);
	float damage;
	float defence;
	float HP , maxHP ;
	int attackMode;
	int weaponId ;
	float attackSpeed ; 
	float moveSpeed; 
	bool death = false;
	Vec2 movement;
	Vec2 weaponPos;
	PhysicsBody* body;
	void DeathEffect();
	Action deathEffect;
	Action ghostAppear;
};

#endif 
