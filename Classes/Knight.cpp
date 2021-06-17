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
		HP = 50;
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
   }
	moveSpeed = moveSpeedMax;
	body->setDynamic(false);
	addComponent(body);
	SetBody(body, KnightCate);
	setTag(knightTag);
	return true;
}



void Knight::HPNowChange(float hpchange,float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (HP + hpchange <= HPMax)
		{
			HP += hpchange;
		}
		else
		{
			HP = HPMax;
		}
	}
	else if(continueTime>0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempHP = HP;
		HP += hpchange;
		auto recovery = CallFunc::create([&]() {
			HP = tempHP;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::HPMaxChange(float hpchange)
{
	HPMax += hpchange;
	HP = HPMax;
}


void Knight::DefenceNowChange(float defencechange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (defence + defencechange <= defenceMax)
		{
			defence += defencechange;
		}
		else
		{
			defence = defenceMax;
		}
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempDefence = defence;
		defence += defencechange;
		auto recovery = CallFunc::create([&]() {
			defence = tempDefence;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::DefenceMaxChange(float defencechange)
{
	defenceMax += defencechange;
	defence = defenceMax;
}


void Knight::MoveSpeedNowChange(float moveSpeedchange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (moveSpeed + moveSpeedchange <= moveSpeedMax)
		{
			moveSpeed += moveSpeedchange;
		}
		else
		{
			moveSpeed = moveSpeedMax;
		}
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempMoveSpeed = moveSpeed;
		moveSpeed += moveSpeedchange;
		auto recovery = CallFunc::create([&]() {
			moveSpeed = tempMoveSpeed;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::MoveSpeedMaxChange(float moveSpeedchange)
{
	moveSpeedMax += moveSpeedchange;
	moveSpeed = moveSpeedMax;
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

void Knight::DamageNowChange(float damagechange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (damage + damagechange <= damageMax)
		{
			damage += damagechange;
		}
		else
		{
			damage = damageMax;
		}
		wea->SetDamageBuff(damage);
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempDamage = damage;
		damage += damagechange;
		wea->SetDamageBuff(damage);
		auto recovery = CallFunc::create([&]() {
			damage = tempDamage;
			wea->SetDamageBuff(damage);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::DamageMaxChange(float damagechange)
{
	damageMax += damagechange;
	damage = damageMax;
	wea->SetDamageBuff(damage);

}


void Knight::AttackSpeedChange(float  attackSpeedchange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (attackSpeed + attackSpeedchange <= attackSpeedMax)
		{
			attackSpeed += attackSpeedchange;
		}
		else
		{
			attackSpeed = attackSpeedMax;
		}
		wea->SetSpeedBuff(attackSpeed);
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempAttackSpeed = attackSpeed;
		attackSpeed += attackSpeedchange;
		wea->SetSpeedBuff(attackSpeed);
		auto recovery = CallFunc::create([&]() {
			attackSpeed = tempAttackSpeed;
			wea->SetSpeedBuff(attackSpeed);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::AttackSpeedMaxChange(float attackSpeedchange)
{
	attackSpeedMax += attackSpeedchange;
	attackSpeed = attackSpeedMax;
	wea->SetSpeedBuff(attackSpeed);
}

void Knight::AttackRangeChange(float attackRangechange, float continueTime )
{
	if (continueTime == -1.0f)
	{
		if (attackRange + attackRangechange <= attackRangeMax)
		{
			attackRange += attackRangechange;
		}
		else
		{
			attackRange = attackRangeMax;
		}
		wea->SetRangeBuff(attackRange);
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempAttackRange = attackRange;
		attackRange += attackRangechange;
		wea->SetRangeBuff(attackRange);
		auto recovery = CallFunc::create([&]() {
			attackRange = tempAttackRange;
			wea->SetRangeBuff(attackRange);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::AttackRangeMaxChange(float attackRangechange)
{
	attackRangeMax += attackRangechange;
	attackRange = attackRangeMax;
	wea->SetRangeBuff(attackRange);
}


void Knight::AttackDistanceChange(float attackDistancechange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (attackDistance + attackDistancechange <= attackDistanceMax)
		{
			attackDistance += attackDistancechange;
		}
		else
		{
			attackDistance = attackDistanceMax;
		}
		wea->SetDistanceBuff(attackDistance);
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		tempAttackDistance = attackDistance;
		attackDistance += attackDistancechange;
		wea->SetDistanceBuff(attackDistance);
		auto recovery = CallFunc::create([&]() {
			attackDistance = tempAttackDistance;
			wea->SetDistanceBuff(attackDistance);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Knight::AttackDistanceMaxChange(float attackDistancechange)
{
	attackDistanceMax += attackDistancechange;
	attackDistance = attackDistanceMax;
	wea->SetDistanceBuff(attackDistance);
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
			wea->WeaponAttack(this->faceDir);
			});
		auto attackEnd = CallFunc::create([&]() {
			this->state = KnightIdle;
			});
		auto delay = DelayTime::create(wea->perTime);
		auto myseq = Sequence::create(attacking, delay, attackEnd, nullptr);
		this->runAction(myseq);
	}
}
