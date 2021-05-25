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

	Vec2 genPoint = Vec2(0, 0);
	Vec2 dirOne = ChangeDir(), dirNext = dirOne;
	int countDir = 0;
	bool first = true, flag = false;
	int wid = 12, hei = 12;
	maxDistance = 0;
	for (int i = 0; i < roomNumber; i++)
	{
		if (first)
		{
			first = false;
		}
		else
		{//´ý¸ü¸Ä
			while (true)
			{
				if (dirOne == dirNext)
				{
					countDir++;
				}
				else
				{
					countDir = 0;
					dirNext = dirOne;
				}

				if (countDir > 0)
				{
					dirOne = ChangeDir();
					continue;
				}
				else
					break;
			}


			Vec2 tempPos = dirOne * offSet + genPoint;
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
		tempRoom->distance = abs(genPoint.x / offSet) + abs(genPoint.y / offSet);
		if (tempRoom->distance > maxDistance)
			maxDistance = tempRoom->distance;
		rooms.pushBack(tempRoom);
	}

	for (auto temp1 : rooms)
	{
		Vec2 pos = temp1->getPosition();
		for (auto temp2 : rooms)
		{
			if (temp2->distance > temp1->distance)
			{
				maxDistance = temp2->distance;
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
		if (temp1->distance == maxDistance && temp1->doorNum != 4)
			farRoom.pushBack(temp1);
		temp1->DrawPassage();
		temp1->UpdateDoor();
		
	}


	Vec2 final = Vec2(0, 0);
	for (auto temp : farRoom)
	{
		if (temp->doorNum == 1)
		{
			oneDoorRoom.pushBack(temp);
			break;
		}
	}

	if (oneDoorRoom.size() != 0)
	{
		endRoom = oneDoorRoom.front();
		endRoom->roomType = 0;
	}
	else
	{
		Vec2 final = Vec2(0, 0);
		bool doorU = false, doorD = false, doorL = false, doorR = false;
		if (!farRoom.front()->doorUp)
		{
			doorD = true;
			final = Vec2(0, offSet);
			farRoom.front()->doorUp = true;
		}
		else if (!farRoom.front()->doorDown)
		{
			doorU = true;
			final = Vec2(0, -offSet);
			farRoom.front()->doorDown = true;
		}
		else if (!farRoom.front()->doorLeft)
		{
			doorR = true;
			final = Vec2(-offSet, 0);
			farRoom.front()->doorLeft = true;
		}
		else if (!farRoom.front()->doorRight)
		{
			doorL = true;
			final = Vec2(offSet, 0);
			farRoom.front()->doorRight = true;
		}
		wid = (rand() % 4) * 2 + 10;
		hei = (rand() % 4) * 2 + 10;
		Room* tempRoom = Room::create(wid, hei, 0, roomTheme, farRoom.front()->roomPosition + final);
		tempRoom->doorUp = doorU;
		tempRoom->doorDown = doorD;
		tempRoom->doorLeft = doorL;
		tempRoom->doorRight = doorR;
		addChild(tempRoom);
		tempRoom->setPosition(farRoom.front()->roomPosition + final);
		tempRoom->UpdateDoor();
		tempRoom->DrawPassage();
		farRoom.front()->UpdateDoor();
		farRoom.front()->DrawPassage();
		rooms.pushBack(tempRoom);
		endRoom = tempRoom;
	}

	auto frames = GetAnim("gate%02d.png", 8);
	auto transDoor = Sprite::createWithSpriteFrame(frames.front());
	transDoor->setGlobalZOrder(shadeOrder);
	endRoom->addChild(transDoor);
	transDoor->setPosition(offSet/2, offSet / 2);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	transDoor->runAction(RepeatForever::create(Animate::create(animation)));

	for (auto temp : rooms)
	{
		temp->UpdateObstacles();
	}

	return true;
}

Room* BattleMap::InRoom(Vec2 pos)
{
	for (auto tempR : rooms)
	{
		Vec2 roomPos = tempR->roomPosition + this->getPosition();
		if (pos.x - roomPos.x <= offSet && pos.y - roomPos.y <= offSet && pos.x - roomPos.x >= 0 && pos.y - roomPos.y >= 0)
		{
			return tempR;
			break;
		}
	}
	return nullptr;
}



