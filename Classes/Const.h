#pragma once

#ifndef __CONST_H__
#define __CONST_H__

#define metaOrder 0
#define floorOrder 1
#define shadeOrder 2
#define wallOrder 3
#define obstaclesOrder 4

#define metaGid 41
#define roomFloorGid 61//enemy可行动处
#define passageFloorGid 31
#define doorOpenGid 21
#define doorCloseGid 1

#define offSet 2112

#define meleeMode 0
#define gunMode 1
#include "cocos2d.h"


USING_NS_CC;
Vector<SpriteFrame*> GetAnim(const char* format, int count);

enum EnemyState
{
    EnemyIdle = 0/*静止*/, EnemyWalk/*玩家进入后激活，开始乱走*/, EnemyChase/*追击*/, EnemyAttack, EnemyAttacked, EnemyDeath
};

enum KnightState
{
    KnightIdle = 0/*行走*/, KnightAttack, KnightAttacked, KnightDeath
};



#endif 