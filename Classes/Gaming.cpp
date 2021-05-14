#include "Gaming.h"
USING_NS_CC;

Scene* Gaming::createScene()
{
	auto scene = Scene::create();
	auto layer = Gaming::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamingScene.cpp\n");
}

void ChangePosition()
{

}


bool Gaming::init()
{
	if (!Scene::init())
	{
		return false;
	}
	srand(time(nullptr));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	
	/*int xOffSet, yOffSet;
	int roomNumber=10;
	Vec2 start = (0, 0);
	Vec2 changeDirection = (0, 0);
	int i = 0;
	/*do
	{
		auto tempRoom = Room::create("roomSmall");
		auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
			PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(false);
		tempRoom->addComponent(physicsBody);
		tempRoom->setTag(0);
		int direction = rand() % 4;
		if (direction = 0)
		{
			
		}
		i++;
	} while (i < roomNumber);
	auto tempRoom = Room::create("roomSmall");
	addChild(tempRoom);

	tempRoom->setPosition(Vec2(100,200));*/



	return true;
}

