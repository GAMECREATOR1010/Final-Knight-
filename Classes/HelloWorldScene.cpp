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

Vec2 ChangeDir()
{
	int i = rand() % 4;
	if (i == 0)
		return Vec2(1, 0);
	else if (i == 1)
		return Vec2(0, 1);
	else if (i == 2)
		return Vec2(-1, 0);
	else
		return Vec2(0, -1);
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

	
	int roomNumber = 6;
	int theme = rand() % 5;
	float offSet = 2112;
	Vec2 genPoint = Vec2(0, 0);
	bool first = true, flag = false;
	int wid = 12, hei =12;

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
			wid = (rand() % 5) * 2 + 10;
			hei = (rand() % 5) * 2 + 10;
		}

		Room* tempRoom = Room::create(wid, hei, 0, theme, genPoint);
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
			if (temp2->Ifnear(pos + Vec2( offSet,0)))
			{
				temp1->doorRight = true;
				temp1->doorNum++;
			}
			if (temp2->Ifnear(pos -Vec2(offSet, 0)))
			{
				temp1->doorLeft = true;
				temp1->doorNum++;
			}
			if (temp1->doorNum >= 4)
				break;
		}
		temp1->drawPassage();
		temp1->updateDoor();
		temp1->updateObstacles();
	}


	auto sprite1 = Sprite::create("Knight1.png");
	if (sprite1 == nullptr)
	{
		problemLoading("'Knight1'");
	}
	else
	{
		sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		addChild(sprite1, 0);
	}

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
