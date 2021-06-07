#include "Bullet.h"

Bullet* Bullet::create(int bulletType, Vec2 dir,int cate,  float range,float damage, float delayTime)
{
	Bullet* bullet = new Bullet;
	if (bullet != nullptr && bullet->init(bulletType, dir,cate,  range, delayTime))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(int bulletType, Vec2 dir,int cate,  float range, float damage, float delayTime)
{
	type = bulletType;
	trigger=  PhysicsBody::create();
	if (bulletType == 0)
	{
		this->initWithFile("roundBullet1.png");
		
		trigger->addShape(PhysicsShapeCircle::create(10.0f));
		SetBody(trigger, ItemCate);
		this->addComponent(trigger);
	}
	if (cate == KnightCate)
	{
		this->setTag(myAttack);
	}
	else
		this->setTag(enemyAttack);

	this->setGlobalZOrder(wallOrder);
	auto moveBy = MoveBy::create(2.0f, dir * 300);
	auto bulletEffect = CallFunc::create([&]() {
		this->ShowEffect();
		});
	auto bulletDis = CallFunc::create([&]() {
		this->removeFromParent();
		});
	auto mySeq = Sequence::create(moveBy, bulletEffect,bulletDis, nullptr);
	this->runAction(mySeq);
	return true;
}

void Bullet::ShowEffect()
{
	if (this->type == 0)
	{
		auto particleSystem = ParticleSystemQuad::create("shot0.plist");
		this->getParent()->addChild(particleSystem);
		particleSystem->setGlobalZOrder(wallOrder);
		particleSystem->setPosition(this->getPosition());
	}
}
