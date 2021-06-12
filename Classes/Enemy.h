#pragma once
#ifndef __ENEMY_H__
#define __EMEMY_H__

#include "General.h"
USING_NS_CC;

class Enemy :public Actor
{
public:
	static Enemy* create(int type = 0, bool ifBoss = true);

private:
	virtual bool init(int type = 0, bool ifBoss = true);
	float chaseDistance;
	float attackDistance;
	float attackDelayTime;/*¹¥»÷Ê±¼ä¼ä¸ô*/
	float touchDamage;
	Room* inRoom;
	EnemyState state;
};

#endif
