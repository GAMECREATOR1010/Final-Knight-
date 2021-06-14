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

void Actor::BindWea(Weapon* myWea)
{
	wea = myWea;
	wea->setPosition(wea->bindPoint);
}
Weapon* Actor::GetWea()
{
	return wea;
}

void Actor::BindRoom(Room* InR)
{
	inRoom = InR;
}

Room* Actor::GetRoom()
{
	return inRoom;
}

bool Actor::init()
{
	return true;
}

void Actor::Behit(float otherDam)
{
	if (!death)
	{
		if (defence - otherDam > 0)
		{
			HP -= defence - otherDam;
			if (HP <= 0)
			{
				death = true;
				DeathEffect();
			}
		}
	}
}


float Actor::GetDamage()
{
	return damage;
}


void Actor::DeathEffect()
{
	auto ActorFall = CallFunc::create([&]() {
		removeAllComponents();
		if (getTag() == enemyTag)
			inRoom->enemyCount -= 1;
		shade->setVisible(false);
		pic->stopAllActions();
		pic->setColor(Color3B(128, 138, 135));
		if (wea != nullptr)
		{
			wea->setColor(Color3B(128, 138, 135));
		}
		pic->setAnchorPoint(Vec2(0.5, 0.3));
		auto temp = this->getScaleX();
		auto rotateBy = RotateBy::create(1.0f, 90.0f*temp);
		this->runAction(rotateBy);
		});

	auto ghostAppear = CallFunc::create([&]() {
		ghost = Sprite::create("ghost.png");
		this->getParent()->addChild(ghost);
		ghost->setGlobalZOrder(wallOrder);
		ghost->setPosition(this->getPosition()+Vec2(40,rand()%15+40));
		auto fadeOut = FadeOut::create(1.5f);
		auto move = MoveBy::create(1.0f, Vec2(0 ,40+rand()%20));
		auto move_ease_out = EaseOut::create(move->clone(),1.5f);
		auto ghostDis = CallFunc::create([&]()
			{
				ghost->removeFromParentAndCleanup(true);
			});
		auto mySpawn = Spawn::create(move_ease_out, fadeOut,nullptr);
		auto ghostSeq= Sequence::create(mySpawn, ghostDis, nullptr);
		ghost->runAction(ghostSeq);
		});
	
	auto ActorDis= CallFunc::create([&]() {
		this -> removeFromParentAndCleanup(true);
		});
	auto delay = DelayTime::create(1.0f);
	auto delayOne = DelayTime::create(2.0f);
	auto seq = Sequence::create(ActorFall, delay, ghostAppear,delayOne, ActorDis,nullptr);
	this->runAction(seq);
}
