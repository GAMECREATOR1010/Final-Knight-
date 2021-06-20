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
	defenceMax = 1;
	if (type == 0)
	{
		auto frames = GetAnim("enemy%02d.png", 5);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		damage = 2;
		moveSpeedMax = 200;
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

		damage = 2.5f;
		chaseDistance = 64 * 10;
		moveSpeedMax = 280;
		HPMax = 6;
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
		moveSpeedMax = 300;
		damage = 0;
		wea = nullptr;
		AddShade(Vec2(0, -40));
	}
	else if (type == 3)
	{
		int i = random(0, 3);
		auto frames = GetAnim("enemy30%02d.png", 5);
		if (i == 0)
		{
			wea = nullptr;
			moveSpeedMax = 250;
			damage = 2.5;
		}
		else if (i == 1)
		{
			frames = GetAnim("enemy31%02d.png", 5);

			wea = Weapon::create(random(0, 2), EnemyCate);
			addChild(wea);
			wea->setPosition(wea->bindPoint);
			attackDelayTime = 1.5f;

			chaseDistance = 64 * 8;
			attackDistance = 64 * 5;
			moveSpeedMax = 270;
		}
		else
		{
			frames = GetAnim("enemy32%02d.png", 5);
			HPMax = 8;
			wea = Weapon::create(random(5, 7), EnemyCate);
			addChild(wea);
			wea->setPosition(wea->bindPoint);
			attackDelayTime = 1.7f;
			moveSpeedMax = 250;
			chaseDistance = 64 * 10;
			attackDistance = 64 * 10;
		}
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));
		AddShade(Vec2(-5, -30));
	}
	else if (type == 4)
	{
		auto frames = GetAnim("enemy4%02d.png", 5);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));

		HPMax = 7;
		chaseDistance = 64 * 8;
		attackDistance = 64 * 8;
		moveSpeedMax = 200;
		damage = 2.5;
		wea = Weapon::create(random(5, 6), EnemyCate);
		addChild(wea);
		wea->setPosition(wea->bindPoint);
		AddShade(Vec2(0, -30));
	}
	else if (type == 5)
	{
		auto frames = GetAnim("enemy5%02d.png", 6);
		auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 5);
		pic = Sprite::createWithSpriteFrame(frames.front());
		pic->runAction(RepeatForever::create(Animate::create(animation)));

		HPMax = 60;
		chaseDistance = 64 * 12;
		attackDistance = 64 *10;
		attackSpeed = -2.0f;
		moveSpeedMax = 170;
		attackDelayTime = 3.0f;
		damage = 4;
		wea = Weapon::create(random(7, 9), EnemyCate);
		addChild(wea);
		wea->setPosition(wea->bindPoint);
		wea->setVisible(false);
		AddShade(Vec2(0, -50));
	}

	defence = defenceMax;
	HP = HPMax;
	moveSpeed = moveSpeedMax;
	pic->setGlobalZOrder(shadeOrder);
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
		if (!inRoom->Movable(getPosition() + faceDir * 170, roomFloorGid))
		{

			body->setVelocity(Vec2(0, 0));
			faceDir = ChangeDir();
			if ((inRoom->Movable(getPosition() + faceDir * 200, roomFloorGid)) || (inRoom->Movable(getPosition() + faceDir * 60, roomFloorGid)))
			{
				body->setVelocity(faceDir * moveSpeed);
			}

		}
		else if (!target->death)
		{
			if (faceDir.x > 0)
				setScaleX(1.0f);
			else
				setScaleX(-1.0f);

			Vec2 pos = getPosition() + getParent()->getPosition() + getParent()->getParent()->getPosition();
			Vec2 farDistance = target->getPosition() - pos;
			float dis = sqrt(farDistance.x * farDistance.x + farDistance.y * farDistance.y);

			if (dis >= chaseDistance)
			{
				state = EnemyWalk;
				if (timeCount == 0.0f)
				{
					faceDir.x = rand_minus1_1() * 1.5;
					faceDir.y = rand_minus1_1() * 1.5;
					body->setVelocity(faceDir * moveSpeed);
				}
			}
			else if (dis < chaseDistance)
			{
				state = EnemyChase;

				faceDir = farDistance / dis;
				body->setVelocity(faceDir * moveSpeed);
				if (dis < attackDistance)
				{
					state = EnemyAttack;
					if (timeCount == 0.0f)
					{
						if (wea != nullptr)
							wea->WeaponAttack(faceDir, inRoom, getPosition());
					}
				}
			}
		}
		timeCount += 0.3f;
		if (timeCount > attackDelayTime)
			timeCount = 0;
	}
}

