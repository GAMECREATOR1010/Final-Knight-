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
static const int roomFloorGid = 61;//enemy���ж���
static const int passageFloorGid = 31;
static const int doorOpenGid = 21;
static const int doorCloseGid = 1;
static const bool obstaclesNorm = true;

static const int offSet = 2112;

static const int knightTag = 1;
static const int enemyTag = 2;
static const int myAttackTag = 4;
static const int enemyAttackTag = 5;

static const int itemTag = 8;
static const int obstaclesNormTag = 9;
static const int obstaclesRemovableTag = 10;
static const int emptyTag = 11;
static const int hitAllActorTag = 13;
static const int lowerAllActorSpeadTag = 14;
static const int explosionTag = 15;
static const int myBulletTag = 16;
static const int enemyBulletTag = 17;

static const int shopkeeperTag = 40;

//��Ҫ����ҽ�������ƷTag>100
static const int chestTag = 119;
static const int statueTag = 120;
static const int potionChestTag = 121;
static const int potionGoodsTag = 122;
static const int potionBoughtGoodsTag = 123;
static const int weaponChestTag = 130;
static const int weaponGoodsTag = 131;
static const int weaponBoughtGoodsTag = 132;
static const int weaponGroundTag = 133;


static const int nextChapterTag = 200;




static const int MONEY_EVERY_ENEMY = 2;
static const int MONEY_EVERY_ROOM = 5;
static const double MONEY_LEVEL_MUTI = 1.4;
static const int MANA_EVERY_ROOM = 20;
static const double MANA_LEVEL_MUTI = 1.1;

static const bool DEBUG_CHEST_MODE = true;
static const bool DEBUG_ROOM_MODE = true;

static const int KnightCate = 1;
static const int EnemyCate = 2;
static const int ObstaclesCate = 3;
static const int ItemCate = 4;

//UI stuff

static const int BloodUIx = 82;
static const int BloodUIy = 15;
static const int BloodUIGap = 60;


static const float StopFramePre = 0.45f;

static const float  ButtonPre = 0.075f;
static const int ButtonWidthGap = 40;
static const int  ButtonHeightGap = 30;
static const int  ButtonWidthGapInStop = 10;
static const int ButtonHeightGapInStop = 90;
//UI stuff end
#include "cocos2d.h"

USING_NS_CC;
Vector<SpriteFrame*> GetAnim(const char*, int);
Vec2 ChangeDir();
void SetBody(PhysicsBody*, int);
Vec2 Rotate(Vec2 faceDir, float angle);

enum  attackModeEnum
{
    meleeEnum = 0, gunEnum, touchEnum/*�����������Ӵ�*/
};

enum  EnemyState
{
    EnemyIdle = 0/*��ֹ*/, EnemyWalk/*��ҽ���󼤻��ʼ����*/, EnemyChase/*׷��*/, EnemyAttack, EnemyAttacked, EnemyDeath
};

enum  KnightState
{
    KnightIdle = 0/*����*/, KnightAttack, KnightAttacked, KnightDeath
};


enum  roomTypeEnum
{
    startRoomEnum = 0, normalRoomEnum = 1, bossRoomEnum = 2, endRoomEnum = 3, ShopRoomEnum = 4, StatueRoomEnum = 5
};

enum roomThemeEnum
{
    iceTheme = 0, darkTheme = 1, techTheme = 2, forestTheme = 3, sandTheme = 4
};

#endif