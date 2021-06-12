#include "Enemy.h"
USING_NS_CC;

Enemy* Enemy::create(int type, bool ifboss)
{
	Enemy* enemy = new Enemy;
	if (enemy != nullptr && enemy->init(type, ifboss))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool Enemy::init(int type, bool ifboss)
{
	this->setTag(enemyTag);
	return true;
}