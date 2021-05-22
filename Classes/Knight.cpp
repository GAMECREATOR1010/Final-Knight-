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
	/*pic= Sprite::create("Knight1.png");
	pic->setPosition(Vec2(0, 0));
	addChild(pic, 0);*/
	if (type == 0)
	{
		maxHP = 5;
		HP = 5;
		auto pinfo = AutoPolygon::generatePolygon("Knight1.png");
		pic = Sprite::create(pinfo);
		addChild(pic, 0);
		auto herobody = PhysicsBody::create();
		Vec2 verts[] = { Vec2(0, 55), Vec2(50, -30), Vec2(-50, -30) };
		herobody->addShape(PhysicsShapePolygon::create(verts, 3));
		herobody->setPositionOffset(Vec2(30, 0));
		herobody->setGravityEnable(false);
		pic->setPhysicsBody(herobody);
		pic->setGlobalZOrder(2);
		
		pic->setAnchorPoint(Vec2(0.7, 0.65));
		
		Animation* animation = Animation::create();
		animation->addSpriteFrameWithFile("Knight1.png");
		animation->addSpriteFrameWithFile("Knight2.png");
		animation->setDelayPerUnit(0.5);
		Animate* Aniaction = Animate::create(animation);
		pic->runAction(RepeatForever::create(Aniaction));
		
		AddShade( Vec2(-5,-40));
   }
	return true;
}


