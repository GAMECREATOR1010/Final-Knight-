#include "Weapon.h"

Weapon* Weapon::create(int id)
{
	Weapon* wea = new Weapon;
	if (wea != nullptr && wea->init(id))
	{
		wea->autorelease();
		return wea;
	}
	CC_SAFE_DELETE(wea);
	return nullptr;
}

bool Weapon::init(int id)
{
	bulletType = id;
	if (id < 5)
		attackMode = meleeMode;
	else
		attackMode = gunMode;


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

