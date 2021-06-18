#include "Knight.h"
USING_NS_CC;

Knight* Knight::create(int type, int rank)
{
	Knight* knight = new Knight;
	if (knight != nullptr && knight->init( type, rank))
	{
		knight->autorelease();
		return knight;
	}
	CC_SAFE_DELETE(knight);
	return nullptr;
}


bool Knight::init(int type, int rank)
{
	wea1 = nullptr;
	state = KnightIdle;
	body = PhysicsBody::create();
	if (type == 0)
	{
		HPMax = 50;
		defenceMax = 2;
		pic = Sprite::create("Knight1.png");
		addChild(pic, 0);
		auto shape = PhysicsShapeBox::create(Size(45.0f,40.0f));
		body->addShape(shape);
		pic->setGlobalZOrder(knightOrder);
		pic->setAnchorPoint(Vec2(0.7f, 0.6f));
		attackMode = gunEnum;
		
		Animation* animation = Animation::create();
		animation->addSpriteFrameWithFile("Knight1.png");
		animation->addSpriteFrameWithFile("Knight2.png");
		animation->setDelayPerUnit(0.5);
		Animate* Aniaction = Animate::create(animation);
		pic->runAction(RepeatForever::create(Aniaction));
		
		AddShade( Vec2(-5,-40));
		wea = Weapon::create(5, KnightCate);
		addChild(wea);
		wea->setPosition(wea->bindPoint);
		wea->trigger->setEnabled(false);
   }
	HPMax = HP;
	moveSpeed = moveSpeedMax;
	defence = defenceMax;
	energyNow = energyMax;


	body->setDynamic(false);
	addComponent(body);
	SetBody(body, KnightCate);
	setTag(knightTag);
	return true;
}


void Knight::EnergyMaxChange(float energychange)
{
	energyMax += energychange;
	energyNow = energyMax;
}

void Knight::EnergyNowChange(float energychange)
{
	if (energyNow + energychange <= energyMax)
	{
		energyNow += energychange;
	}
	else
	{
		energyNow = energyMax;
	}
}

float Knight::GetEnergyNow()
{
	return energyNow;
}

float Knight::GetEnergyMax()
{
	return energyMax;
}


int Knight::GetRank()
{
	return rank;
}

void Knight::LevelUp()
{
	energyMax += 10;
	energyNow = energyMax;
}

void Knight::AddEXP(int addEXP)
{
	EXP += addEXP;
	if (EXP / 20 > rank * 20)
	{
		rank += 1;
		LevelUp();
	}
}

void Knight::MyAttack()
{
	if (this->state != KnightAttack&&(energyNow-wea->costEnergy)>=0)
	{
		this->state = KnightAttack;
		energyNow -= wea->costEnergy;
		auto attacking = CallFunc::create([&]() {
			wea->WeaponAttack(this->faceDir,inRoom, getPosition() -inRoom->roomPosition -inRoom->getParent()->getPosition());
			});
		auto attackEnd = CallFunc::create([&]() {
			this->state = KnightIdle;
			});
		auto delay = DelayTime::create(wea->perTime);
		auto myseq = Sequence::create(attacking, delay, attackEnd, nullptr);
		this->runAction(myseq);
	}
}
