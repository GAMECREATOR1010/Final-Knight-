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
	void ChangeWea();
	float GetDamage();
	float GetMoveSpeed();
	void BindRoom(Room* );
	Room* GetRoom();
	Weapon* GetWea();
	Vec2 faceDir=Vec2(0,1);
	bool death = false;
	~Actor();
	Actor();
protected:
    Sprite* pic;
	Weapon* wea;
	Weapon* wea1;
	Sprite* shade;
	Sprite* ghost;
	Room* inRoom;


	virtual bool init();
	attackModeEnum attackMode=gunEnum;
	float attackSpeed=3;
	float moveSpeed=20;
	float attackRange=1;

	float damage=2;//�Ӵ��˺�
	float defence=1;
	float HP=5 , maxHP=5 ;
	
	PhysicsBody* body;

};

#endif 
