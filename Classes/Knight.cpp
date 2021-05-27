#include "Knight.h"
USING_NS_CC;

Knight* Knight::create(int type, int rank)
{
	Knight* knight = new Knight;
	if (knight != nullptr && knight->init( type, rank))
	{
		knight->autorelease();
		return knight;
	}
	CC_SAFE_DELETE(knight);
	return nullptr;
}

bool Knight::init(int type, int rank)
{
	this->setTag(knightTag);
	state = KnightIdle;
	body = PhysicsBody::create();
	if (type == 0)
	{
		maxHP = 5;
		HP = 5;
		pic = Sprite::create("Knight1.png");
		addChild(pic, 0);
		auto shape = PhysicsShapeBox::create(Size(65.0f, 80.0f));
		//Vec2 verts[] = { Vec2(0, 55), Vec2(50, -30), Vec2(-50, -30) };
		//body->addShape(PhysicsShapePolygon::create(verts, 3));
		body->addShape(shape);
		body->setPositionOffset(Vec2(30, 0));
		pic->setPhysicsBody(body);
		pic->setGlobalZOrder(shadeOrder);
		pic->setAnchorPoint(Vec2(0.7f, 0.6f));
		attackMode = gunEnum;
		
	
		Animation* animation = Animation::create();
		animation->addSpriteFrameWithFile("Knight1.png");
		animation->addSpriteFrameWithFile("Knight2.png");
		animation->setDelayPerUnit(0.5);
		Animate* Aniaction = Animate::create(animation);
		pic->runAction(RepeatForever::create(Aniaction));
		
		AddShade( Vec2(-5,-40));
   }
		body->setDynamic(false);
	SetBody(body, KnightCate);
	return true;
}


