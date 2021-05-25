#include "Bullet.h"

Bullet* Bullet::create(int bulletType)
{
	Bullet* bullet = new Bullet;
	if (bullet != nullptr && bullet->init(bulletType))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(int bulletType)
{
	return true;
}

void Bullet::ShowEffect(int bulletType)
{

}

void Bullet::RemoveBullet()
{

}