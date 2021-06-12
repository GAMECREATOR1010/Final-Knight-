#pragma once
#ifndef __BATTLEMAP_H__
#define __BATTLEMAP_H__

#include "General.h"
USING_NS_CC;
class BattleMap :public cocos2d::Node
{
public:
	static  BattleMap* create(int chapter, roomThemeEnum rTheme);
	Vector<Room*> rooms;
	Vector<Room*> farRoom;
	Vector<Room*> oneDoorRoom;
	Room* InRoom(Vec2 position);
private:
	virtual bool init(int chapter, roomThemeEnum rTheme);
	roomThemeEnum roomTheme;
	int roomNumber;
	int chapter;
	Room* endRoom;
	float maxDistance;
};

#endif 