#include "Const.h"
Vector<SpriteFrame*> GetAnim(const char* format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}

	return animFrames;
}

Vec2 ChangeDir()
{
	int i = rand() % 4;
	if (i == 0)
		return Vec2(1, 0);
	else if (i == 1)
		return Vec2(0, 1);
	else if (i == 2)
		return Vec2(-1, 0);
	else
		return Vec2(0, -1);
}

Vec2 Rotate(Vec2 faceDir, float angle)
{
	Vec2 temp = Vec2(faceDir.x * cosf(angle) - faceDir.y * sinf(angle), faceDir.x * sinf(angle) + faceDir.y * cosf(angle));
	return temp;
}

void SetBody(PhysicsBody* body, int category)
{
	if (category == KnightCate)
	{
		body->setCategoryBitmask(0x01); //1
		body->setCollisionBitmask(0x06); //110
		
	}
	else if (category == EnemyCate)
	{
		body->setCategoryBitmask(0x02); //10
		body->setCollisionBitmask(0xff); //避免重叠
	}
	else if (category == ObstaclesCate)
	{
		body->setCategoryBitmask(0x03); //11
		body->setCollisionBitmask(0x06); //110
	}
	else if (category == ItemCate)
	{
		body->setCategoryBitmask(0x04);//100 //不碰撞,仅触发
		body->setCollisionBitmask(0x01); 
		body->setDynamic(false);
	}
	body->setContactTestBitmask(0xff);
}