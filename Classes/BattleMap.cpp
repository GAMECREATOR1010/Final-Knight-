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
	targetKnight = target;
	roomTheme = rTheme;
	chapter = cha;
	if (chapter <= 4)
	{
		roomNumber = 7;
	} else
		roomNumber = rand() % 3 + 8;

	Vec2 genPoint = Vec2(0, 0);
	Vec2 dirOne = ChangeDir(), dirNext = dirOne;
	bool first = true, flag = false;
	int wid = 12, hei = 12;
	maxDistance = 0;
	roomTypeEnum type = startRoomEnum;
	for (int i = 0; i < roomNumber; i++) { /*生成房间*/
		if (!first) {
			while (true) {
				if (dirOne == dirNext) {
					dirOne = ChangeDir();
					continue;
				} else {
					dirNext = dirOne;
					break;
				}
			}

			Vec2 tempPos = dirOne * offSet + genPoint;
			for (auto tempR : rooms) {
				Vec2 pos = tempR->getPosition();
				if (tempPos == pos) {
					flag = true;
					break;
				} else
					flag = false;
			}
			if (flag) {
				i--;
				continue;
			}
			genPoint = tempPos;
			wid = (rand() % 4) * 2 + 12;
			hei = (rand() % 4) * 2 + 12;
		}

		if (DEBUG_ROOM_MODE)
		{
			if (first)
			{
				first = false;
			}
			else if (i % 3 == 1)
			{
				type = ShopRoomEnum;
			}
			else if (i % 3 == 2)
			{
				type = StatueRoomEnum;
			}
			else
			{
				type = normalRoomEnum;//待修改
			}

		}
		else
		{
			if (first)
			{
				first = false;
			}
			else if (i == 3)
			{
				type = ShopRoomEnum;
			}
			else if (i == 4)
			{
				type = StatueRoomEnum;
			}
			else
			{
				type = normalRoomEnum;//待修改
			}
		}


		Room* tempRoom = Room::create(wid, hei, type, roomTheme, genPoint);
		first = false;
		addChild(tempRoom);
		tempRoom->setPosition(genPoint);
		tempRoom->distance = abs(genPoint.x / offSet) + abs(genPoint.y / offSet);
		if (tempRoom->distance > maxDistance)
			maxDistance = tempRoom->distance;
		rooms.pushBack(tempRoom);
	}


	for (auto temp1 : rooms) 
	{ /*连接各房间，找到距离较远的房间*/
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
	for (auto temp : farRoom) { //Find endRoom
		if (temp->doorNum == 1) 
		{
			oneDoorRoom.pushBack(temp);
			break;
		}
	}

	if (oneDoorRoom.size() != 0) 
	{
		endRoom = oneDoorRoom.front();
		endRoom->roomType = endRoomEnum;
	} else {
		Vec2 final = Vec2(0, 0);
		bool doorU = false, doorD = false, doorL = false, doorR = false;
		if (!farRoom.front()->doorUp) 
		{
			doorD = true;
			final = Vec2(0, offSet);
			farRoom.front()->doorUp = true;
		} else if (!farRoom.front()->doorDown) 
		{
			doorU = true;
			final = Vec2(0, -offSet);
			farRoom.front()->doorDown = true;
		} else if (!farRoom.front()->doorLeft) 
		{
			doorR = true;
			final = Vec2(-offSet, 0);
			farRoom.front()->doorLeft = true;
		} else if (!farRoom.front()->doorRight) 
		{
			doorL = true;
			final = Vec2(offSet, 0);
			farRoom.front()->doorRight = true;
		}
		if (chapter % 3 == 0) 
		{
			wid = (rand() % 4) * 2 + 14;
			hei = (rand() % 4) * 2 + 14;
		} 
		else 
		{
			wid = (rand() % 4) * 2 + 10;
			hei = (rand() % 4) * 2 + 10;
		}

		Room* tempRoom = Room::create(wid, hei, endRoomEnum, roomTheme, farRoom.front()->roomPosition + final);

		tempRoom->doorUp = doorU;
		tempRoom->doorDown = doorD;
		tempRoom->doorLeft = doorL;
		tempRoom->doorRight = doorR;
		addChild(tempRoom);
		tempRoom->setPosition(farRoom.front()->roomPosition + final);
		tempRoom->DrawPassage();
		tempRoom->UpdateDoor();
		farRoom.front()->DrawPassage();
		farRoom.front()->UpdateDoor();
		tempRoom->roomType = endRoomEnum;
		rooms.pushBack(tempRoom);
		endRoom = tempRoom;
	}

	if (chapter % 3 == 0) { //boss房放置
		if (endRoom->width > 14 && endRoom->height > 14)
			endRoom->roomType = bossRoomEnum;
	}

	for (auto temp : rooms) {
		temp->UpdateObstacles();
		AddThings(temp);
	}

	return true;
}


