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

	roomThemeEnum theme = roomThemeEnum( rand() % 5);
	
	map = BattleMap::create(1, theme);
	change = Vec2(0, 0);
	addChild(map, 0);
	
	
	flag = false;//
	inPassage = false;
	
	sprite1 = Knight::create(0,1);
	sprite1->setGlobalZOrder(shadeOrder);
	
	sprite1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2 ));
	addChild(sprite1);

	weapon =Weapon::create(5,KnightCate);

	sprite1->BindWea(weapon);
	weapon->setPosition(Vec2(-20, -20));
	
	auto pinfo = AutoPolygon::generatePolygon("enemy.png");
	auto ene = Sprite::create(pinfo);
	map->addChild(ene);
	ene->setPhysicsBody(PhysicsBody::createBox(ene->getContentSize()));
	ene->setGlobalZOrder(shadeOrder);
	ene->setPosition(Vec2(1000, 800));
	ene->getPhysicsBody()->setRotationEnable(false);
	//auto enebody = PhysicsBody::createBox(Size(65.0f, 80.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//ene->addComponent(enebody);
	SetBody(ene->getPhysicsBody(), EnemyCate);
	


	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);

	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//this->setScale(0.2f);
	map->setVisible(false);
	this->scheduleUpdate();
	schedule(SEL_SCHEDULE(&HelloWorld::myUpdate), 1.5f,-1,0);
	

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
	
	if (keycode == EventKeyboard::KeyCode::KEY_A)
	{
		
		sprite1->MyAttack();
	}
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		sprite1->faceDir = Vec2(0,1);
		sprite1->GetWea()->setRotation(-90.0f);
		change = Vec2(0, -1);
		//return true;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		sprite1->faceDir = Vec2(-1, 0);
		sprite1->setScaleX(-1.0f);
		sprite1->GetWea()->setRotation(0.0f);
		change = Vec2(1, 0);
		//return true;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		sprite1->faceDir = Vec2(1, 0);
		sprite1->setScaleX(1.0f);
		sprite1->GetWea()->setRotation(0.0f);
		change = Vec2(-1, 0);
		//return true;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		sprite1->faceDir = Vec2(0, -1);
		sprite1->GetWea()->setRotation(90.0f);
		change = Vec2(0, 1);
		//return true;
	}
	else
		return false;
	return true;
	
}

void HelloWorld::myUpdate(float delta)
{
	/*if (!atRoom->playerEnter)
	{
		Vec2 roomPos = atRoom->roomPosition + map->getPosition();
		atRoom->UpdatePlayerEnter(sprite1->getPosition() - roomPos);
	}*/

}

void HelloWorld::update(float delta)
{
	atRoom = map->InRoom(sprite1->getPosition());
	nextRoom = map->InRoom(sprite1->getPosition() - change * 100);
	if (atRoom == nextRoom)
	{
		Vec2 roomPos = atRoom->roomPosition + map->getPosition();
		if (atRoom->Movable(sprite1->getPosition() - change * 30- roomPos, 41, false))
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
		if ((sprite1->getPosition() - change * 60).x <= 1800 && (sprite1->getPosition() - change * 60).x >= 600
			&& (sprite1->getPosition() - change * 60).y <= 1200 && (sprite1->getPosition() - change * 60).y >= 500)
			sprite1->setPosition(sprite1->getPosition() - change* 10);
		else
			map->setPosition(map->getPosition() + change * 10);
	}
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
