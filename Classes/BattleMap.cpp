#include "BattleMap.h"
USING_NS_CC;

BattleMap* BattleMap::create(int chapter, roomThemeEnum rTheme,  Knight* target)
{
	BattleMap* battleMap = new BattleMap;
	if (battleMap != nullptr && battleMap->init(chapter, rTheme,target))
	{
		battleMap->autorelease();
		return battleMap;
	}
	CC_SAFE_DELETE(battleMap);
	return nullptr;
}


bool BattleMap::init(int cha, roomThemeEnum rTheme, Knight* target)
{
	AddRoom(cha,rTheme, target,this);

	return true;
}

void BattleMap::Test()
{
	auto sprit = Sprite::create("tileSet.png");
	sprit->setGlobalZOrder(shadeOrder);
	endRoom -> addChild(sprit);
}

void BattleMap::AddRoom(int cha, roomThemeEnum rTheme, Knight* target,BattleMap* battlemap)
{
	battlemap->targetKnight = target;
	battlemap->roomTheme = rTheme;
	battlemap->chapter = cha;
	if (battlemap->chapter <= 4)
	{
		battlemap->roomNumber = 7;
	}
	else
		battlemap->roomNumber = rand() % 3 + 8;

	Vec2 genPoint = Vec2(0, 0);
	Vec2 dirOne = ChangeDir(), dirNext = dirOne;
	bool first = true, flag = false;
	int wid = 12, hei = 12;
	battlemap->maxDistance = 0;
	roomTypeEnum type = startRoomEnum;
	for (int i = 0; i < battlemap->roomNumber; i++)/*生成房间*/
	{
		if (!first)
		{
			while (true)
			{
				if (dirOne == dirNext)
				{
					dirOne = ChangeDir();
					continue;
				}
				else
				{
					dirNext = dirOne;
					break;
				}
			}

			Vec2 tempPos = dirOne * offSet + genPoint;
			for (auto tempR : battlemap->rooms)
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

		if (first)
		{
			first = false;
		}
		else
		{
			type = normalRoomEnum;//待修改
		}

		Room* tempRoom = Room::create(wid, hei, type, battlemap->roomTheme, genPoint);
		first = false;
		battlemap->addChild(tempRoom);
		tempRoom->setPosition(genPoint);
		tempRoom->distance = abs(genPoint.x / offSet) + abs(genPoint.y / offSet);
		if (tempRoom->distance > battlemap->maxDistance)
			battlemap->maxDistance = tempRoom->distance;
		battlemap->rooms.pushBack(tempRoom);
	}


	for (auto temp1 : battlemap->rooms)/*连接各房间，找到距离较远的房间*/
	{
		Vec2 pos = temp1->getPosition();
		for (auto temp2 : battlemap->rooms)
		{
			if (temp2->distance > temp1->distance)
			{
				battlemap->maxDistance = temp2->distance;
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
		if (temp1->distance == battlemap->maxDistance && temp1->doorNum != 4)
			battlemap->farRoom.pushBack(temp1);
		temp1->DrawPassage();
		temp1->UpdateDoor();
	}


	Vec2 final = Vec2(0, 0);
	for (auto temp : battlemap->farRoom)//Find endRoom
	{
		if (temp->doorNum == 1)
		{
			battlemap->oneDoorRoom.pushBack(temp);
			break;
		}
	}

	if (battlemap->oneDoorRoom.size() != 0)
	{
		battlemap->endRoom = oneDoorRoom.front();
		battlemap->endRoom->roomType = endRoomEnum;
	}
	else
	{
		Vec2 final = Vec2(0, 0);
		bool doorU = false, doorD = false, doorL = false, doorR = false;
		if (!battlemap->farRoom.front()->doorUp)
		{
			doorD = true;
			final = Vec2(0, offSet);
			battlemap->farRoom.front()->doorUp = true;
		}
		else if (!battlemap->farRoom.front()->doorDown)
		{
			doorU = true;
			final = Vec2(0, -offSet);
			battlemap->farRoom.front()->doorDown = true;
		}
		else if (!battlemap->farRoom.front()->doorLeft)
		{
			doorR = true;
			final = Vec2(-offSet, 0);
			battlemap->farRoom.front()->doorLeft = true;
		}
		else if (!battlemap->farRoom.front()->doorRight)
		{
			doorL = true;
			final = Vec2(offSet, 0);
			battlemap->farRoom.front()->doorRight = true;
		}
		if (battlemap->chapter % 3 == 0)
		{
			wid = (rand() % 4) * 2 + 14;
			hei = (rand() % 4) * 2 + 14;
		}
		else
		{
			wid = (rand() % 4) * 2 + 10;
			hei = (rand() % 4) * 2 + 10;
		}

		Room* tempRoom = Room::create(wid, hei, endRoomEnum, battlemap->roomTheme, battlemap->farRoom.front()->roomPosition + final);

		tempRoom->doorUp = doorU;
		tempRoom->doorDown = doorD;
		tempRoom->doorLeft = doorL;
		tempRoom->doorRight = doorR;
		battlemap->addChild(tempRoom);
		tempRoom->setPosition(battlemap->farRoom.front()->roomPosition + final);
		tempRoom->DrawPassage();
		tempRoom->UpdateDoor();
		battlemap->farRoom.front()->DrawPassage();
		battlemap->farRoom.front()->UpdateDoor();
		tempRoom->roomType = endRoomEnum;
		battlemap->rooms.pushBack(tempRoom);
		battlemap->endRoom = tempRoom;
	}

	if (chapter % 3 == 0)//boss房放置
	{
		if (battlemap->endRoom->width > 14 && battlemap->endRoom->height > 14)
			battlemap->endRoom->roomType = bossRoomEnum;
	}

	for (auto temp : battlemap->rooms)
	{
		temp->UpdateObstacles();
		AddThings(temp);
	}
}


void BattleMap::AddThings(Room* inRoom)
{
	if (inRoom->roomType == startRoomEnum)
	{
		auto enemy1 = Enemy::create(0);
		enemy1->target = targetKnight;
		inRoom->addChild(enemy1);
		enemy1->setPosition(Vec2(offSet / 2, offSet / 2));
		enemy1->BindRoom(inRoom);
		inRoom->enemyCount = 1;
		Enemies.pushBack(enemy1);
	}
	else if(inRoom->roomType == normalRoomEnum)
	{
		/*int enemyType = random(0, 3);
		int i = 0;
		if (enemyType < 3)
			i = random(3, 7);
		else
			i = random(2, 5);
		inRoom->enemyCount = i;
		for (int j = 0; j < i; ++j)
		{
			int x =random(-inRoom->width/2+1,inRoom->width / 2-1);
			int y = random(-inRoom->height / 2+1, inRoom->height / 2-1);
			if (inRoom->Movable(Vec2((15 + x) * 64, offSet - (15 + y) * 64), roomFloorGid)&&
				(inRoom->enemyPos->getTileGIDAt(Vec2(15+x, 15+y)) == passageFloorGid))
			{
				inRoom->enemyPos->setTileGID(roomFloorGid, Vec2(15 + x, 15 + y));
				auto enemy = Enemy::create(enemyType);
				enemy->target = targetKnight;
				inRoom->addChild(enemy);
				enemy->setPosition(Vec2((15 + x)* 64, offSet - (15+y) * 64));
				enemy->BindRoom(inRoom);
			}
			else
			{
				--j;
			}
		}*/
	}
	else if(inRoom->roomType == endRoomEnum)
	{
		AddTransDoor(endRoom);
	}
}

void BattleMap::ClearBattleMap()
{
	this->removeAllChildrenWithCleanup(true);
	rooms.clear();
	farRoom.clear();
	oneDoorRoom.clear();
	Enemies.clear();
}


void BattleMap::AddTransDoor(Room* inRoom)
{
	auto frames = GetAnim("gate%02d.png", 8);
	auto transDoor = Sprite::createWithSpriteFrame(frames.front());
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	transDoor->runAction(RepeatForever::create(Animate::create(animation)));
	transDoor->setPhysicsBody(PhysicsBody::createBox(transDoor->getContentSize()));
	transDoor->setTag(nextChapterTag);
	SetBody(transDoor->getPhysicsBody(), ItemCate);
	transDoor->setGlobalZOrder(knightOrder);

	inRoom->addChild(transDoor);
	transDoor->setPosition(offSet / 2, offSet / 2);
	auto particleSystem = ParticleSystemQuad::create("gate/door.plist");
	inRoom->addChild(particleSystem);
	particleSystem->setGlobalZOrder(wallOrder);
	particleSystem->setPosition(transDoor->getPosition());
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


