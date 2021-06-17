 /****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 �ò���Ϊ������
 ****************************************************************************/
#include "Chest.h"

bool Chest::init()
{

	return true;
}

WhiteChest* WhiteChest::create()
{
	auto pRet = new(std::nothrow) WhiteChest();
	if (pRet && pRet->init())
	{
		pRet->setTag(chestTag);
		pRet->setGlobalZOrder(shadeOrder);
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

/// <summary>
/// �򿪱��䣬������Ʒ/���������������Ʒ����Ҫ���ö�������
/// </summary>
/// <returns>���ɵ���Ʒ����ָ�룬���ɽ���������ؿ�</returns>
Item* WhiteChest::open(Knight* activer)
{
	if (_isOpened)
	{
		return nullptr;
	}
	_isOpened = true;
	this->setVisible(false);
	/* ����Ч���������� */

	/* �ı���� */

	/* ������� */
	int type = random(1, 5);
	switch (type)
	{
		case 1:	//���ɽ�Һ�����
			goldMoney.ChangeBalance(MONEY_EVERY_ROOM * MONEY_LEVEL_MUTI);
			activer->EnergyNowChange(MANA_EVERY_ROOM * MANA_LEVEL_MUTI);
			return nullptr;
		case 2:	//����HPҩˮ
		{
			auto hp = HealPotion::create(SMALL);
			hp->setTag(potionChestTag);
			return hp;
		}
		case 3:	//����MPҩˮ
		{
			auto mp = ManaPotion::create(SMALL);
			mp->setTag(potionChestTag);
			return mp;
		}
		case 4:	//��������
		{
			auto wp = RandomWeaponCreate();
			wp->setTag(weaponTag);
			return wp;
		}
		default:
			throw("No such type in chest");
			break;
	}
}

/// <summary>
/// ���ͼƬ�������ײ��Χ
/// </summary>
/// <returns></returns>
bool WhiteChest::init()
{
	if (!initWithFile(WHITE_CHEST_PATH) && !Chest::init())
	{
		return false;
	}
	/* �����ײ��Χ */
	auto phy = PhysicsBody::createCircle(80.0, PhysicsMaterial(0.0, 0.0, 0.0));
	SetBody(phy, ItemCate);
	addComponent(phy);

	return true;
}