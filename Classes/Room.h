#pragma once
#ifndef __Room_H__
#define __Room_H__

#include "cocos2d.h"
#include "Const.h"


USING_NS_CC;
class Room :public cocos2d::Node
{
    friend class BattleMap;
    friend class Gaming;
    friend class Knight;
    friend class Actor;
public:
    static Room* create(int wid, int hei, roomTypeEnum rType, roomThemeEnum rTheme, Vec2 roomPos);
    void DrawRoom();
    void DrawPassage();
    void DrawDoor(float, float);
    void DrawFloor(float, float, bool = true);
    void DrawWall(float, float, bool = true, bool = true);
    void DrawObstacles(float, float,bool);
    void AddThing(float, float,float, float);
    void DeleteObstacles(float, float);
    void UpdateObstacles();
    void UpdateDoor();
    bool Movable(Vec2, unsigned int, bool = true);
    void UpdatePlayerEnter(Vec2 );
    Vec2 roomPosition;
    bool Ifnear(Vec2);
    bool playerEnter = false;

private:
    virtual bool init(int wid, int hei, roomTypeEnum rType, roomThemeEnum rTheme, Vec2 roomPos);
    roomThemeEnum roomTheme;
    roomTypeEnum roomType;
    TMXTiledMap* roomMap;
    TMXLayer* meta;
    TMXLayer* floor;
    TMXLayer* shade;
    TMXLayer* wall;
    TMXLayer* obstacles;
    TMXLayer* enemyPos;

    int width, height;
    float distance;

    int enemyCount = 0;

    bool doorOpen = true;
    bool doorUp = false, doorDown = false, doorLeft = false, doorRight = false;
    int doorNum = 0;
};

#endif 