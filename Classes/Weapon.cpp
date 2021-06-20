#include "Weapon.h"

/// <summary>
/// 随机创建武器
/// </summary>
/// <returns>武器对象指针</returns>
Weapon* RandomWeaponCreate()
{
	auto rarity = RandomItemRarity();
	switch (rarity)
	{
		case LEGENDARY:
			return nullptr;
		case EPIC:
		{
			int rId = 9;
			return Weapon::create(rId, 1);
		}
		case VERYRARE:
		{
			int rId = 8;
			return Weapon::create(rId, 1);
		}
		case RARE:
		{
			int rId = 7;
			return Weapon::create(rId, 1);
		}
		case UNCOMMON:
		{
			int rId = 6;
			return Weapon::create(rId, 1);
		}
		case COMMON:
		{
			int rId = random(0, 5);
			return Weapon::create(rId, 1);
		}
		default:
			throw("Weapon random create failed! In func: RandomWeaponCreate");
	}
}

Weapon* Weapon::create(int id, int cate)
{
	Weapon* wea = new Weapon;
	if (wea != nullptr && wea->init(id, cate))
	{
		wea->autorelease();
		return wea;
	}
	CC_SAFE_DELETE(wea);
	return nullptr;
}

bool Weapon::init(int id, int cate)
{
	belongCate = cate;
	bulletType = id;
	bindPoint = Vec2(-20, -20);
	ID = id;
	if (id < 5)
	{
		attackMode = meleeEnum;
		attackEffect = Sprite::create("effect_sword.png");
		auto attackEffectbody = PhysicsBody::create();
		Vec2 verts[] = { Vec2(15, -40), Vec2(30, -12), Vec2(30, 10), Vec2(15, 30),Vec2(-30, 30),Vec2(10, 10) };
		attackEffectbody->addShape(PhysicsShapeEdgePolygon::create(verts, 6));
		attackEffect->addComponent(attackEffectbody);
		addChild(attackEffect);
		attackEffect->setPosition(Vec2(30, 60));
		attackEffect->setGlobalZOrder(wallOrder);


		SetBody(attackEffect->getPhysicsBody(), ItemCate);
		attackEffect->setVisible(false);
		attackEffect->getPhysicsBody()->setEnabled(false);

		if (belongCate == KnightCate)
			attackEffect->setTag(myAttackTag);
		else
			attackEffect->setTag(enemyAttackTag);
	}
	else
	{
		perTime = 0.2f;
		std::string  name = "weapon/gun_";
		std::string  number = StringUtils::toString(id - 5);
		bulletType = id - 5;
		std::string gunFilename = name + number + ".png";
		attackMode = gunEnum;
		initWithFile(gunFilename);
	}
	if (id == 0)
	{
		initWithFile("weapon/sword_0.png");
		setAnchorPoint(Vec2(0.2f, 0.5f));
		damage = 1.5;
	}
	else if (id == 1)
	{
		initWithFile("weapon/axe_0.png");
		costEnergy = 1;
		damage = 1.5;
		range = 1.3;
	}
	else if (id == 2)
	{
		initWithFile("weapon/sword_1.png");
		costEnergy = 2;
		damage = 2;
		range = 1.5;
		speed = 2;
	}
	else if (id == 3)
	{
		initWithFile("weapon/sword_2.png");
		costEnergy = 2;
		damage = 3;
		range = 1.8;
		speed = 2;
	}
	else if (id == 4)
	{
		initWithFile("weapon/knife_0.png");
		bindPoint = Vec2(0, -20);
		costEnergy = 3;
		damage = 4;
		range = 2;
		speed = 3;
	}
	else if (id == 5)
	{
		setAnchorPoint(Vec2(0.25f, 0.5f));
		damage = 2.5;
	}
	else if (id == 6)
	{
		setAnchorPoint(Vec2(0.3f, 0.5f));
		damage = 2.5;
		countPerTime = 3;
		costEnergy = 2;
	}
	else if (id == 7)
	{
		setAnchorPoint(Vec2(0.3f, 0.5f));
		damage = 3;
		countPerTime = 4;
		distance = 2;
		costEnergy = 3;
	}
	else if (id == 8)
	{
		setAnchorPoint(Vec2(0.3f, 0.5f));
		damage = 3;
		countPerTime = 8;
		speed = 2;
		distance = 3;
		costEnergy = 4;
	}
	else if (id == 9)
	{
		setAnchorPoint(Vec2(0.3f, 0.5f));
		damage = 4;
		countPerTime = 12;
		speed = 2;
		distance = 1;
		costEnergy = 10;
	}
	else if (id == 10)
	{
		setAnchorPoint(Vec2(0.3f, 0.6f));
		damage = 4;
		countPerTime = 1;
		speed = 2;
		distance = 2;
		costEnergy = 3;
	}
	if (cate == KnightCate)//避免敌人武器被玩家捡起
	{
		trigger = PhysicsBody::createCircle(90.0f, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		SetBody(trigger, ItemCate);
		addComponent(trigger);
	}
	this->SetValue(weaponValue);

	setGlobalZOrder(knightOrder);
	setTag(weaponGroundTag);
	return true;
}

float Weapon::GetDamage()
{
	return damage + damageBuff;
}


/*武器本身属性*/
void Weapon::SetSpeed(float sChange)
{
	speed += sChange;
}
void Weapon::SetRange(float rChange)
{
	range += rChange;
}
void Weapon::SetDamage(float dChange)
{
	damage += dChange;
}
void Weapon::SetDistance(float dChange)
{
	distance += dChange;
}



/*knight属性加成*/
void Weapon::SetSpeedBuff(float sBuff)
{
	speedBuff = sBuff;
}

void Weapon::SetRangeBuff(float rBuff)
{
	rangeBuff = rBuff;
}

void Weapon::SetDamageBuff(float dBuff)
{
	damageBuff = dBuff;
}

void Weapon::SetDistanceBuff(float dBuff)
{
	distanceBuff = dBuff;
}

void Weapon::AddBullet(float addBullet)
{
	if (attackMode == gunEnum)
	{
		if (countPerTime + addBullet <= 12)
		{
			countPerTime += addBullet;
		}
	}
}

void Weapon::WeaponAttack(Vec2  faceDir, Room* inRoom, Vec2 pos)
{
	if (attackMode == meleeEnum)
	{
		MeleeAttack(faceDir);
	}
	else if (attackMode == gunEnum)
	{
		GenerateBullet(faceDir, inRoom, pos);
	}
}

void Weapon::MeleeAttack(Vec2  faceDir)
{
	if (faceDir == Vec2(1, 0) || faceDir == Vec2(-1, 0))
	{
		meleeFacDir = Vec2(30, 0);
		meleeStartRot = -60.0f;
	}
	else if (faceDir == Vec2(0, 1))
	{
		meleeFacDir = Vec2(30, 30);
		meleeStartRot = -10.0f;
	}
	else if (faceDir == Vec2(0, -1))
	{
		meleeFacDir = Vec2(30, 0);
		meleeStartRot = -10.0f;
	}
	setScale(range + 0.2f + rangeBuff * 0.2f);
	auto moveBy = MoveBy::create(0.01f, meleeFacDir);
	auto rotateByOne = RotateBy::create(0.1f - (speed + speedBuff) * 0.01, meleeStartRot);
	auto rotateByTwo = RotateBy::create(0.2f - (speed + speedBuff) * 0.02, 35.0f);
	auto rotateByThird = RotateBy::create(0.2f - (speed + speedBuff) * 0.02, 100.0f);
	auto rotateByForth = RotateBy::create(0.1f, -135.0f - meleeStartRot);



	auto meleeStart = CallFunc::create([&]() {

		if (ID > 0)
		{
			int i = random(0, ID);
			float tempscale = range + ID * 0.1;
			attackEffect->setScale(tempscale);
		}
		attackEffect->setVisible(true);
		attackEffect->getPhysicsBody()->setEnabled(true);
		auto scaleTo = ScaleTo::create(0.2f - (speed + speedBuff) * 0.02, 0.5f);
		attackEffect->runAction(scaleTo);
		});

	auto meleeEnd = CallFunc::create([&]() {
		attackEffect->setVisible(false);
		attackEffect->getPhysicsBody()->setEnabled(false);
		});

	auto recovery = CallFunc::create([&]() {
		setScale(1.0f);
		attackEffect->setScale(1.0f);
		});

	meleeAttack = Sequence::create(moveBy, rotateByOne, rotateByTwo, meleeStart, rotateByThird,
		meleeEnd, rotateByForth, recovery, moveBy->reverse(), nullptr);

	runAction(meleeAttack);

}

void Weapon::GenerateBullet(Vec2  faceDir, Room* inRoom, Vec2 pos)
{
	auto bull = Bullet::create(bulletType, faceDir, belongCate,
		range + rangeBuff * 0.2, damageBuff + damage, speed + speedBuff, distance + distanceBuff);
	inRoom->addChild(bull);
	bull->setPosition(pos);

	if (countPerTime > 1)
	{
		float perAngle = 30;
		float perRradian = 0.523;
		if (countPerTime == 4)
		{
			perAngle = 90.0f;
			perRradian = 1.57f;
		}
		if (countPerTime == 8)
		{
			perAngle = 45.0f;
			perRradian = 0.785f;
		}
		for (int i = 0; i < countPerTime - 1; ++i)
		{
			auto bull = Bullet::create(bulletType, Rotate(faceDir, perRradian * (i / 2 + 1)), belongCate,
				range + rangeBuff * 0.2, damageBuff + damage, speed + speedBuff, distance + distanceBuff);
			inRoom->addChild(bull);
			bull->setRotation(-perAngle * (i / 2 + 1));
			bull->setPosition(pos);
			perAngle = -1 * perAngle;
			perRradian = -1 * perRradian;
		}
	}
}
