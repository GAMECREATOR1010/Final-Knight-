#include "Gaming.h"
USING_NS_CC;

Scene* Gaming::createScene(Knight* myknight,  int Chapter)
{
	Gaming* gaming = new Gaming;
	if (gaming != nullptr && gaming->init(myknight, Chapter))
	{
		gaming->autorelease();
		return gaming;
	}
	CC_SAFE_DELETE(gaming);
	return nullptr;
	
}

bool Gaming::init(Knight* myknight, int Chapter)
{
	if (!Scene::init())
	{
		return false;
	}
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	srand((unsigned)time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("gate/gate.plist");
	spritecache->addSpriteFramesWithFile("obstacles/box.plist");
	spritecache->addSpriteFramesWithFile("enemy/enemy_0.plist");
	spritecache->addSpriteFramesWithFile("enemy/enemy_1.plist");
	spritecache->addSpriteFramesWithFile("enemy/enemy_2.plist");
	spritecache->addSpriteFramesWithFile("enemy/enemy_3.plist");
	spritecache->addSpriteFramesWithFile("enemy/enemy_4.plist");
	
	myKnight = myknight;
	chapter = Chapter;
	roomThemeEnum theme = roomThemeEnum(rand() % 5);
	auto battlemap = BattleMap::create(Chapter, theme, myKnight);
	change = Vec2(0, 0);
	addChild(battlemap);
	map = battlemap;
	
	myKnight->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	addChild(myKnight);
	flag = false;//
	inPassage = false;
	transing = false;
	endGame = false;

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(Gaming::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(Gaming::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Gaming::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto mainUILayer = MainUILayer::create(*keyListener, *this);
	mainUILayer->setGlobalZOrder(uiOrder);
	this->addChild(mainUILayer);

	//this->setScale(0.2f);
	//map->setVisible(false);
	this->scheduleUpdate();
	schedule(SEL_SCHEDULE(&Gaming::myUpdate), 0.5f, -1, 0);

	return true;
}

bool Gaming::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == myAttackTag)
		{
			auto attack = static_cast<Weapon*>(nodeA->getParent());
			if (nodeB->getTag() == enemyTag)
			{
				auto enemy = static_cast<Enemy*>(nodeB);
				myKnight->AddEXP(enemy->GetEXP());
				enemy->Behit(attack->GetDamage());
			}
		}

		if (nodeA->getTag() == enemyAttackTag)
		{
			auto attack = static_cast<Weapon*>(nodeA->getParent());
			if (nodeB->getTag() == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeB) ;
				knight->Behit(attack->GetDamage());
			}
		}

		if (nodeB->getTag() == enemyTag)
		{
			if (nodeA->getTag() == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeA); 
				auto enemy = static_cast<Enemy*>(nodeB); 
				knight->Behit(enemy->GetDamage());
			}
			
		}

		if (nodeA->getTag() == explosionTag)
		{
			auto bullet = static_cast<Bullet*>(nodeA->getParent());
			if (nodeB->getTag() == enemyTag)
			{
				auto enemy = static_cast<Enemy*>(nodeB);
				enemy->Behit(bullet->damage);

			}
			if (nodeB->getTag() == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeB);
				knight->Behit(bullet->damage);
			}
			if (nodeB->getTag() == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
				auto room = static_cast<Room*>(nodeB->getParent()->getParent()->getParent());
				room->DeleteObstacles(nodeB->getPosition().x / 64, 32 - nodeB->getPosition().y / 64);
				nodeB->removeAllComponents();
			}
		}


		if (nodeA->getTag() == myBulletTag)
		{
			auto bullet = static_cast<Bullet*>(nodeA);
			if (nodeB->getTag() == enemyTag)
			{
				auto enemy = static_cast<Enemy*>(nodeB);
				enemy->Behit(bullet->damage);
				myKnight->AddEXP(enemy->GetEXP());
				bullet->ShowEffect();
			}
			else if (nodeB->getTag() == obstaclesNormTag)
				bullet->ShowEffect();
			else if (nodeB->getTag() == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
				auto room = static_cast<Room*>(nodeB->getParent()->getParent()->getParent());
				room->DeleteObstacles(nodeB->getPosition().x / 64, 32 - nodeB->getPosition().y / 64);
				nodeB->removeAllComponents();
			}
		}

		if (nodeA->getTag() == enemyBulletTag)
		{
			auto bullet = static_cast<Bullet*>(nodeA);;
			if (nodeB->getTag() == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeB) ;
				knight->Behit(bullet->damage);
				bullet->ShowEffect();
			}
			else if (nodeB->getTag() == obstaclesNormTag || nodeB->getTag() == obstaclesRemovableTag)
				bullet->ShowEffect();
		}

		if (nodeB->getTag() == knightTag)
		{
			if (nodeA->getTag() == nextChapterTag && !transing)
			{
				log("onContactBegin");
				transing = true;
				chapter += 1;
				myKnight->retain();
				myKnight->removeFromParentAndCleanup(false);
				myKnightForever = myKnight;
				nodeA->removeAllComponents();
			}
			
		}
		/* 开启宝箱 */
		if (nodeA->getTag() == knightTag && nodeB->getTag() == chestTag)
		{
			if (_isInteract)
			{
				_isInteract = false;
				auto activer = static_cast <Knight*> (nodeA);
				auto chest = static_cast <Chest*> (nodeB);
				auto item = chest->open(activer);
				item->setPosition(chest->getPosition());
				addChild(item);
			}

		}

		/* 触发雕像 */
		if (nodeA->getTag() == knightTag && nodeB->getTag() == statueTag)
		{
			if (_isInteract)
			{
				_isInteract = false;
				auto activer = static_cast <Knight*> (nodeA);
				auto statue = static_cast <Statue*> (nodeB);
				statue->ActiveStatue(activer);
			}

		}

		/* 宝箱中/掉落的药水交互 */
		if (nodeA->getTag() == knightTag && nodeB->getTag() == potionChestTag)
		{
			if (_isInteract)
			{
				_isInteract = false;
				auto activer = static_cast <Knight*> (nodeA);
				auto potion = static_cast <Potion*> (nodeB);
				potion->Drink(activer);
				removeChild(potion);
			}
		}

		/* 宝箱中/掉落的武器交互 */
		if (nodeA->getTag() == knightTag && nodeB->getTag() == weaponChestTag)
		{
			if (_isInteract)
			{
				_isInteract = false;
				auto activer = static_cast <Knight*> (nodeA);
				auto wp = static_cast <Weapon*> (nodeB);
				activer->BindWea(wp);
				removeChild(wp);
			}
		}

		/* 商店物品交互 */
		if (nodeA->getTag() == knightTag && ((nodeB->getTag() == potionGoodsTag) || (nodeB->getTag() == weaponGoodsTag)))
		{
			if (_isInteract)
			{
				_isInteract = false;
				auto activer = static_cast <Knight*> (nodeA);
				auto potionG = static_cast <Goods*> (nodeB);
				if (potionG->Buy())
				{
					/* 提示购买成功 */
				}
				else
				{
					/* 提示没有足够的钱 */
				}
			}
		}
	}

	return true;
}



