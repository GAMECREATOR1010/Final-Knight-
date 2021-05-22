#include "Actor.h"
USING_NS_CC;

Actor* Actor::create()
{
	Actor* actor = new Actor;
	if (actor != nullptr && actor->init())
	{
		actor->autorelease();
		return actor;
	}
	CC_SAFE_DELETE(actor);
	return nullptr;
}

Actor::~Actor() {}

void Actor::AddShade(const Vec2 test)
{
	shade = Sprite::create("shade.png");
	if (shade == nullptr)
	{
		log("'test1.png'");
	}
	else
	{
		addChild(shade);
		shade->setPosition(test);
		shade->setGlobalZOrder(1);
	}
}

bool Actor::init()
{
	return true;
}
