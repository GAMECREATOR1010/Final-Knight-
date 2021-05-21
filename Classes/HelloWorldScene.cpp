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
	
	srand((unsigned)time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*
		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.

		// add a "close" icon to exit the progress. it's an autorelease object
		auto closeItem = MenuItemImage::create(
											   "CloseNormal.png",
											   "CloseSelected.png",
											   CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

		if (closeItem == nullptr ||
			closeItem->getContentSize().width <= 0 ||
			closeItem->getContentSize().height <= 0)
		{
			problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		}
		else
		{
			float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
			float y = origin.y + closeItem->getContentSize().height/2;
			closeItem->setPosition(Vec2(x,y));
		}

		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);

		/////////////////////////////
		// 3. add your codes below...

		// add a label shows "Hello World"
		// create and initialize a label

		auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
		if (label == nullptr)
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(Vec2(origin.x + visibleSize.width/2,
									origin.y + visibleSize.height - label->getContentSize().height));

			// add the label as a child to this layer
			this->addChild(label, 1);
		}*/

	int theme = rand() % 5;
	map= BattleMap::create(0,theme);
	map->setPosition(Vec2(-300, -300));
	addChild(map,0);
	
	


	sprite1= Sprite::create("Knight1.png");
	if (sprite1 == nullptr)
	{
		problemLoading("'Knight1'");
	}
	else
	{
		sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		addChild(sprite1, 0);
	}
	auto herobody = PhysicsBody::create();
	Vec2 verts[] = { Vec2(0, 55), Vec2(50, -30), Vec2(-50, -30) };
	herobody->addShape(PhysicsShapePolygon::create(verts, 3));
	herobody->setPositionOffset(Vec2(30, 0)); 
	herobody->setGravityEnable(false);
	sprite1->setPhysicsBody(herobody);
	sprite1->setGlobalZOrder(2);
	
	

	auto sprite2 = Sprite::create("shade.png");
	if (sprite2 == nullptr)
	{
		problemLoading("'test1.png'");
	}
	else
	{
		sprite1->addChild(sprite2, -1);
		sprite2->setPosition(Vec2(55, 0));
	}



	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) 
{
	Vec2 change = Vec2(0, 0);
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) 
	{
		change = Vec2(0,-10);
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		change = Vec2(10, 0);
		
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		change = Vec2(-10, 0);
		
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		change = Vec2(0, 10);
	}

	map->setPosition(map->getPosition() +change);

	return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
