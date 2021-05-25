#pragma once
#ifndef __Room_H__
#define __Room_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;
class Room :public cocos2d::Node
{
    friend class BattleMap;
    friend class Enemy;
public:
    static Room* create(int wid, int hei, int rType, int rTheme, Vec2 roomPos);
    void DrawRoom();
    void DrawPassage();
    void DrawDoor(float, float);
    void DrawFloor(float, float, bool = true);
    void DrawWall(float, float, bool = true, bool = true);
    void DrawObstacles(float, float);
    void UpdateObstacles();
    void UpdateDoor();
    bool Movable(Vec2, unsigned int, bool = true);
    Vec2 roomPosition;
    bool Ifnear(Vec2);
    bool doorOpen = true;
    int width, height;
    int enemyCount = 0;
    bool playerEnter = false;
    bool doorUp = false, doorDown = false, doorLeft = false, doorRight = false;
    float distance;
    int doorNum = 0;
    bool endRoom ;

private:
    virtual bool init(int wid, int hei, int rType, int rTheme, Vec2 roomPos);
    int roomTheme;
    int roomType;
    TMXTiledMap* roomMap;
    TMXLayer* meta;
    TMXLayer* floor;
    TMXLayer* shade;
    TMXLayer* wall;
    TMXLayer* obstacles;
};

#endif 