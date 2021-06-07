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
	bulletType = id;
	if (id < 5)
	{
		//attackMode = meleeEnum;
		//attackEffect = Sprite::create("effect_sword.png");
		////addChild(attackEffect);
		//attackEffect->setPosition(Vec2(50, 100));
		//attackEffect->setGlobalZOrder(wallOrder);
		////attackEffect->setVisible(false);
	}
	else
		attackMode = gunEnum;

	if (id == 0)
	{
		this->initWithFile("sword_0.png");
		this->setAnchorPoint(Vec2(0.1, 0.5));
		//this->setRotation(60.0f);
	}

	if (cate == KnightCate)//±ÜÃâµÐÈËÎäÆ÷±»Íæ¼Ò¼ñÆð
	{
		trigger = PhysicsBody::createCircle(60.0f, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		SetBody(trigger, ItemCate);
		addComponent(trigger);
	}

	this->setGlobalZOrder(shadeOrder);
	this->setTag(weaponTag);
	return true;
}

void Weapon::GenerateBullet()
{

}

void Weapon::MeleeStart()
{
	meleeEffect->setEnabled(true);
}

void Weapon::MeleeEnd()
{
	meleeEffect->setEnabled(false);
}

