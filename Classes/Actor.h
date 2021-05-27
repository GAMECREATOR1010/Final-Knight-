#pragma once
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Const.h"
#include "Weapon.h"

USING_NS_CC;
class Actor :public Node
{
public:
    static Actor* create();
	void DeathEffect();
	void bindWea(Weapon*);
	~Actor();
	Actor();
protected:
	Sequence* deathSequence;
	Sprite* pic;
	Weapon* wea;
	Sprite* shade;
	Sprite* ghost;
	int state;
	virtual bool init();
	void AddShade(const Vec2);
	float damage;
	float defence;
	float HP , maxHP ;
	attackModeEnum attackMode;
	int weaponId ;
	float attackSpeed ; 
	float moveSpeed; 
	bool death = false;
	Vec2 movement;
	Vec2 weaponPos;
	PhysicsBody* body;
	Action* fallDown;
	
};

#endif 
