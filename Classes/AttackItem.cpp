#include "AttackItem.h"

USING_NS_CC;

AttackItem* AttackItem::create()
{
	AttackItem* attackitem = new AttackItem;
	if (attackitem != nullptr && attackitem->init())
	{
		attackitem->autorelease();
		return attackitem;
	}
	CC_SAFE_DELETE(attackitem);
	return nullptr;
}

bool AttackItem::init()
{
	return true;
}
