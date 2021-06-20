#pragma once
#ifndef __BATTLEMAP_H__
#define __BATTLEMAP_H__

#include "cocos2d.h"
#include "RoomAndMap/Room.h"
#include "PlayerAndMonster/Actor.h"
#include "PlayerAndMonster/Enemy.h"
#include "PlayerAndMonster/Knight.h"
#include "RoomAndMap/Shop.h"
#include "RoomAndMap/Statue.h"

USING_NS_CC;
class BattleMap :public cocos2d::Node
{
	friend class Gaming;
public:
	static  BattleMap* create(int chapter, roomThemeEnum rTheme, Knight* target);
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