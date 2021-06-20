#include "Knight.h"
USING_NS_CC;

Knight* Knight::create(int type, int rank)
{
	Knight* knight = new Knight;
	if (knight != nullptr && knight->init(type, rank))
	{
		knight->autorelease();
		return knight;
	}
	CC_SAFE_DELETE(knight);
	return nullptr;
}

bool Knight::init(int type, int Firstrank)
{
	rank = Firstrank;
	knightType = type;
	damageMax = 1;
	wea1 = nullptr;
	state = KnightIdle;
	body = PhysicsBody::create();
	auto spritecache = SpriteFrameCache::getInstance();
	if (type == 0)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_0.plist");
		auto frames = GetAnim("knight0%02d.png", 2);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 4);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.7f, 0.6f));
		HPMax = 40;
		defenceMax = 1.5;
		attackMode = gunEnum;

		auto shape = PhysicsShapeBox::create(Size(45.0f, 40.0f));
		body->addShape(shape);

		AddShade(Vec2(-5, -40));
		wea = Weapon::create(5, KnightCate);
	}
	else if (type == 1)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_1.plist");
		auto frames = GetAnim("knight1%02d.png", 7);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));
		HPMax = 60;
		moveSpeedMax = 19;
		defenceMax = 2;
		attackRange = 1;
		attackMode = gunEnum;
		Vec2 verts[] = { Vec2(-27, -35), Vec2(-27,27), Vec2(27, 27),Vec2(27, -35) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -10);
		wea = Weapon::create(5, KnightCate);
		AddShade(Vec2(0, -50));
	}
	else if (type == 2)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_2.plist");
		auto frames = GetAnim("knight2%02d.png", 7);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));
		HPMax = 80;
		energyMax = 200;
		moveSpeedMax = 21;
		defenceMax = 1.5;
		attackMode = meleeEnum;
		attackSpeed = 2;
		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,24), Vec2(27, 24),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -5);
		wea = Weapon::create(0, KnightCate);
		AddShade(Vec2(0, -45));
	}
	else if (type == 3)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_3.plist");
		auto frames = GetAnim("knight3%02d.png", 7);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));
		HPMax = 40;
		moveSpeedMax = 13;
		defenceMax = 1.5;
		attackMode = gunEnum;
		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,20), Vec2(27,20),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -5);
		wea = Weapon::create(8, KnightCate);
		wea->costEnergy = 2;
		AddShade(Vec2(0, -45));
	}
	else if (type == 4)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_4.plist");
		auto frames = GetAnim("knight4%02d.png", 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));
		HPMax = 80;
		energyMax = 170;
		moveSpeedMax = 19;
		defenceMax = 2;
		attackMode = gunEnum;
		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,20), Vec2(27,20),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -5);
		wea = Weapon::create(7, KnightCate);
		wea->costEnergy = 2;
		AddShade(Vec2(0, -45));
	}
	else if (type == 5)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_5.plist");
		auto frames = GetAnim("knight5%02d.png", 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.7f));

		HPMax = 70;
		moveSpeedMax = 21;
		defenceMax = 2;
		attackSpeed = 2;
		attackRange = 1;
		attackMode = meleeEnum;
		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,20), Vec2(27,20),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(5, -15);
		wea = Weapon::create(3, KnightCate);
		AddShade(Vec2(0, -50));
	}
	else if (type == 6)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_6.plist");
		auto frames = GetAnim("knight6%02d.png", 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));

		HPMax = 70;
		moveSpeedMax = 21;
		defenceMax = 2.5;
		attackDistance = 2;
		attackMode = gunEnum;
		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,20), Vec2(27,20),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -10);
		wea = Weapon::create(6, KnightCate);
		AddShade(Vec2(0, -45));
	}
	else if (type == 7)
	{
		spritecache->addSpriteFramesWithFile("knight/knight_7.plist");
		auto frames = GetAnim("knight7%02d.png", 5);
		pic = Sprite::createWithSpriteFrame(frames.front());
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		addChild(pic);

		pic->setAnchorPoint(Vec2(0.5f, 0.65f));

		HPMax = 100;
		energyMax = 200;
		moveSpeedMax = 21;
		defenceMax = 2.5;
		attackMode = gunEnum;
		skillTime = 10.0f;

		Vec2 verts[] = { Vec2(-27, -40), Vec2(-27,20), Vec2(27,20),Vec2(27, -40) };
		body->addShape(PhysicsShapeEdgePolygon::create(verts, 4));

		bindPointOffSet = Vec2(0, -5);
		wea = Weapon::create(10, KnightCate);
		AddShade(Vec2(0, -45));
	}

	addChild(wea);
	wea->setPosition(wea->bindPoint + bindPointOffSet);
	wea->trigger->setEnabled(false);
	SetWeaponBuff(wea);

	energyMax += (rank - 1) * 5;

	HP = HPMax;
	moveSpeed = moveSpeedMax;
	defence = defenceMax;
	energyNow = energyMax;
	damage = damageMax;

	pic->setGlobalZOrder(knightOrder);
	body->setDynamic(false);
	addComponent(body);
	SetBody(body, KnightCate);
	setTag(knightTag);
	return true;
}

