#include "Actor.h"
#include "Chest.h"
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

void Actor::BindWea(Weapon* myWea)/*°óÎäÆ÷*/
{

	if ((myWea->costEnergy == 0 && wea->costEnergy == 0)||
		(myWea->costEnergy >0 && wea->costEnergy > 0))
	{
		Weapon* temp = wea;
		wea = myWea;
		myWea = temp;
		wea->setPosition(wea->bindPoint);
	}
	else
	{
		Weapon* temp = wea1;
		wea1 = myWea;
		myWea = temp;
	}
}

void Actor::ChangeWea()
{
	if (wea1 != nullptr)
	{
		Weapon* temp = wea;
		wea = wea1;
		wea1 = temp;
	}
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

void Actor::Behit(float otherDam)/*¹¥»÷Ð§¹û*/
{
	if (!death)
	{
		if (otherDam - defence > 0)
		{
			HP -= otherDam - defence;
			if (HP <= 0)
			{
				DeathEffect();
			}
		}
	}
}


float Actor::GetDamage()
{
	return damage;
}

float Actor::GetMoveSpeed()
{
	return moveSpeed;
}

void Actor::DeathEffect()/*ËÀÍöÐ§¹û*/
{
	death = true;
	auto ActorFall = CallFunc::create([&]() {
		removeAllComponents();
		pic->stopAllActions();
		if (getTag() == enemyTag)
		{
			if (DEBUG_CHEST_MODE)
			{
				auto enemyDiePos = getPosition();
				auto wChe=WhiteChest::create();
				wChe->setPosition(enemyDiePos);
				this->getParent()->addChild(wChe);
			}
			inRoom->enemyCount -= 1;
			if (inRoom->enemyCount <= 0)
			{
				inRoom->UpdateDoor();
			}
		}
		shade->setVisible(false);
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
