#pragma once
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "General.h"

USING_NS_CC;
class Actor :public cocos2d::Node
{
public:
    static Actor* create();
private:
	virtual bool init();
	Sprite* actor;
	Sprite* weapon;
protected:
	int attack = 3;
	int HP =5, maxHP=5 ;
	int attackMode=0;
	int weaponId = 0;
	float attackSpeed = 0.0f; 
	float moveSpeed = 0.0f; 
	bool death = false;
};

#endif 
