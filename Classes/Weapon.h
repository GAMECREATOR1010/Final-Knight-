#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"
#include "Bullet.h"
#include "Room.h"

USING_NS_CC;

Weapon* RandomWeaponCreate();

class Weapon :public Item
{
	friend class Enemy;
	friend class Knight;
	friend class Actor;
public:
	static Weapon* create(int id = 0, int cate = KnightCate);
	void GenerateBullet(Vec2 faceDir, Room* inRoom, Vec2 pos);
	void MeleeAttack(Vec2 faceDir);
	void WeaponAttack(Vec2 faceDir, Room* inRoom, Vec2 pos);

	void SetSpeed(float sChange);
	void SetRange(float rChange);
	void SetDamage(float dChange);
	void SetDistance(float dChange);

	void SetSpeedBuff(float sBuff);
	void SetRangeBuff(float rBuff);
	void SetDamageBuff(float dBuff);
	void SetDistanceBuff(float dBuff);

	void AddBullet(float addBullet);
	float GetDamage();
	PhysicsBody* trigger;//捡起检测

private:
	virtual bool init(int id = 0, int cate = KnightCate);
	attackModeEnum attackMode;
	int costEnergy = 0;
	int bulletType = 0;
	int belongCate = KnightCate;
	int countPerTime = 1;
	//自带攻击速度，范围，伤害值
	float speed = 1;
	float range = 1;
	float damage = 1;
	float distance = 1;
	//玩家属性加成
	float speedBuff = 0;
	float rangeBuff = 0;
	float damageBuff = 0;
	float distanceBuff = 0;

	Vec2 bindPoint;

	int ID = 0;
	float perTime = 0.5f;
	Sequence* meleeAttack;
	Sprite* attackEffect;

	Vec2 meleeFacDir;
	float  meleeStartRot;
};
static Weapon* weaponForever;
#endif 