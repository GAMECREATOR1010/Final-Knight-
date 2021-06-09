#pragma once

#ifndef __CONST_H__
#define __CONST_H__

#define metaOrder 0
#define floorOrder 1
#define shadeOrder 2
#define wallOrder 3
#define obstaclesOrder 4
#define uiOrder 5 


#define metaGid 41
#define roomFloorGid 61//enemy可行动处
#define passageFloorGid 31
#define doorOpenGid 21
#define doorCloseGid 1

#define offSet 2112


#define knightTag 1
#define enemyTag 2
#define weaponTag 3
#define myAttack 4
#define enemyAttack 5
#define itemTag 6

#define KnightCate 1
#define EnemyCate 2
#define ObstaclesCate 3
#define ItemCate 4

#define faceRight 1
#define faceLeft 2
#define faceUp 3
#define faceDown 4

#include "cocos2d.h"


USING_NS_CC;
Vector<SpriteFrame*> GetAnim(const char* , int );
Vec2 ChangeDir();
void SetBody(PhysicsBody*,int);

enum  attackModeEnum
{
    meleeEnum= 0, gunEnum,touchEnum/*无武器，靠接触*/
};

enum  EnemyState
{
    EnemyIdle = 0/*静止*/, EnemyWalk/*玩家进入后激活，开始乱走*/, EnemyChase/*追击*/, EnemyAttack, EnemyAttacked, EnemyDeath
};

enum  KnightState
{
    KnightIdle = 0/*行走*/, KnightAttack, KnightAttacked, KnightDeath
};

/*enum  WeaponState
{
    WeaponIdle = 0/*静止, WeaponUsing
};*/


enum  roomTypeEnum
{
    startRoomEnum=0,normalRoomEnum=1,bonusRoomEnum=2,sacrificeRoomEnum=3,bossRoomEnum=4,endRoomEnum =5
};

enum roomThemeEnum
{
    iceTheme = 0, darkTheme=1, techTheme=2,forestTheme=3,sandTheme =4
};

#endif 