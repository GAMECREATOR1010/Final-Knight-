#include "Bullet.h"

Bullet* Bullet::create(int bulletType, Vec2 dir, int cate, float range, float damage, float delayTime)
{
	Bullet* bullet = new Bullet;
	if (bullet != nullptr && bullet->init(bulletType, dir, cate, range, delayTime))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(int bulletType, Vec2 dir, int cate, float range, float damage, float delayTime)
{
	type = bulletType;
	trigger = PhysicsBody::create();
	if (bulletType == 0)
	{
		this->initWithFile("bullet/roundBullet1.png");
		trigger->addShape(PhysicsShapeCircle::create(20.0f));
	}
	else if (bulletType == 1)
	{
		this->initWithFile("bullet/triangleBullet.png");
		Vec2 verts[] = { Vec2(-30, -3), Vec2(30,-3), Vec2(0, 40) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
	}
	else if (bulletType == 2)
	{
		this->initWithFile("bullet/triangleBullet1.png");
		Vec2 verts[] = { Vec2(-17, -17), Vec2(17,-17), Vec2(0, 27) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 3));
	}
	else if (bulletType == 3)
	{
		this->initWithFile("bullet/lightEffect01.png");
		Vec2 verts[] = { Vec2(-15, -144), Vec2(-15,144), Vec2(15, 144),Vec2(15, -144) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 4));
	}
	else if (bulletType == 4)
	{
		this->initWithFile("bullet/crossBullet.png");
		Vec2 verts[] = { Vec2(-15, -144), Vec2(-15,144), Vec2(15, 144),Vec2(15, -144) };
		trigger->addShape(PhysicsShapeEdgePolygon::create(verts, 4));
	}

	SetBody(trigger, ItemCate);
	this->addComponent(trigger);
	if (cate == KnightCate)
	{
		this->setTag(myAttack);
	}
	else
		this->setTag(enemyAttack);

	//this->setGlobalZOrder(wallOrder);
	auto moveBy = MoveBy::create(2.0f, dir * 300);
	auto bulletEffect = CallFunc::create([&]() {
		this->ShowEffect();
		});
	auto bulletDis = CallFunc::create([&]() {
		this->removeFromParent();
		});
	auto mySeq = Sequence::create(moveBy, bulletEffect, bulletDis, nullptr);
	this->runAction(mySeq);
	return true;
}

void Bullet::ShowEffect()
{
	std::string  effect = "bulletParticle/shot";
	std::string count = StringUtils::toString(type);
	std::string filename = effect + count + ".plist";
	auto particleSystem = ParticleSystemQuad::create(filename);
	this->getParent()->addChild(particleSystem);
	particleSystem->setGlobalZOrder(wallOrder);
	particleSystem->setPosition(this->getPosition());
}