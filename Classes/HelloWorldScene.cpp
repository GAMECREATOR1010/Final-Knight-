/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// 1. super init first
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
	roomThemeEnum theme = roomThemeEnum(rand() % 5);

	map = BattleMap::create(1, theme);
	change = Vec2(0, 0);
	addChild(map, 0);

	flag = false;//
	inPassage = false;

	myKnight = Knight::create(0, 1);
	myKnight->setGlobalZOrder(shadeOrder);

	myKnight->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	addChild(myKnight);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//this->setScale(0.2f);
	//map->setVisible(false);
	this->scheduleUpdate();
	schedule(SEL_SCHEDULE(&HelloWorld::myUpdate), 1.5f, -1, 0);

	return true;
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == myAttackTag)
		{
			auto attack = (Weapon*)nodeA->getParent();
			if (nodeB->getTag() == enemyTag)
			{
				auto enemy = (Enemy*)nodeB;
				enemy->Behit(attack->GetDamage());
			}
		}

		if (nodeA->getTag() == enemyAttackTag)
		{
			auto attack = (Weapon*)nodeA->getParent();
			if (nodeB->getTag() == knightTag)
			{
				auto knight = (Knight*)nodeB;
				knight->Behit(attack->GetDamage());
			}
		}

		if (nodeB->getTag() == enemyTag)
		{
			if (nodeA->getTag() == knightTag)
			{
				auto knight = (Knight*)nodeA;
				auto enemy = (Enemy*)nodeB;
				knight->Behit(enemy->GetDamage());
			}
		}

		if (nodeA->getTag() == myBulletTag)
		{
			auto bullet = (Bullet*)nodeA;
			if (nodeB->getTag() == enemyTag)
			{
				auto enemy = (Enemy*)nodeB;
				enemy->Behit(bullet->damage);
				bullet->ShowEffect();
			}
			else if (nodeB->getTag() == obstaclesNormTag)
				bullet->ShowEffect();
			else if (nodeB->getTag() == obstaclesRemovableTag)
			{
				bullet->ShowEffect();
				auto room = (Room*)nodeB->getParent()->getParent()->getParent();
				room->DeleteObstacles(nodeB->getPosition().x / 64, 32 - nodeB->getPosition().y / 64);
				nodeB->removeAllComponents();
			}
		}

		if (nodeA->getTag() == enemyBulletTag)
		{
			auto bullet = (Bullet*)nodeA;
			if (nodeB->getTag() == knightTag)
			{
				auto knight = (Knight*)nodeB;
				knight->Behit(bullet->damage);
				bullet->ShowEffect();
			}
			else if (nodeB->getTag() == obstaclesNormTag || nodeB->getTag() == obstaclesRemovableTag)
				bullet->ShowEffect();
		}

	}


	log("onContactBegin");
	return true;
}

bool HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
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

bool HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (!myKnight->death)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			//myKnight->DeathEffect();
			myKnight->MyAttack();
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
	}
	return true;
}

void HelloWorld::myUpdate(float delta)
{
	if (!atRoom->playerEnter)
	{
		Vec2 roomPos = atRoom->roomPosition + map->getPosition();
		atRoom->UpdatePlayerEnter(myKnight->getPosition() - roomPos);
	}
}

void HelloWorld::update(float delta)
{
	if (!myKnight->death)
	{
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
				myKnight->setPosition(myKnight->getPosition() - change * 10);
			else
				map->setPosition(map->getPosition() + change * 10);
		}
	}
	else if (!endGame && myKnight->death)/*转换场景*/
	{
		endGame = true;
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}