void Knight::EnergyMaxChange(float energychange)
{
	energyMax += energychange;
	energyNow = energyMax;
}

void Knight::EnergyNowChange(float energychange)
{
	if (energyNow + energychange <= energyMax)
	{
		energyNow += energychange;
	}
	else
	{
		energyNow = energyMax;
	}
}

float Knight::GetEnergyNow()
{
	return energyNow;
}

float Knight::GetEnergyMax()
{
	return energyMax;
}

int Knight::GetRank()
{
	return rank;
}

void Knight::LevelUp()
{
	energyMax += 5;
	energyNow = energyMax;
}

void Knight::AddEXP(int addEXP)
{
	EXP += addEXP;
	if (EXP / 20 > rank)
	{
		rank += 1;
		LevelUp();
	}
}

void Knight::MyAttack()
{
	if (this->state != KnightAttack && (energyNow - wea->costEnergy) >= 0)
	{
		this->state = KnightAttack;
		energyNow -= wea->costEnergy;
		auto attacking = CallFunc::create([&]() {
			wea->WeaponAttack(this->faceDir, inRoom, getPosition() - inRoom->roomPosition - inRoom->getParent()->getPosition());
			});
		auto attackEnd = CallFunc::create([&]() {
			this->state = KnightIdle;
			});
		auto delay = DelayTime::create(wea->perTime);
		auto myseq = Sequence::create(attacking, delay, attackEnd, nullptr);
		this->runAction(myseq);
	}
}

Sprite* CreateDice(int dice)
{
	std::string  path = "dice/dice0";
	std::string count = StringUtils::toString(dice);
	std::string filename = path + count + ".png";
	auto Dice = Sprite::create(filename);
	Dice->setGlobalZOrder(uiOrder);
	return Dice;
}

void Knight::LaunchSkillTime()
{
	if (knightType > 0 && energyNow >= skillCostEnergy)
	{
		if (launchSkill == false)
		{
			launchSkill = true;
			energyNow -= skillCostEnergy;

			int diceOne = random(1, 6);
			diceSpriteOne = CreateDice(diceOne);
			addChild(diceSpriteOne);
			diceSpriteOne->setPosition(Vec2(-35, 70));

			int diceTwo = random(1, 6);
			diceSpriteTwo = CreateDice(diceTwo);
			addChild(diceSpriteTwo);
			diceSpriteTwo->setPosition(Vec2(35, 70));

			auto diceDelay = DelayTime::create(0.7f);
			auto diceRecovery = CallFunc::create([&]() {
				diceSpriteOne->removeFromParentAndCleanup(true);
				diceSpriteTwo->removeFromParentAndCleanup(true);
				});
			auto diceAction = Sequence::create(diceDelay, diceRecovery, nullptr);
			runAction(diceAction);

			if (knightType == 1)
			{
				HPNowChange(diceOne + diceTwo);
			}
			else if (knightType == 2)
			{
				HPNowChange(diceOne * diceTwo);
			}
			else if (knightType == 3)
			{
				MoveSpeedNowChange(diceOne + diceTwo, 3.0f);
			}
			else if (knightType == 4)
			{
				EnergyNowChange(diceOne * diceTwo);
			}
			else if (knightType == 5)
			{
				EnergyNowChange(diceOne + diceTwo);
			}
			else if (knightType == 6)
			{
				AttackDistanceChange((diceOne + diceTwo) * 0.1, 5.0f);
			}
			else if (knightType == 7)
			{
				InvincibleTimeChange((diceOne + diceTwo) * 0.1, 10.0f);
			}

			auto delay = DelayTime::create(skillTime);
			auto recovery = CallFunc::create([&]() {
				launchSkill = false;
				});
			auto seq = Sequence::create(delay, recovery, nullptr);
			runAction(seq);
		}
	}
}