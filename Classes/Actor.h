#pragma once
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "Room.h"
#include "cocos2d.h"
#include "Const.h"
#include "Weapon.h"

USING_NS_CC;
class Actor :public Node
{
public:
	static Actor* create();
	void Behit(float otherDam);
	void DeathEffect();
	void AddShade(const Vec2);
	void BindWea(Weapon*);
	float GetDamage();
	void BindRoom(Room*);
	Room* GetRoom();
	Weapon* GetWea();
	Vec2 faceDir = Vec2(0, 1);
	bool death = false;
	~Actor();
	Actor();
protected:
	Sprite* pic;
	Weapon* wea;
	Sprite* shade;
	Sprite* ghost;
	Room* inRoom;

	virtual bool init();
	attackModeEnum attackMode = gunEnum;
	float attackSpeed = 3;
	float moveSpeed = 5;
	float attackRange = 1;

	float damage = 1;//Ω”¥•…À∫¶
	float defence = 2;
	float HP = 5, maxHP = 5;

	int weaponId = 0;
	PhysicsBody* body;
};

#endif
