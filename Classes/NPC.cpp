/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w21a (2021-5-26)
 ****************************************************************************/

#include "NPC.h"

NPC* NPC::create(int id)
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

bool NPC::init(int id)
{
	/* �����Ӧ��NPC���ܶ��弰ͼƬ���� */
	if (initWithFile(FileName))
	{
		_id = id;
		return true;
	}
	return false;
}
