#pragma once
#ifndef __Room_H__
#define __Room_H__

#include "cocos2d.h"
USING_NS_CC;
class Room :public cocos2d::Node
{
public:
    static Room* create(int wid, int hei, int rType, int rTheme,Vec2 roomPos);
    int enemyCount=0;
    bool playerEnter=false;
    bool doorOpen=true;
    bool doorUp= false, doorDown = false, doorLeft = false, doorRight = false;
    int distance;
    int doorNum=0;
    bool endRoom = false;
    void drawRoom();
    void drawPassage();
    void drawDoor(float, float);
    void drawFloor(float, float);
    void drawWall(float, float,bool=true);
    void drawObstacles(float, float);
    void updateObstacles();
    void updateDoor();
    TMXTiledMap* roomMap;
    TMXLayer* meta;
    TMXLayer* floor;
    TMXLayer* shade;
    TMXLayer* wall;
    TMXLayer* obstacles;
    Vec2 roomPosition;
    bool Ifnear(Vec2);
private:
    virtual bool init(int wid, int hei, int rType, int rTheme, Vec2 roomPos);
    int roomTheme;
    int roomType;
    int width, height;
   
    
};

#endif 