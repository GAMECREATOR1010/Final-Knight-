#include "Enemy.h"
USING_NS_CC;

Enemy* Enemy::create(int type, bool ifboss)
{
	Enemy* enemy = new Enemy;
	if (enemy != nullptr && enemy->init(type, ifboss))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool Enemy::init(int type, bool ifboss)
{
	state = EnemyIdle;
	attackMode = touchEnum;
	body = PhysicsBody::create();
	if (type == 0)
	{
		auto frames = GetAnim("enemy%02d.png", 5);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));

		moveSpeed = 200;
		attackMode = touchEnum;
		wea = nullptr;
		AddShade(Vec2(0, -27));
	}
	else if (type == 1)/*鬼魂*/
	{
		auto frames = GetAnim("enemy1%02d.png", 9);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));

		chaseDistance = 64 * 10;
		moveSpeed = 300;
		maxHP = 6;
		HP = 6;
		AddEXP = 2;
		wea = nullptr;
		AddShade(Vec2(0, -27));
		auto delayBetweenAppear = DelayTime::create(1.0f);
		auto Appear = CallFunc::create([&]() {
			if (!death)
			{
				pic->setOpacity(255);
				body->setEnabled(true);
			}
			});
		auto Disappear = CallFunc::create([&]() {
			if (!death)
			{
				body->setEnabled(false);
				pic->setOpacity(30);
			}
			});
		auto ghostSkill = Sequence::create(Appear, delayBetweenAppear, Disappear, delayBetweenAppear, nullptr);
		auto repeat = RepeatForever::create(ghostSkill);
		runAction(repeat);
	}
	else if (type == 2)/*烦人但杀不死我的南瓜人*/
	{
		auto frames = GetAnim("enemy2%02d.png", 9);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));

		chaseDistance = 64 * 12;
		moveSpeed = 400;
		damage = 0;
		wea = nullptr;
		AddShade(Vec2(0, -40));
	}
	else if (type == 3)
	{
		int i = random(0, 3);
		auto frames = GetAnim("enemy30%02d.png",5);
		if (i == 0)
		{
			wea = nullptr;
			moveSpeed = 250;
		}
		else if (i == 1)
		{
			frames = GetAnim("enemy31%02d.png", 5);
			
			wea = Weapon::create(random(0,2), EnemyCate);
			addChild(wea);
			wea->setPosition(wea->bindPoint);
			attackDelayTime = 1.5f;

			chaseDistance = 64 * 8;
			attackDistance = 64 * 6;
			moveSpeed = 270;
		}
		else
		{
			frames = GetAnim("enemy32%02d.png", 5);

			wea = Weapon::create(random(5, 7), EnemyCate);
			addChild(wea);
			wea->setPosition(wea->bindPoint);
			wea->countPerTime = random(1, 3);
			attackDelayTime = 1.5f;
			moveSpeed = 300;
			chaseDistance = 64 * 12;
			attackDistance = 64 * 9;
		}
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		AddShade(Vec2(-5, -40));
	}

	pic->setGlobalZOrder(knightOrder);
	body->addShape(PhysicsShapeBox::create(pic->getContentSize()));
	body->setRotationEnable(false);
	addChild(pic);
	addComponent(body);
	SetBody(getPhysicsBody(), EnemyCate);
	setTag(enemyTag);
	auto delay = DelayTime::create(0.3f);
	auto move = CallFunc::create([&]() {
		Movement();
		});
	auto enemySeq = Sequence::create(move, delay, nullptr);
	auto repeat = RepeatForever::create(enemySeq);
	runAction(repeat);

	return true;
}

int Enemy::GetEXP()
{
	return AddEXP;
}


void Enemy::Movement()
{
	if (inRoom->playerEnter && !death)
	{
		if (!inRoom->Movable(getPosition() + faceDir * 100, roomFloorGid))
		{
			HP -= 0.1;
			if (HP < 0)
				DeathEffect();
			else
			{
				body->setVelocity(Vec2(0,0));
				faceDir=ChangeDir();
				if(inRoom->Movable(getPosition() + faceDir * 200, roomFloorGid))
					body->setVelocity(faceDir*moveSpeed);
			}
		}
		else if (!target->death)
		{
			if (faceDir.x > 0)
				setScaleX(1.0f);
			else
				setScaleX(-1.0f);

			Vec2 pos = getPosition() + getParent()->getPosition() + getParent()->getParent()->getPosition();
			float disX = pos.x - target->getPositionX();
			float disY = pos.y - target->getPositionY();
			float dis = sqrt(disX * disX + disY * disY);

			if (dis >= chaseDistance)
			{
				state = EnemyWalk;
				if (time_count == 0.0f)
				{
					faceDir.x = rand_minus1_1() * 1.5;
					faceDir.y = rand_minus1_1() * 1.5;
					body->setVelocity(faceDir * moveSpeed);
				}
			}
			else if (dis < chaseDistance)
			{
				state = EnemyChase;
				if (disX > 0)
					faceDir.x = -1;
				else
					faceDir.x = 1;

				if (disY > 0)
					faceDir.y = -1;
				else
					faceDir.y = 1;
				body->setVelocity(faceDir * moveSpeed);
				if (dis < attackDistance)
				{
					state = EnemyAttack;
					if (time_count == 0.0f)
					{
						if (wea != nullptr)
							wea->WeaponAttack(faceDir);
					}
				}
			}
		}
		time_count += 0.3f;
		if (time_count > attackDelayTime)
			time_count = 0;
	}
}

