#include "Knight.h"
USING_NS_CC;

Knight* Knight::create(int type, int rank)
{
	Knight* knight = new Knight;
	if (knight != nullptr && knight->init(type, rank))
	{
		knight->autorelease();
		return knight;
	}
	CC_SAFE_DELETE(knight);
	return nullptr;
}

bool Knight::init(int type, int rank)
{
	state = KnightIdle;
	body = PhysicsBody::create();
	if (type == 0)
	{
		maxHP = 5;
		HP = 5;
		pic = Sprite::create("Knight1.png");
		addChild(pic, 0);
		auto shape = PhysicsShapeBox::create(Size(45.0f, 40.0f));
		body->addShape(shape);
		pic->setGlobalZOrder(shadeOrder);
		pic->setAnchorPoint(Vec2(0.7f, 0.6f));
		attackMode = gunEnum;

		Animation* animation = Animation::create();
		animation->addSpriteFrameWithFile("Knight1.png");
		animation->addSpriteFrameWithFile("Knight2.png");
		animation->setDelayPerUnit(0.5);
		Animate* Aniaction = Animate::create(animation);
		pic->runAction(RepeatForever::create(Aniaction));

		AddShade(Vec2(-5, -40));
		wea = Weapon::create(6, KnightCate);
		addChild(wea);
		wea->setPosition(wea->bindPoint);
	}

	body->setDynamic(false);
	addComponent(body);
	SetBody(body, KnightCate);
	setTag(knightTag);
	return true;
}

void Knight::AddDefence(float addDefence)
{
	defence += addDefence;
}

void Knight::AddMoveSpeed(float addMoveSpeed)
{
	moveSpeed += addMoveSpeed;
}

void Knight::MyAttack()
{
	if (this->state != KnightAttack && (energy - wea->costEnergy) > 0)
	{
		this->state = KnightAttack;
		energy -= wea->costEnergy;
		auto attacking = CallFunc::create([&]() {
			wea->WeaponAttack(this->faceDir);
			});
		auto attackEnd = CallFunc::create([&]() {
			this->state = KnightIdle;
			});
		auto delay = DelayTime::create(0.5f);
		auto myseq = Sequence::create(attacking, delay, attackEnd, nullptr);
		this->runAction(myseq);
	}
}