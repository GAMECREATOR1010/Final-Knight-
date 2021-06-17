#include "Room.h"
USING_NS_CC;

Room* Room::create(int  wid, int hei, roomTypeEnum rType, roomThemeEnum rTheme, Vec2 roomPos)
{
	Room* room = new Room;
	if (room != nullptr && room->init(wid, hei, rType, rTheme, roomPos))
	{
		room->autorelease();
		return room;
	}
	CC_SAFE_DELETE(room);
	return nullptr;
}


void Room::DrawRoom()
{
	for (float x = 15- width / 2; x < 18 + width / 2; x++)
	{
		for (float y = 15 - height / 2; y < 18 + height / 2; y++)
		{
			if (((x == 15 - width / 2 || x == 18 + width / 2 - 1) && y >= 15 - height / 2 && y < 18 + height / 2)
				|| ((y == 15 - height / 2 || y == 18 + height / 2 - 1)) && x >= 15 - width / 2 && x < 18 + width / 2)
			{
				if (y == 15 - height / 2)
				{
					DrawWall(x, y, true, false);
				}
				else
					DrawWall(x, y);
			}
			else
			{
				DrawFloor(x, y, false);
			}
		}
	}

}

void Room::DrawFloor(float x, float y, bool flag)
{
	unsigned int gid;
	gid = rand() % 5 + 6 + roomTheme * 10;
	floor->setTileGID(gid, Vec2(x, y));
	if (!flag)
	{
		meta->setTileGID(roomFloorGid, Vec2(x, y));
	}
}

void Room::DrawWall(float x, float y, bool flag, bool shadow)
{
	unsigned int gid;
	gid = 2 * (rand() % 2) + 2 + roomTheme * 10;
	if (shadow)
	{
		wall->setTileGID(gid, Vec2(x, y));
	}
	else
		shade->setTileGID(gid, Vec2(x, y));

	meta->setTileGID(metaGid, Vec2(x, y));
	if (flag)
	{
		gid += 1;
		shade->setTileGID(gid, Vec2(x, y + 1));
	}
}

void Room::DrawPassage()
{
	for (float x = 13; x < 20; x++)
	{
		if (doorUp)
		{
			for (float y = 0; y <= 15 - height / 2; y++)
			{
				if (x == 13 || x == 19)
					DrawWall(x, y);
				else
					DrawFloor(x, y);
			}
		}
		if (doorDown)
		{
			for (float y = 17 + height / 2; y < 33; y++)
			{
				if (x == 13 || x == 19)
					DrawWall(x, y, false);
				else
					DrawFloor(x, y);
			}
		}
	}
	for (float y = 13; y < 20; y++)
	{
		if (doorLeft)
		{
			for (float x = 0; x <= 15 - width / 2; x++)
			{
				if (y == 13 || y == 19)
				{
					if (y == 13)
						DrawWall(x, y, true, false);
					else
						DrawWall(x, y);
				}
				else
					DrawFloor(x, y);
			}
		}
		if (doorRight)
		{
			for (float x = 17 + width / 2; x < 33; x++)
			{
				if (y == 13 || y == 19)
				{
					if (y == 13)
						DrawWall(x, y, true, false);
					else
						DrawWall(x, y);
				}
				else
					DrawFloor(x, y);
			}
		}
	}
}

void Room::DrawDoor(float x, float y)
{
	wall->setTileGID(passageFloorGid, Vec2(x, y));
	shade->setTileGID(passageFloorGid, Vec2(x, y + 1));
	meta->setTileGID(passageFloorGid, Vec2(x, y));
	if (doorOpen)
	{
		shade->setTileGID(doorOpenGid, Vec2(x, y));
		wall->setTileGID(passageFloorGid, Vec2(x, y - 1));
	}
	else
	{
		shade->setTileGID(doorCloseGid+10, Vec2(x, y ));
		meta->setTileGID(metaGid, Vec2(x, y ));
		wall->setTileGID(doorCloseGid, Vec2(x, y-1));
	}
}

void Room::UpdateDoor()
{
	if (!playerEnter || (playerEnter && enemyCount == 0))
		doorOpen = true;
	else
		doorOpen = false;

	for (float x = 14; x < 19; x++)
	{
		if (doorUp)
		{
			float y = 15 - height / 2;
			DrawDoor(x, y);
		}
		if (doorDown)
		{
			float y = 17 + height / 2;
			DrawDoor(x, y);
		}
	}
	for (float y = 14; y < 19; y++)
	{
		if (doorLeft)
		{
			float x = 15 - width / 2;
			DrawDoor(x, y);
		}
		if (doorRight)
		{
			float x = 17 + width / 2;
			DrawDoor(x, y);
		}
	}
}

