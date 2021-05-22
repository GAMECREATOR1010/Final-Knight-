#pragma once
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

USING_NS_CC;
class Actor :public Node
{
	friend class Knight;
public:
    static Actor* create();
	Sprite* pic;
	Sprite* weapon;
	Sprite* shade;
	~Actor();
protected:
	virtual bool init();
	void AddShade(const Vec2);
	int damage;
	int defence;
	int HP , maxHP ;
	int attackMode;
	int weaponId ;
	float attackSpeed ; 
	float moveSpeed; 
	bool death = false;
	Vec2 movement;
};

#endif 
