#pragma once

#ifndef __CONST_H__
#define __CONST_H__

static const int metaOrder = 0;
static const int floorOrder = 1;
static const int shadeOrder = 2;
static const int knightOrder = 3;
static const int wallOrder = 4;
static const int obstaclesOrder = 5;
static const int uiOrder = 6;


static const int metaGid = 41;
static const int roomFloorGid = 61;//enemy可行动处
static const int passageFloorGid = 31;
static const int doorOpenGid = 21;
static const int doorCloseGid = 1;
static const bool obstaclesNorm = true;

static const int offSet = 2112;

static const int knightTag = 1;
static const int enemyTag = 2;
static const int weaponTag = 3;
static const int myAttackTag = 4;
static const int enemyAttackTag = 5;

static const int itemTag = 8;
static const int obstaclesNormTag = 9;
static const int obstaclesRemovableTag = 10;
static const int emptyTag = 11;
static const int nextChapterTag = 12;
static const int hitAllActorTag = 13;
static const int lowerAllActorSpeadTag = 14;
static const int explosionTag = 15;
static const int myBulletTag = 16;
static const int enemyBulletTag = 17;

static const int chestTag = 19;
static const int statueTag = 20;
static const int potionChestTag = 21;
static const int potionGoodsTag = 22;
static const int weaponChestTag = 23;
static const int weaponGoodsTag = 24;


static const int shopkeeperTag = 40;


static const int MONEY_EVERY_ENEMY = 2;
static const int MONEY_EVERY_ROOM = 5;
static const double MONEY_LEVEL_MUTI = 1.4;
static const int MANA_EVERY_ROOM = 20;
static const double MANA_LEVEL_MUTI = 1.1;

static const bool DEBUG_CHEST_MODE = true;

static const int KnightCate = 1;
static const int EnemyCate = 2;
static const int ObstaclesCate = 3;
static const int ItemCate = 4;

//UI stuff
#define stopButtonOrder 800
#define stopLayerOrder  850
#define stopLayerStuffOrder  900
#define infoLayerOrder       950
#define infoLayerStuffOrder  999

#define StopFramePre     0.45f

#define ButtonPre    0.075f
#define ButtonWidthGap   40
#define ButtonHeightGap  30
#define ButtonWidthGapInStop   10
#define ButtonHeightGapInStop  90
//UI stuff end
#include "cocos2d.h"

USING_NS_CC;
Vector<SpriteFrame*> GetAnim(const char* , int );
Vec2 ChangeDir();
void SetBody(PhysicsBody*,int);
Vec2 Rotate(Vec2 faceDir, float angle);

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


enum  roomTypeEnum
{
    startRoomEnum=0,normalRoomEnum=1,bonusRoomEnum=2,sacrificeRoomEnum=3,bossRoomEnum=4,endRoomEnum =5, ShopRoomEnum=10,StatueRoomEnum=11
};

enum roomThemeEnum
{
    iceTheme = 0, darkTheme=1, techTheme=2,forestTheme=3,sandTheme =4
};

#endif