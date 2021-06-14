/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为NPC
 ****************************************************************************/

#include "NPC.h"

NPC* NPC::create(NpcId id)
{
	auto pRet = new(std::nothrow) NPC();
	if (pRet && pRet->init(id))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}

	return nullptr;
}

bool NPC::init(NpcId id)
{
	if (id == NPCCOUNT)
	{
		return false;
	}

	_id = id;
	switch (id)
	{
		case SHOPKEEPER:
			initWithFile(SHOPKEEPER_PATH);
			break;
		default:
			return false;
	}

	return true;
}