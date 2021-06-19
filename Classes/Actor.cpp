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

float Actor::GetDamage()
{
	return damage;
}

float Actor::GetDamageMax()
{
	return damageMax;
}


float Actor::GetMoveSpeed()
{
	return moveSpeed;
}

float Actor::GetMoveSpeedMax()
{
	return moveSpeedMax;
}


float Actor::GetHP()
{
	return HP;
}

float Actor::GetHPMax()
{
	return HPMax;
}


float Actor::GetDefence()
{
	return defence;
}

float Actor::GetDefenceMax()
{
	return defenceMax;
}


float Actor::GetAttackRange()
{
	return attackRange;
}

float Actor::GetAttackRangeMax()
{
	return attackRangeMax;
}


float Actor::GetAttackSpeed()
{
	return attackSpeed;
}

float Actor::GetAttackSpeedMax()
{
	return attackSpeedMax;
}


float  Actor::GetAttackDistance()
{
	return attackDistance;
}

float  Actor::GetAttackDistanceMax()
{
	return attackDistanceMax;
}


void Actor::HPNowChange(float hpchange)
{
	if (HP + hpchange <= HPMax)
	{
		HP += hpchange;
	}
	else
	{
		HP = HPMax;
	}
	if (HP <= 0)
	{
		DeathEffect();
	}
}

void Actor::HPMaxChange(float hpchange)
{
	HPMax += hpchange;
	HP = HPMax;
}



