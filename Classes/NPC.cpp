/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-26)
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