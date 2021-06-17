#include "Bullet.h"

Bullet* Bullet::create(int bulletType, Vec2 dir,int cate,  float range,float damage, float speed,float distance)
{
	Bullet* bullet = new Bullet;
	if (bullet != nullptr && bullet->init(bulletType, dir,cate,  range, speed,distance))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(int bulletType, Vec2 dir,int cate,  float rangeW, float damageW, float speed,float distance)
{
	std::string  path = "bullet/";
	std::string count = StringUtils::toString(cate);
	std::string filename = path + count ;

	type = bulletType;
	damage = damageW;
	trigger=  PhysicsBody::create();
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
		Vec2 verts[] = { Vec2(-30, -3), Vec2(30,-3), Vec2(0, 40)};
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

	SetBody(trigger, ItemCate);
	this->addComponent(trigger);

	if (cate == KnightCate)
	{
		this->setTag(myBulletTag);
	}
	else
		this->setTag(enemyBulletTag);
	


	this->setScale(rangeW);
	this->setGlobalZOrder(uiOrder);
	auto moveBy = MoveBy::create(1.5f-speed*0.2f, dir * (250+distance*50));
	auto bulletEffect = CallFunc::create([&]() {
		this->ShowEffect();
		});
	
	auto mySeq = Sequence::create(moveBy, bulletEffect,nullptr);
	this->runAction(mySeq);
	return true;
}

void Bullet::BulletDis()
{
	this->removeFromParentAndCleanup(true);
}

void Bullet::ShowEffect()
{
	std::string  effect = "bulletParticle/shot";
	std::string countEffect = StringUtils::toString(type);
	std::string filenameEffect = effect + countEffect + ".plist";
	auto particleSystem = ParticleSystemQuad::create(filenameEffect);
	this->getParent()->addChild(particleSystem);
	particleSystem->setGlobalZOrder(wallOrder);
	particleSystem->setPosition(this->getPosition());
	auto bulletDis = CallFunc::create([&]() {
		this->BulletDis();
		});
	auto delay = DelayTime::create(0.05f);
	auto mySeq = Sequence::create(delay, bulletDis, nullptr);
	this->runAction(mySeq);
}