void Actor::DefenceNowChange(float defencechange, float continueTime)
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
		defence += defencechange;
		auto recovery = CallFunc::create([&]() {
			defence = defenceMax;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}
void Actor::DefenceMaxChange(float defencechange)
{
	defenceMax += defencechange;
	defence = defenceMax;
}


void Actor::MoveSpeedNowChange(float moveSpeedchange, float continueTime)
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
		moveSpeed += moveSpeedchange;
		auto recovery = CallFunc::create([&]() {
			moveSpeed = moveSpeedMax;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::MoveSpeedMaxChange(float moveSpeedchange)
{
	moveSpeedMax += moveSpeedchange;
	moveSpeed = moveSpeedMax;
}


void Actor::DamageNowChange(float damagechange, float continueTime)
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
		damage += damagechange;
		wea->SetDamageBuff(damage);
		auto recovery = CallFunc::create([&]() {
			damage = damageMax;
			wea->SetDamageBuff(damage);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::DamageMaxChange(float damagechange)
{
	damageMax += damagechange;
	damage = damageMax;
	wea->SetDamageBuff(damage);

}



void Actor::AttackSpeedChange(float  attackSpeedchange, float continueTime)
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
		attackSpeed += attackSpeedchange;
		wea->SetSpeedBuff(attackSpeed);
		auto recovery = CallFunc::create([&]() {
			attackSpeed = attackSpeedMax;
			wea->SetSpeedBuff(attackSpeed);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::AttackSpeedMaxChange(float attackSpeedchange)
{
	attackSpeedMax += attackSpeedchange;
	attackSpeed = attackSpeedMax;
	wea->SetSpeedBuff(attackSpeed);
}



void Actor::AttackRangeChange(float attackRangechange, float continueTime)
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
		attackRange += attackRangechange;
		wea->SetRangeBuff(attackRange);
		auto recovery = CallFunc::create([&]() {
			attackRange = attackRangeMax;
			wea->SetRangeBuff(attackRange);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::AttackRangeMaxChange(float attackRangechange)
{
	attackRangeMax += attackRangechange;
	attackRange = attackRangeMax;
	wea->SetRangeBuff(attackRange);
}



void Actor::AttackDistanceChange(float attackDistancechange, float continueTime)
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
		attackDistance += attackDistancechange;
		wea->SetDistanceBuff(attackDistance);
		auto recovery = CallFunc::create([&]() {
			attackDistance = attackDistanceMax;
			wea->SetDistanceBuff(attackDistance);
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::AttackDistanceMaxChange(float attackDistancechange)
{
	attackDistanceMax += attackDistancechange;
	attackDistance = attackDistanceMax;
	wea->SetDistanceBuff(attackDistance);
}


void Actor::InvincibleTimeChange(float invincibleTimechange, float continueTime)
{
	if (continueTime == -1.0f)
	{
		if (invincibleTime + invincibleTimechange <= invincibleTimeMax)
		{
			invincibleTime += invincibleTimechange;
		}
		else
		{
			invincibleTime = invincibleTimeMax;
		}
	}
	else if (continueTime > 0.0f)
	{
		auto delay = DelayTime::create(continueTime);
		invincibleTime += invincibleTimechange;
		auto recovery = CallFunc::create([&]() {
			invincibleTime = invincibleTimeMax;
			});
		auto seq = Sequence::create(delay, recovery, nullptr);
		runAction(seq);
	}
}

void Actor::InvincibleTimeMaxChange(float invincibleTimechange)
{
	invincibleTimeMax += invincibleTimechange;
	invincibleTime = invincibleTimeMax;
}


void Actor::AddShade(const Vec2 test)
{
	shade = Sprite::create("shade.png");
	this->addChild(shade);
	shade->setPosition(test);
	shade->setGlobalZOrder(floorOrder);
}

void Actor::SetWeaponBuff(Weapon* myWea)
{
	myWea->SetDamageBuff(damage);
	myWea->SetRangeBuff(attackRange);
	myWea->SetSpeedBuff(attackSpeed);
	myWea->SetDistanceBuff(attackDistance);
}
void  Actor::BindWea(Weapon* myWea)/*°óÎäÆ÷*/
{
	SetWeaponBuff(myWea);
	myWea->trigger->setEnabled(false);
	if ((myWea->costEnergy == 0 && wea->costEnergy == 0) ||
		(myWea->costEnergy > 0 && wea->costEnergy > 0))
	{
		weaponForever = wea;
		wea = myWea;
		myWea = weaponForever;
		wea->setPosition(wea->bindPoint + bindPointOffSet);
	}
	else if (wea1 != nullptr)
	{
		weaponForever = wea1;
		wea1 = myWea;
		myWea = weaponForever;
	}
	else
	{
		wea1 = myWea;
	}
	myWea->trigger->setEnabled(true);
}

void  Actor::ChangeWea()
{
	if (wea1 != nullptr)
	{
		weaponForever = wea;
		wea = wea1;
		SetWeaponBuff(wea);
		wea1 = weaponForever;
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
			else
			{
				if (getTag() == knightTag)
				{
					body->setEnabled(false);
					pic->setOpacity(150);
					auto knightBehit = CallFunc::create([&]() {
						; body->setEnabled(true);
						pic->setOpacity(255);
						});
					auto delay = DelayTime::create(invincibleTime);
					auto seq = Sequence::create(delay, knightBehit, nullptr);
					runAction(seq);
				}
			}
		}
	}
}

void Actor::DeathEffect()/*ËÀÍöÐ§¹û*/
{
	death = true;
	auto ActorFall = CallFunc::create([&]() {
		pic->stopAllActions();
		removeAllComponents();
		auto delay = DelayTime::create(0.5f);
		if (getTag() == enemyTag)
		{
			if (DEBUG_CHEST_MODE)
			{
				auto enemyDiePos = getPosition();
				auto wChe = WhiteChest::create();
				wChe->setPosition(enemyDiePos);
				this->getParent()->addChild(wChe);
				inRoom->UpdateDoor();
			}
			inRoom->enemyCount -= 1;
			if (inRoom->enemyCount <= 0)
			{
				inRoom->UpdateDoor();
				if (inRoom->roomType == endRoomEnum)
				{
					inRoom->AddTransDoor();
				}
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
		auto rotateBy = RotateBy::create(1.0f, 90.0f * temp);
		auto seq = Sequence::create(delay, rotateBy, nullptr);
		this->runAction(seq);
		});

	auto ghostAppear = CallFunc::create([&]() {
		ghost = Sprite::create("ghost.png");
		this->getParent()->addChild(ghost);
		ghost->setGlobalZOrder(wallOrder);
		ghost->setPosition(this->getPosition() + Vec2(40, rand() % 15 + 40));
		auto fadeOut = FadeOut::create(1.5f);
		auto move = MoveBy::create(1.0f, Vec2(0, 40 + rand() % 20));
		auto moveEaseOut = EaseOut::create(move->clone(), 1.5f);
		auto ghostDis = CallFunc::create([&]()
			{
				ghost->removeFromParentAndCleanup(true);
			});
		auto mySpawn = Spawn::create(moveEaseOut, fadeOut, nullptr);
		auto ghostSeq = Sequence::create(mySpawn, ghostDis, nullptr);
		ghost->runAction(ghostSeq);
		});

	auto ActorDis = CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
		});
	auto delay = DelayTime::create(1.0f);
	auto delayOne = DelayTime::create(2.0f);
	auto seq = Sequence::create(ActorFall, delay, ghostAppear, delayOne, ActorDis, nullptr);
	this->runAction(seq);
}