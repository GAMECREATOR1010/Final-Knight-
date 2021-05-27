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
Actor::Actor() {}

void Actor::AddShade(const Vec2 test)
{
	shade = Sprite::create("shade.png");
	this->addChild(shade);
	shade->setPosition(test);
	shade->setGlobalZOrder(floorOrder);
}

void Actor::bindWea(Weapon* myWea)
{
	wea = myWea;
	addChild(myWea);
}

bool Actor::init()
{
	return true;
}


void Actor::DeathEffect()
{
	auto ActorFall = CallFunc::create([&]() {
		shade->setVisible(false);
		pic->stopAllActions();
		pic->setColor(Color3B(128, 138, 135));
		if (wea != nullptr)
		{
			wea->setColor(Color3B(128, 138, 135));
		}
		pic->setAnchorPoint(Vec2(0.5, 0.3));
		auto rotateBy = RotateBy::create(1.0f, 90.0f);
		this->runAction(rotateBy);
		/**/
		});

	auto ghostAppear = CallFunc::create([&]() {
		ghost = Sprite::create("ghost.png");
		addChild(ghost);
		ghost->setGlobalZOrder(wallOrder);
		ghost->setPosition(Vec2(-30, 50));
		auto fadeOut = FadeOut::create(1.5f);
		auto move = MoveBy::create(1.0f, Vec2(-40,0));
		auto move_ease_out = EaseOut::create(move->clone(),1.0f);
		auto mySpawn = Spawn::create(move_ease_out, fadeOut,nullptr);
		ghost->runAction(mySpawn);
		});
	
	auto delay = DelayTime::create(1.0f);
	auto seq = Sequence::create(ActorFall, delay, ghostAppear, nullptr);
	this->runAction(seq);
}
