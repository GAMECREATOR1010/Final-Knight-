#include "Room.h"
USING_NS_CC;

Room* Room::create(int  wid, int hei, int rType, int rTheme, Vec2 roomPos)
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

void Room::drawRoom()
{
	for (float x = 15 - width / 2; x < 18 + width / 2; x++)
	{
		for (float y = 15 - height / 2; y < 18 + height / 2; y++)
		{
			if (((x == 15 - width / 2 || x == 18 + width / 2 - 1) && y >= 15 - height / 2 && y < 18 + height / 2)
				|| ((y == 15 - height / 2 || y == 18 + height / 2 - 1)) && x >= 15 - width / 2 && x < 18 + width / 2)
			{
				drawWall(x, y);
			}
			else
			{
				drawFloor(x, y);
			}
		}
	}

}

void Room::drawFloor(float x, float y)
{
	unsigned int gid;
	gid = rand() % 5 + 6 + roomTheme * 10;
	floor->setTileGID(gid, Vec2(x, y));
}

void Room::drawWall(float x, float y, bool flag)
{
	unsigned int gid;
	gid = 2 * (rand() % 2) + 2 + roomTheme * 10;
	wall->setTileGID(gid, Vec2(x, y));
	meta->setTileGID(41, Vec2(x, y));
	if (flag)
	{
		gid += 1;
		shade->setTileGID(gid, Vec2(x, y + 1));
	}
}

void Room::drawPassage()
{
	for (float x = 13; x < 20; x++)
	{
		if (doorUp)
		{
			for (float y = 0; y <= 15 - height / 2; y++)
			{
				if (x == 13 || x == 19)
					drawWall(x, y);
				else
					drawFloor(x, y);
			}
		}
		if (doorDown)
		{
			for (float y = 17 + height / 2; y < 33; y++)
			{
				if (x == 13 || x == 19)
					drawWall(x, y, false);
				else
					drawFloor(x, y);
			}
		}
	}
	for (float y = 12; y < 20; y++)
	{
		if (doorLeft)
		{
			for (float x = 0; x <= 15 - width / 2; x++)
			{
				if (y == 12 || y == 19)
					drawWall(x, y);
				else
					drawFloor(x, y);
			}
		}
		if (doorRight)
		{
			for (float x = 17 + width / 2; x < 33; x++)
			{
				if (y == 12 || y == 19)
					drawWall(x, y);
				else
					drawFloor(x, y);
			}
		}
	}
}

void Room::drawDoor(float x,float y)
{
	wall->setTileGID(31, Vec2(x, y));
	shade->setTileGID(31, Vec2(x, y + 1));
	if (doorOpen)
	{
		wall->setTileGID(21, Vec2(x, y));
		meta->setTileGID(31, Vec2(x, y));
	}
	else
	{
		shade->setTileGID(11, Vec2(x, y+1));
		meta->setTileGID(41, Vec2(x, y));
		wall->setTileGID(1, Vec2(x, y ));
	}
}

void Room::updateDoor()
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
			drawDoor(x, y);
		}
		if (doorDown)
		{
			float y = 17 + height / 2;
			drawDoor(x, y);
		}
	}
	for (float y = 14; y < 19; y++)
	{
		if (doorLeft)
		{
			float x = 15 - height / 2;
			drawDoor(x, y);
		}
		if (doorRight)
		{
			float x = 17 + height / 2;
			drawDoor(x, y);
		}
	}
}

void Room::drawObstacles(float x, float y)
{
	wall->setTileGID(55, Vec2(x, y));
	meta->setTileGID(55, Vec2(x, y));
	shade->setTileGID(56, Vec2(x, y+1));
}

void Room::updateObstacles()
{
	if (roomType == 1)
	{
		int i = rand() % 3;
		if (i == 0)
		{
			float x =12-rand()%2;
			int hei =  height - 3-rand()%3;
			for (float y = 16 - height / 2; y < 16 - height / 2+hei; y++)
			{
				drawObstacles(x, y);
			}

			 x =rand() % 2 + 19;
			for (float y = 17 + height / 2-hei; y < 17 + height / 2; y++)
			{
				drawObstacles(x, y);
			}
		}
		else if (i == 1)
		{
			for (int k = 0; k<4; k++)
			{
				int x = rand() % (width - 3) + 17 - width / 2;
				int y= rand() % (height - 3) + 17 - height/ 2;
				for (int m = 0; m < 2; m++)
				{
					for (int n = 0; n < 2; n++)
					{
						drawObstacles(x+m, y+n);
					}
				}
			}
		}
		
	}
}


bool Room::Ifnear(Vec2 pos)
{
	if (pos==roomPosition)
		return true;
	return false;
}


//rType=0为起始房间，rType=1为正常房，有敌人
bool Room::init(int wid, int hei, int rType, int rTheme, Vec2 roomPos)
{
	roomType = rType;
	roomTheme = rTheme;
	width = wid;
	height = hei;
	if (rType == 1)
	{
		enemyCount = rand() % 4 + 5;
	}
	else
		enemyCount = 0;
	playerEnter = false;
	doorUp = false, doorDown = false, doorLeft = false, doorRight = false;
	doorNum = 0;
	roomPosition = roomPos;
	roomMap = TMXTiledMap::create("room.tmx");
	meta = roomMap->getLayer("meta");
	floor = roomMap->getLayer("floor");
	shade = roomMap->getLayer("shade");
	wall = roomMap->getLayer("wall");
	obstacles = roomMap->getLayer("obstacles");
	drawRoom();
	addChild(roomMap);

	return true;
}



