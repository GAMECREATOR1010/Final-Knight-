#pragma once
#ifndef __ENEMY_H__
#define __EMEMY_H__

#include "Actor.h"
#include "Knight.h"
USING_NS_CC;

class Enemy :public Actor
{
	friend class Room;
public:
	Knight* target;
	static Enemy* create(int type = 0, bool ifBoss = false);
	void Movement();
	int GetEXP();
private:
	virtual bool init(int type = 0, bool ifBoss = false);
	float chaseDistance = 64 * 8;
	float attackDistance = 64 * 5;
	float attackDelayTime = 1.0f;/*¹¥»÷Ê±¼ä¼ä¸ô*/
	EnemyState state;
	int AddEXP = 3;
	float timeCount = 0;
};

#endif
