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

	float GetHP();
	float GetHPMax();

	float GetDamage();
	float GetDamageMax();

	float GetDefence();
	float GetDefenceMax();

	float GetMoveSpeed();
	float GetMoveSpeedMax();

	float GetAttackRange();
	float GetAttackRangeMax();

	float GetAttackSpeed();
	float GetAttackSpeedMax();

	float GetAttackDistance();
	float GetAttackDistanceMax();


	void HPNowChange(float, float continueTime = -1.0f);
	void HPMaxChange(float);

	void DefenceNowChange(float, float continueTime = -1.0f);
	void DefenceMaxChange(float);

	void MoveSpeedNowChange(float, float continueTime = -1.0f);
	void MoveSpeedMaxChange(float);

	void DamageNowChange(float, float continueTime = -1.0f);
	void DamageMaxChange(float);

	void AttackSpeedChange(float, float continueTime = -1.0f);
	void AttackSpeedMaxChange(float);

	void AttackRangeChange(float, float continueTime = -1.0f);
	void AttackRangeMaxChange(float);

	void AttackDistanceChange(float, float continueTime = -1.0f);
	void AttackDistanceMaxChange(float);

	void InvincibleTimeChange(float, float continueTime = -1.0f);
	void InvincibleTimeMaxChange(float);

	void BindRoom(Room*);
	Room* GetRoom();

	void BindWea(Weapon*);
	void ChangeWea();
	Weapon* GetWea();
	Vec2 faceDir = Vec2(0, 1);
	bool death = false;
	~Actor();
	Actor();
protected:
	Sprite* pic;
	Weapon* wea;
	Weapon* wea1 = nullptr;
	Sprite* shade;
	Sprite* ghost = nullptr;
	Room* inRoom;


	virtual bool init();
	attackModeEnum attackMode = gunEnum;
	float attackSpeed = 1;
	float attackSpeedMax = 1;
	float moveSpeed = 20;
	float moveSpeedMax = 20;
	float attackRange = 1;
	float attackRangeMax = 1;
	float attackDistance = 1;
	float attackDistanceMax = 1;
	float invincibleTime =1.5f;//骑士专供无敌时间
	float invincibleTimeMax = 1.5f;

	float damage = 2;//接触伤害
	float damageMax = 2;
	float defence = 1;
	float defenceMax = 1;
	float HP = 5, HPMax = 5;

	float tempHP, tempEnergy, tempDefence, tempMoveSpeed, tempDamage,
		tempAttackSpeed, tempAttackRange, tempAttackDistance, tempInvincibleTime;
	PhysicsBody* body;

};

#endif 
