#include "Bullet.h"

Bullet* Bullet::create(int bulletType, Vec2 dir, int cate, float range, float damage, float speed, float distance)
{
	Bullet* bullet = new Bullet;
	if (bullet != nullptr && bullet->init(bulletType, dir,  cate, range, damage, speed, distance))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(int bulletType, Vec2 dir, int cate, float rangeW, float damageW, float speed, float distance)
{
	std::string  path = "bullet/";
	std::string count = StringUtils::toString(cate);
	std::string filename = path + count;

	belongCate = cate;
	type = bulletType;
	damage = damageW;
	trigger = PhysicsBody::create();
	if (bulletType == 0)
	{
		filename += "roundBullet1.png";
		this->initWithFile(filename);
		trigger->addShape(PhysicsShapeCircle::create(20.0f));
	}
	else if (bulletType == 1)
	{
		filename += "triangleBullet.png";
		this->initWithFile(filename);
		Vec2 verts[] = { Vec2(-30, -3), Vec2(30,-3), Vec2(0, 40) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
	}
	else if (bulletType == 2)
	{
		filename += "triangleBullet1.png";
		this->initWithFile(filename);
		Vec2 verts[] = { Vec2(-17, -17), Vec2(17,-17), Vec2(0, 27) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
	}
	else if (bulletType == 3)
	{
		filename += "crossBullet.png";
		this->initWithFile(filename);
		Vec2 verts[] = { Vec2(-25, -7), Vec2(-25,7), Vec2(-5, 7),Vec2(-5, 25),Vec2(5,25),Vec2(5,7)
		, Vec2(25,7),Vec2(25, -7),Vec2(5,-7),Vec2(5, -25), Vec2(-5, -25), Vec2(-5,-7), };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 12));
	}
	else if (bulletType == 4)
	{
		filename += "lightEffect.png";
		this->initWithFile(filename);
		Vec2 verts[] = { Vec2(-15, -144), Vec2(-15,144), Vec2(15, 144),Vec2(15, -144) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 4));
	}
	else if (bulletType == 5)
	{
		filename += "bomb.png";
		this->initWithFile(filename);
		trigger->addShape(PhysicsShapeCircle::create(25.0f));
	}
	if (type < 5)
	{
		SetBody(trigger, ItemCate);
		if (cate == KnightCate)
		{
			this->setTag(myBulletTag);
		}
		else
			this->setTag(enemyBulletTag);
	}
	else
	{
		SetBody(trigger, ObstaclesCate);
		trigger->setDynamic(false);
	}

	this->addComponent(trigger);
	this->setScale(rangeW);
	this->setGlobalZOrder(wallOrder);

	auto bulletEffect = CallFunc::create([&]() {
		this->ShowEffect();
		});

	if (type > 4)
	{
		auto delayPre = DelayTime::create(2.0f-(type-5)*0.1f);
		auto explosion = Sprite::create("weapon/empty.png");
		addChild(explosion);
		explosion->setPosition(Vec2(15, 30));
		explosionEffect = PhysicsBody::create();
		explosionEffect->addShape(PhysicsShapeCircle::create(25 * type));
		SetBody(explosionEffect,ItemCate);
		explosion->addComponent(explosionEffect);
		explosion->setTag(explosionTag);
	
		explosionEffect->setEnabled(false);
		auto bomp = CallFunc::create([&]() {
			explosionEffect->setEnabled(true);
			});
		auto continueExplosion = DelayTime::create(0.3f);
		auto mySeq = Sequence::create(delayPre, bomp, continueExplosion, bulletEffect,nullptr);
		this->runAction(mySeq);
	}
	else
	{
		auto moveBy = MoveBy::create(0.8f - speed * 0.1f, dir * (500 + distance * 70));
		auto moveEasOut = EaseOut::create(moveBy->clone(), 0.5f);
		if (bulletType == 4)
		{
			auto moveSineOut = EaseSineOut::create(moveBy->clone());
			auto mySeq = Sequence::create(moveSineOut, bulletEffect, nullptr);
			this->runAction(mySeq);
		}
		else
		{
			auto mySeq = Sequence::create(moveEasOut, bulletEffect, nullptr);
			this->runAction(mySeq);
		}
	}
	return true;
}

void Bullet::BulletDis()
{
	this->removeFromParentAndCleanup(true);
}

void Bullet::ShowEffect()
{
	stopAllActions();
	auto bulletParticle = CallFunc::create([&]() {
		if (type > 4)
			type = 5;
		std::string  effect = "bulletParticle/shot";
		std::string countEffect = StringUtils::toString(type);
		std::string filenameEffect = effect + countEffect + ".plist";
		auto particleSystem = ParticleSystemQuad::create(filenameEffect);
		this->getParent()->addChild(particleSystem);
		particleSystem->setGlobalZOrder(wallOrder);
		particleSystem->setPosition(this->getPosition());
		});
	auto bulletDis = CallFunc::create([&]() {
		this->BulletDis();
		});

	auto delay = DelayTime::create(0.05f);
	auto mySeq = Sequence::create(bulletParticle, delay, bulletDis, nullptr);
	this->runAction(mySeq);
}
