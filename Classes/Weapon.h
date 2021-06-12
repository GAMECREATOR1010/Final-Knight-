#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"
#include "Bullet.h"

USING_NS_CC;

/* �������һ�������Ķ��� */
Weapon* RandomWeaponCreate();

class Weapon :public Item
{
public:
	static Weapon* create(int id = 0, int cate = KnightCate);
	void GenerateBullet(Vec2 faceDir);
	void MeleeAttack(Vec2 faceDir);
	void WeaponAttack(Vec2 faceDir);

	void SetSpeedBuff(float speedBuff);
	void SetRangeBuff(float rangeBuff);
	void SetDamageBuff(float damageBuff);

private:
	attackModeEnum attackMode;
	int costEnergy;
	int bulletType;
	int belongCate;
	int countPerTime = 12;
	//�Դ������ٶȣ���Χ���˺�ֵ
	float speed;
	float range = 1;
	float damege;
	//������Լӳ�
	float speedBuff = 0;
	float rangeBuff = 0;
	float damageBuff = 0;

	virtual bool init(int id = 0, int cate = KnightCate);

	Sequence* meleeAttack;
	Sprite* attackEffect;

	Vec2 bindPoint;
	Vec2 shotPoint;

	Vec2 meleeFacDir;
	float meleeStartRot;
	PhysicsBody* trigger;//������
};

#endif 