void BattleMap::AddThings(Room* inRoom) {
	roomTypeEnum rType = inRoom->roomType;
	switch (rType) {
		case startRoomEnum:
			break;
		case normalRoomEnum: {
			int enemyType = random(0, 4);
			int i = 0;
			if (enemyType < 2)
				i = random(3, 7);
			else if(enemyType==2) {
				i = random(5, 7);
			} else
				i = random(2, 3);

			i+=(chapter / 3) % 4;
			inRoom->enemyCount = i;

			for (int j = 0; j < i; ++j) {
				int x =random(-(inRoom->width-2)/2, (inRoom->width - 2) / 2);
				int y = random(-(inRoom->height - 2)/2, (inRoom->height - 2) / 2);
				if (inRoom->Movable(Vec2((15 + x) * 64, offSet - (15 + y) * 64), roomFloorGid)&&
				        (inRoom->enemyPos->getTileGIDAt(Vec2(15+x, 15+y)) == passageFloorGid)) {
					inRoom->enemyPos->setTileGID(roomFloorGid, Vec2(15 + x, 15 + y));
					auto enemy = Enemy::create(enemyType);
					enemy->target = targetKnight;
					inRoom->addChild(enemy);
					enemy->HPMaxChange(chapter/3);
					enemy->setPosition(Vec2((15 + x)* 64, offSet - (15+y) * 64));
					enemy->BindRoom(inRoom);
				} else {
					--j;
				}
			}
		}
		break;
		case bossRoomEnum:
			break;
		case endRoomEnum:
			inRoom->AddTransDoor();
			break;
		case ShopRoomEnum: {
			Shop shop;
			shop.InitGoods(chapter);

			/* 添加商人*/
			auto shopkeeper = shop.SetShopKeeper();
			shopkeeper->setPosition(Vec2(offSet / 2, offSet / 2+100));
			inRoom->addChild(shopkeeper);

			/* 添加商品 */
			for (int i = 0; i < MAX_GOODS; i++)
			{
				auto point = Vec2(offSet / 2 + (i - 1) * 250, offSet / 2 - 150);

				auto shelf = shop.shelfCreate();
				shelf->setPosition(point);
				inRoom->addChild(shelf);

				auto goods = shop.goodses[i].GetGoods();
				goods->setScale(1.5);
				goods->setPosition(point);
				inRoom->addChild(goods);
			}
		}
			break;
		case StatueRoomEnum:
		{
			auto sType = static_cast<StatueType>(random(0, static_cast<int>(STATUECOUNT) - 1));
			auto statue = Statue::create(sType);
			if (statue)
			{
				statue->setPosition(Vec2(offSet / 2, offSet / 2));
				inRoom->addChild(statue);
				inRoom->AddThing((offSet / 2 - 64*0.52)/ 64 , (offSet / 2+64*1)/ 64,2, 2.1);
				CCLOG("BattleMap::AddThings: Statue create succsee, type %d",sType);
			}
		}
		break;
		default:
			break;
	}

}


Room* BattleMap::InRoom(Vec2 pos) {
	for (auto tempR : rooms) {
		Vec2 roomPos = tempR->roomPosition + this->getPosition();
		if (pos.x - roomPos.x <= offSet && pos.y - roomPos.y <= offSet && pos.x - roomPos.x >= 0 && pos.y - roomPos.y >= 0) {
			return tempR;
			break;
		}
	}
	return nullptr;
}
