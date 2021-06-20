#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "Item.h"

USING_NS_CC;

class Bullet :public Item
{
	friend class Weapon;
public:
	static Bullet* create(int bulletType, Vec2 dir, int cate = KnightCate, float range = 1,
		float damage = 1, float speed = 1.0, float distance = 1.0f);
	void ShowEffect();
	void BulletDis();
	float damage;
	int belongCate;
private:
	virtual bool init(int bulletType, Vec2 dir, int cate = KnightCate, float range = 1,
		float damage = 1, float speed = 1.0, float distance = 1.0f);
	int type;
	PhysicsBody* trigger;//Åö×²¼ì²â¹¥»÷
	PhysicsBody* explosionEffect;
	Sprite* explosion;
	//×²»÷Ð§¹û
};

#endif