bool Gaming::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		if (change == Vec2(0, -1))
			change = Vec2(0, 0);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (change == Vec2(0, 1))
			change = Vec2(0, 0);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if (change == Vec2(1, 0))
			change = Vec2(0, 0);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if (change == Vec2(-1, 0))
			change = Vec2(0, 0);
	}
	return true;
}

bool Gaming::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (!myKnight->death)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			myKnight->BindRoom(atRoom);
			myKnight->MyAttack();
		}

		if (keycode == EventKeyboard::KeyCode::KEY_W)
		{
			map->setVisible(true);
		}
		if (keycode == EventKeyboard::KeyCode::KEY_S)
		{
			map->setVisible(false);
		}


		if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			myKnight->faceDir = Vec2(0, 1);
			myKnight->GetWea()->setRotation(-90.0f);
			change = Vec2(0, -1);
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			myKnight->faceDir = Vec2(-1, 0);
			myKnight->setScaleX(-1.0f);
			myKnight->GetWea()->setRotation(0.0f);
			change = Vec2(1, 0);
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			myKnight->faceDir = Vec2(1, 0);
			myKnight->setScaleX(1.0f);
			myKnight->GetWea()->setRotation(0.0f);
			change = Vec2(-1, 0);
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			myKnight->faceDir = Vec2(0, -1);
			myKnight->GetWea()->setRotation(90.0f);
			change = Vec2(0, 1);
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_F)
		{
			_isInteract = true;
		}
	}
	return true;

}

void Gaming::myUpdate(float delta)
{
	if (!transing && (!map->InRoom(myKnight->getPosition())->playerEnter))
	{
		Vec2 roomPos = atRoom->roomPosition + map->getPosition();
		atRoom->UpdatePlayerEnter(myKnight->getPosition() - roomPos);
	}
}

void Gaming::update(float delta)
{
	if (!myKnight->death && (!transing))
	{
		float move = myKnight->GetMoveSpeed();
		atRoom = map->InRoom(myKnight->getPosition());
		nextRoom = map->InRoom(myKnight->getPosition() - change * 100);
		if (atRoom == nextRoom)
		{
			Vec2 roomPos = atRoom->roomPosition + map->getPosition();
			if (atRoom->Movable(myKnight->getPosition() - change * 30 - roomPos, metaGid, false))
			{
				flag = true;
			}
			else
				flag = false;
		}
		else//修复通道中行动易发生错误的bug
		{
			flag = true;
		}

		if (flag)
		{
			if ((myKnight->getPosition() - change * 60).x <= 1800 && (myKnight->getPosition() - change * 60).x >= 600
				&& (myKnight->getPosition() - change * 60).y <= 1200 && (myKnight->getPosition() - change * 60).y >= 500)
				myKnight->setPosition(myKnight->getPosition() - change * move);
			else
				map->setPosition(map->getPosition() + change * move);
		}
	}
	else if (!endGame && myKnight->death)/*转换场景*/
	{
		
		endGame = true;

	}
	if (transing)
	{
		transing = false;
		endGame = true;
		auto startNewChapter = CallFunc::create([&]() {
			auto scene = Gaming::createScene(myKnightForever, chapter);
			Director::getInstance()->replaceScene(scene);
			});
		
		runAction(startNewChapter);
		unscheduleUpdate();
	}
}