void Room::AddThing(float x,float y,float hei,float wid)
{
	for (float i = x; i < x + wid; ++i)
	{
		for (float j = y; j < y + hei; ++j)
		{
			meta->setTileGID(metaGid, Vec2(i, j));
		}
	}
}

void Room::DrawObstacles(float x, float y,bool removable)
{
	obstacles->setTileGID(55, Vec2(x, y));
    meta->setTileGID(metaGid, Vec2(x, y));
	auto obstaclesbox = PhysicsBody::createBox(Size(64.0f, 64.0f));
	obstaclesbox->setDynamic(false);
	SetBody(obstaclesbox, ObstaclesCate);
	obstacles->getTileAt(Vec2(x, y))->addComponent(obstaclesbox);
	if(removable)
		obstacles->getTileAt(Vec2(x, y))->setTag(obstaclesRemovableTag);
	else
		obstacles->getTileAt(Vec2(x, y))->setTag(obstaclesNormTag);
	shade->setTileGID(56, Vec2(x, y + 1));
}

void Room::DeleteObstacles(float x, float y)
{
	meta->setTileGID(roomFloorGid, Vec2(x, y));
	obstacles->setTileGID(roomFloorGid, Vec2(x, y));
	shade->setTileGID(roomFloorGid, Vec2(x, y + 1));
	obstacles->getTileAt(Vec2(x, y))->setTag(emptyTag);
}

void Room::UpdateObstacles()//添加障碍物，后期会更改丰富
{
	if (roomType == normalRoomEnum)
	{
		int i = rand() % 3;
		if (i == 0)
		{
			float x = 13 - rand() % 2;
			int hei = height - 3 - rand() % 3;
			for (float y = 16 - height / 2; y < 16 - height / 2 + hei; y++)
			{
				DrawObstacles(x, y,true);
			}
			x = rand() % 2 + 19;
			for (float y = 17 + height / 2 - hei; y < 17 + height / 2; y++)
			{
				DrawObstacles(x, y, true);
			}
		}
		else if (i == 1)
		{
			for (int k = 0; k < 4; k++)
			{
				int x = rand() % (width - 3) + 17 - width / 2;
				int y = rand() % (height - 3) + 17 - height / 2;
				for (int m = 0; m < 2; m++)
				{
					for (int n = 0; n < 2; n++)
					{
						DrawObstacles(x + m, y + n, true);
					}
				}
			}
		}
	}
}

bool Room::Ifnear(Vec2 pos)
{
	if (pos == roomPosition)
		return true;
	return false;
}

bool Room::Movable(Vec2 pos, unsigned int gid, bool flag)//判断是否可行走
{
	unsigned int myGid = meta->getTileGIDAt(Vec2(int(pos.x / 64), int((offSet - pos.y) / 64)));
	if (flag)
	{
		if (myGid != gid)
		{
			return false;
		}
		else
			return true;
	}
	else
	{
		if (myGid != gid)
		{
			return true;
		}
		else
			return false;
	}
	return true;
}

void Room::UpdatePlayerEnter(Vec2 pos)
{
	if (pos.x >= offSet / 2 - width * 32 && pos.x <= offSet / 2 + width * 32
		&& pos.y >= offSet / 2 - height * 32 && pos.y <= offSet / 2 + height * 32)
	{
		playerEnter = true;
		UpdateDoor();
	}
}

//rType=0为起始房间/中止房间，rType=1为正常房，有敌人,
bool Room::init(int wid, int hei, roomTypeEnum rType, roomThemeEnum rTheme, Vec2 roomPos)
{
	roomType = rType;
	roomTheme = rTheme;
	width = wid;
	height = hei;
	if (rType == normalRoomEnum)
	{
		enemyCount = rand() % 4 + 5;
	}
	else
		enemyCount = 0;
	doorNum = 0;
	roomPosition = roomPos;
	roomMap = TMXTiledMap::create("room.tmx");
	meta = roomMap->getLayer("meta");
	meta->setGlobalZOrder(metaOrder);
	floor = roomMap->getLayer("floor");
	floor->setGlobalZOrder(floorOrder);
	shade = roomMap->getLayer("shade");
	shade->setGlobalZOrder(shadeOrder);
	wall = roomMap->getLayer("wall");
	wall->setGlobalZOrder(wallOrder);
	obstacles = roomMap->getLayer("obstacles");
	obstacles->setGlobalZOrder(obstaclesOrder);
	enemyPos= roomMap->getLayer("enemyPos");
	DrawRoom();
	addChild(roomMap);

	return true;
}

