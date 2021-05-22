#include "BattleMap.h"
USING_NS_CC;

BattleMap* BattleMap::create(int chapter, int rTheme)
{
	BattleMap* battleMap = new BattleMap;
	if (battleMap != nullptr && battleMap->init(chapter, rTheme))
	{
		battleMap->autorelease();
		return battleMap;
	}
	CC_SAFE_DELETE(battleMap);
	return nullptr;
}

bool BattleMap::init(int cha, int rTheme)
{
	roomTheme = rTheme;
	chapter = cha;
	if (chapter <= 4)
	{
		roomNumber = rand() % 1 + 5;
	}
	else
		roomNumber = rand() % 2 + 6;

	float offSet = 2112;
	Vec2 genPoint = Vec2(0, 0);
	bool first = true, flag = false;
	int wid = 12, hei = 12;

	for (int i = 0; i < roomNumber; i++)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			Vec2 tempPos = ChangeDir() * offSet + genPoint;
			for (auto tempR : rooms)
			{
				Vec2 pos = tempR->getPosition();
				if (tempPos == pos)
				{
					flag = true;
					break;
				}
				else
					flag = false;
			}
			if (flag)
			{
				i--;
				continue;
			}
			genPoint = tempPos;
			wid = (rand() % 4) * 2 + 12;
			hei = (rand() % 4) * 2 + 12;
		}

		Room* tempRoom = Room::create(wid, hei, 1, roomTheme, genPoint);
		addChild(tempRoom);
		tempRoom->setPosition(genPoint);
		tempRoom->distance = genPoint.x / offSet + genPoint.y / offSet;
		rooms.pushBack(tempRoom);
	}

	for (auto temp1 : rooms)
	{
		Vec2 pos = temp1->getPosition();
		for (auto temp2 : rooms)
		{
			if (temp2->distance >= temp1->distance)
			{
			}
			if (temp2->Ifnear(pos + Vec2(0, offSet)))
			{
				temp1->doorUp = true;
				temp1->doorNum++;
			}
			if (temp2->Ifnear(pos - Vec2(0, offSet)))
			{
				temp1->doorDown = true;
				temp1->doorNum++;
			}

			if (temp2->Ifnear(pos + Vec2(offSet, 0)))
			{
				temp1->doorRight = true;
				temp1->doorNum++;
			}
			if (temp2->Ifnear(pos - Vec2(offSet, 0)))
			{
				temp1->doorLeft = true;
				temp1->doorNum++;
			}
			if (temp1->doorNum >= 4)
				break;
		}
		temp1->DrawPassage();
		temp1->UpdateDoor();
		temp1->UpdateObstacles();
	}

	return true;
}

Room* BattleMap::InRoom(Vec2 pos)
{
	for (auto tempR : rooms)
	{
		Vec2 roomPos = tempR->roomPosition + this->getPosition();
		if (pos.x - roomPos.x <= 2112 && pos.y - roomPos.y <= 2112 && pos.x - roomPos.x >= 0 && pos.y - roomPos.y >= 0)
		{
			return tempR;
			break;
		}
	}
	return nullptr;
}