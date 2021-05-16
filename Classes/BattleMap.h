#pragma once
#ifndef __BATTLEMAP_H__
#define __BATTLEMAP_H__

#include "General.h"
USING_NS_CC;
class BattleMap :public cocos2d::Node
{
public:
    static  BattleMap* create(int chapter, int rTheme);
    Vector<Room*> rooms;
    Room* InRoom(Vec2 position);
private:
    virtual bool init(int chapter, int rTheme);
    int roomTheme;
    int roomNumber;
    int chapter;
    
};

#endif 