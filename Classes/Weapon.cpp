#include "Weapon.h"

Weapon* Weapon::create(int id, int cate)
{
	Weapon* wea = new Weapon;
	if (wea != nullptr && wea->init(id,cate))
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
	
	if (id < 5)
	{
		attackMode = meleeEnum;
		attackEffect = Sprite::create("effect_sword.png");
		auto attackEffectbody = PhysicsBody::create();
		Vec2 verts[] = { Vec2(15, -40), Vec2(30, -12), Vec2(30, 10), Vec2(15, 30),Vec2(-30, 30),Vec2(10, 10) };
		attackEffectbody->addShape(PhysicsShapeEdgePolygon::create(verts, 6));
		attackEffect->addComponent(attackEffectbody);
		addChild(attackEffect);
		attackEffect->setPosition(Vec2(30,60));
		attackEffect->setGlobalZOrder(wallOrder);
		
		SetBody(attackEffect->getPhysicsBody(), cate);
		attackEffect->setVisible(false);
		attackEffect->getPhysicsBody()->setEnabled(false);
		if (belongCate == KnightCate)
			attackEffect->getPhysicsBody()->setTag(myAttack);
		else
			attackEffect->getPhysicsBody()->setTag(enemyAttack);
	}
	else
		attackMode = gunEnum;

	if (id == 0)
	{
		this->initWithFile("sword_0.png");
		this->setAnchorPoint(Vec2(0.2, 0.5));
	}
	else if (id == 5)
	{
		this->initWithFile("weapon/gun_0.png");
		this->setAnchorPoint(Vec2(0.25, 0.5));
		bulletType = 0;
	}

	if (cate == KnightCate)//±ÜÃâµÐÈËÎäÆ÷±»Íæ¼Ò¼ñÆð
	{
		trigger = PhysicsBody::createCircle(90.0f, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		SetBody(trigger, ItemCate);
		addComponent(trigger);
	}

	this->setGlobalZOrder(wallOrder);
	this->setTag(weaponTag);
	return true;
}

void Weapon::WeaponAttack(Vec2  faceDir)
{
	if (attackMode == meleeEnum)
	{
		MeleeAttack( faceDir);
	}
	else if(attackMode==gunEnum)
	{
		GenerateBullet(faceDir);
	}
}

void Weapon::MeleeAttack(Vec2  faceDir)
{
	if (faceDir == Vec2(1,0) || faceDir == Vec2(-1, 0))
	{
		meleeFacDir = Vec2(20, 0);
		meleeStartRot = -60.0f;
	}
	else if (faceDir == Vec2(0, 1))
	{
		meleeFacDir = Vec2(20, 30);
		meleeStartRot = -10.0f;
	}
	else if (faceDir == Vec2(0, -1))
	{
		meleeFacDir = Vec2(20,0);
		meleeStartRot = -10.0f;
	}


	this->setScale(range+0.2+rangeBuff*0.2);
	auto moveBy = MoveBy::create(0.01f, meleeFacDir);
	auto rotateByOne = RotateBy::create(0.1f, meleeStartRot);
	auto rotateByTwo = RotateBy::create(0.2f, 35.0f);
	auto rotateByThird = RotateBy::create(0.2f, 100.0f);
	auto rotateByForth = RotateBy::create(0.1f, -135.0f - meleeStartRot);
	//auto delay = DelayTime::create(0.2f);


	auto meleeStart = CallFunc::create([&]() {
		attackEffect->setVisible(true);
		attackEffect->getPhysicsBody()->setEnabled(true);
		auto scaleBy = ScaleTo::create(0.2f, 0.5f);
		attackEffect->runAction(scaleBy);
		});

	auto meleeEnd = CallFunc::create([&]() {
		attackEffect->setVisible(false);
		attackEffect->getPhysicsBody()->setEnabled(false);
		});
	
	auto recovery = CallFunc::create([&]() {
		this->setScale(1.0f);
		attackEffect->setScale(1.0f);
		});

	meleeAttack = Sequence::create(moveBy, rotateByOne, rotateByTwo, meleeStart, rotateByThird,
		meleeEnd, rotateByForth, recovery,moveBy->reverse(), nullptr);
	
	this->runAction(meleeAttack);
	
}

Vec2 Rotate(Vec2 faceDir, float angle)
{
	Vec2 temp = Vec2(faceDir.x * cosf(angle) - faceDir.y * sinf(angle), faceDir.x * sinf(angle) + faceDir.y * cosf(angle));
	return temp;
}


void Weapon::GenerateBullet(Vec2  faceDir)
{
	auto bull = Bullet::create(bulletType, faceDir, belongCate, 1.0f + rangeBuff, damageBuff + 1.0f);
	this->getParent()->getParent()->addChild(bull);
	bull->setPosition(this->getParent()->getPosition());


	if (countPerTime > 1)
	{ 
		float perAngle = 30;
		float perRradian = 0.523;
		if (countPerTime == 4)
		{
			perAngle = 90;
			perRradian = 1.57;
		}
		if (countPerTime == 8)
		{
			perAngle = 45;
			perRradian = 0.785;
		}
		for (int i = 0; i < countPerTime ; ++i)
		{
			auto bull = Bullet::create(bulletType, Rotate(faceDir, perRradian*(i/2+1)), belongCate, 1.0f + rangeBuff, damageBuff + 1.0f);
			this->getParent()->getParent()->addChild(bull);
			//this->setRotation(angle);
			bull->setPosition(this->getParent()->getPosition());
			perAngle = -1 * perAngle;
			perRradian = -1 * perRradian;

		}
	}

}


