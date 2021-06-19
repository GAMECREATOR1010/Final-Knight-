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
		pRet->setGlobalZOrder(obstaclesOrder);
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

bool Statue::ActiveStatue(Knight* activer)
{
	if (goldMoney.ChangeBalance(-STATUE_COST));
	{
		switch (_type)
		{
			case WEREWOLF:
				activer->MoveSpeedNowChange(SPEED_BUFF);
				break;
			case PRIEST:
				activer->EnergyNowChange(MANA_MAXADD_BUFF);
				break;
			case KNIGHT:
				activer->DefenceNowChange(DEFENCE_BUFF);
				break;
			case THIEF:
			{
				auto curWp = activer->GetWea();
				curWp->SetDamageBuff(DAMAGE_BUFF);
			}
			break;
			case ELF:
				activer->HPMaxChange(HEALTH_MAXADD_BUFF);
				break;
				//case SORCERER:
				//	break;
				//case ASSASSIN:
				//	break;
				//case PALADIN:
				//	break;
				//case ENGINEER:
				//	break;
				//case BERSERKER:
				//	break;
				//case STATUECOUNT:
				//	break;
			default:
				throw("Statue::ActiveStatue failed");
				return false;
		}
		return true;
	}

	return false;
}

bool Statue::init(StatueType type)
{
	switch (type)
	{
		case WEREWOLF:
			initWithFile(WEREWOLF_PATH);
			break;
		case PRIEST:
			initWithFile(PRIEST_PATH);
			break;
		case KNIGHT:
			initWithFile(KNIGHT_PATH);
			break;
		case THIEF:
			initWithFile(THIEF_PATH);
			break;
		case ELF:
			initWithFile(ELF_PATH);
			break;
			//case SORCERER:
			//	break;
			//case ASSASSIN:
			//	break;
			//case PALADIN:
			//	break;
			//case ENGINEER:
			//	break;
			//case BERSERKER:
			//	break;
			//case STATUECOUNT:
			//	break;
		default:
			CCLOG("Statue::init: Statue create failed, because it has typeid %d",type);
			return false;
	}
	_type = type;
	this->setTag(statueTag);
	CCLOG("Statue::init: Statue create success, typeid %d", type);

	/* 添加碰撞范围 */
	auto phy = PhysicsBody::createCircle(_physicalRange);
	SetBody(phy, ObstaclesCate);
	addComponent(phy);

	return true;
}