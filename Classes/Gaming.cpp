#include "Gaming.h"
USING_NS_CC;

Scene* Gaming::createScene(Knight* myknight, int Chapter)
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
	contactListener->onContactPreSolve = CC_CALLBACK_1(Gaming::onContactPreSolve, this);

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
		int aTag;
		int bTag;
		if (nodeA->getTag() <= nodeB->getTag())
		{
			aTag = nodeA->getTag();
			bTag = nodeB->getTag();
		}
		else
		{
			bTag = nodeA->getTag();
			aTag = nodeB->getTag();
			auto nodeTemp = nodeA;
			nodeA = nodeB;
			nodeB = nodeTemp;
		}

		CCLOG("onContactBegin %d %d", aTag, bTag);

		if (aTag == enemyTag && bTag == myAttackTag)
		{
			auto attack = static_cast<Weapon*>(nodeB->getParent());
			auto enemy = static_cast<Enemy*>(nodeA);
			myKnight->AddEXP(enemy->GetEXP());
			enemy->Behit(attack->GetDamage());
		}

		if (aTag == knightTag && bTag == enemyAttackTag)
		{
			auto attack = static_cast<Weapon*>(nodeB->getParent());
			auto knight = static_cast<Knight*>(nodeA);
			knight->Behit(attack->GetDamage());
		}

		if (aTag == knightTag && bTag == enemyTag)
		{
			auto knight = static_cast<Knight*>(nodeA);
			auto enemy = static_cast<Enemy*>(nodeB);
			knight->Behit(enemy->GetDamage());
		}

		if (bTag == explosionTag)
		{
			auto bullet = static_cast<Bullet*>(nodeB->getParent());
			if (aTag == enemyTag)
			{
				auto enemy = static_cast<Enemy*>(nodeA);
				enemy->Behit(bullet->damage);
			}
			if (aTag == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeA);
				knight->Behit(bullet->damage);
			}
			if (aTag == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
				auto room = static_cast<Room*>(nodeA->getParent()->getParent()->getParent());
				room->DeleteObstacles(nodeA->getPosition().x / 64, 32 - nodeA->getPosition().y / 64);
				nodeA->removeAllComponents();
			}
		}

		if (bTag == myBulletTag)
		{
			auto bullet = static_cast<Bullet*>(nodeB);
			if (aTag == enemyTag)
			{
				auto enemy = static_cast<Enemy*>(nodeA);
				enemy->Behit(bullet->damage);
				myKnight->AddEXP(enemy->GetEXP());
				bullet->ShowEffect();
			}
			else if (aTag == obstaclesNormTag)
				bullet->ShowEffect();
			else if (aTag == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
				auto room = static_cast<Room*>(nodeA->getParent()->getParent()->getParent());
				room->DeleteObstacles(nodeA->getPosition().x / 64, 32 - nodeA->getPosition().y / 64);
				nodeA->removeAllComponents();
			}
		}

		if (bTag == enemyBulletTag)
		{
			auto bullet = static_cast<Bullet*>(nodeB);
			if (aTag == knightTag)
			{
				auto knight = static_cast<Knight*>(nodeA);
				knight->Behit(bullet->damage);
				bullet->ShowEffect();
			}
			else if (aTag == obstaclesNormTag || aTag == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
			}
		}
		CCLOG("onContactEnd %d %d", aTag, bTag);
	}


	return true;
}

bool Gaming::onContactPreSolve(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		int aTag;
		int bTag;
		if (nodeA->getTag() <= nodeB->getTag())
		{
			aTag = nodeA->getTag();
			bTag = nodeB->getTag();
		}
		else
		{
			bTag = nodeA->getTag();
			aTag = nodeB->getTag();
			auto nodeTemp = nodeA;
			nodeA = nodeB;
			nodeB = nodeTemp;
		}
		//CCLOG("onContactPreSolve, between %d %d", aTag, bTag);

		/* 玩家交互检测 */
		if (aTag == knightTag && bTag>=100)
		{
			CCLOG("Interact contact begin, between %d %d",aTag,bTag);
			if (bTag == chestTag)			/* 开启宝箱 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					auto activer = static_cast <Knight*> (nodeA);
					auto chest = static_cast <Chest*> (nodeB);
					CCLOG("Gaming::onContactPreSolve: Interact activer at position at %f %f", activer->getPositionX(), activer->getPositionY());
					auto item = chest->open(activer);
					if (item != nullptr)
					{
						auto room = chest->getParent();
						room->addChild(item);
						item->setPosition(chest->getPositionX()-offSet*3, chest->getPositionY() - offSet*3);
					}
					chest->setVisible(false);
					chest->removeFromParent();
				}
			}
			else if (bTag == statueTag)			/* 触发雕像 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					CCLOG("Gaming::onContactPreSolve: Active statue");
					auto activer = static_cast <Knight*> (nodeA);
					auto statue = static_cast <Statue*> (nodeB);
					statue->ActiveStatue(activer);
				}
			}
			else if (bTag == potionChestTag)			/* 宝箱中/掉落的药水交互 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					auto activer = static_cast <Knight*> (nodeA);
					auto potion = static_cast <Potion*> (nodeB);
					potion->Drink(activer);
					potion->removeFromParent();
				}
			}
			else if (bTag == weaponChestTag)			/* 宝箱中/掉落的武器交互 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					auto activer = static_cast <Knight*> (nodeA);
					auto wp = static_cast <Weapon*> (nodeB);
					activer->BindWea(wp);
					wp->removeFromParent();
				}
			}
			else if (bTag == potionGoodsTag || bTag == weaponGoodsTag)		/* 商店物品交互 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					auto activer = static_cast <Knight*> (nodeA);
					auto potionG = static_cast <Item*> (nodeB);
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
			else if (bTag == potionBoughtGoodsTag || bTag == weaponBoughtGoodsTag)		/* 已购买物品交互 */
			{
				if (_isInteract)
				{
					_isInteract = false;
					auto activer = static_cast <Knight*> (nodeA);
					auto goodsG = static_cast <Goods*> (nodeB);
					if (bTag == potionBoughtGoodsTag)
					{
						static_cast <Potion*>(goodsG->GetGoods())->Drink(activer);
					}
					else if(bTag== weaponBoughtGoodsTag)
					{
						activer->BindWea(static_cast <Weapon*>(goodsG->GetGoods()));
						activer->ChangeWea();
					}
				}
			}
			else if (bTag == nextChapterTag && !transing)
			{
				if (_isInteract)
				{
					_isInteract = false;
					transing = true;
					chapter += 1;
					myKnight->retain();
					myKnight->removeFromParentAndCleanup(false);
					myKnightForever = myKnight;
					nodeA->removeAllComponents();
				}
			}

			//CCLOG("Interact contact end");
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
	if (keycode == EventKeyboard::KeyCode::KEY_F)
	{
		_isInteract = false;
		CCLOG("F Released");
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
			CCLOG("F Pressed");
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			myKnight->LaunchSkillTime();
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_G)
		{
			auto hackWea=Weapon::create(8);
			myKnight->BindWea(hackWea);
			//myKnight->ChangeWea();

			myKnight->MoveSpeedMaxChange(5);
			myKnight->AttackDistanceMaxChange(5);
			myKnight->DamageMaxChange(10);
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
