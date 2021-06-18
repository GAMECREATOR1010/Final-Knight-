#pragma once
#ifndef __BATTLEMAP_H__
#define __BATTLEMAP_H__

#include "cocos2d.h"
#include "Room.h"
#include "Actor.h"
#include "Enemy.h"
#include "Knight.h"

USING_NS_CC;
class BattleMap :public cocos2d::Node
{
    friend class Gaming;
public:
    static  BattleMap* create(int chapter, roomThemeEnum rTheme,Knight* target);
    Vector<Room*> rooms;
    Vector<Room*> farRoom;
    Vector<Room*> oneDoorRoom;
    int chapter = 1;
    Knight* targetKnight;
    Room* InRoom(Vec2 position);
    void AddThings(Room* inRoom);
private:
    virtual bool init(int chapter, roomThemeEnum rTheme, Knight* target);
    roomThemeEnum roomTheme;
    int roomNumber;
    Room* endRoom;
    float maxDistance;
};

#endif 