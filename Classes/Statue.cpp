/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 该部分为雕像
 ****************************************************************************/

#include "Statue.h"

Statue* Statue::create(StatueType type)
{
	auto pRet = new(std::nothrow) Statue();
	if (pRet && pRet->init(type))
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

bool Statue::init(StatueType type)
{
	if (initWithFile(FILENAME))
	{
		_type = type;
		return true;
	}
	return false;
}