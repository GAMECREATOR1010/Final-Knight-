/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:°²È«³¡¾°
 ****************************************************************************/

#include "SafeScene.h"
USING_NS_CC;

Scene* SafeScene::createScene()
{
	return SafeScene::create();
}

void SafeScene::problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SafeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();

	{
		//ÏÔÊ¾±³¾°Í¼Æ¬
		auto back = Sprite::create(s_P_BackGround);
		if (back == nullptr)
		{
			problemLoading(s_P_BackGround);
		}
		else
		{
			float scaledPre = visibleSize.width / (back->getContentSize().width);
			back->setScale(scaledPre);
			back->setPosition(Vec2(visibleSize / 2) + originSize);
			this->addChild(back);
		}
	}

	float x = 0;
	float y = 0;

	auto enemyFrame = Sprite::create(s_P_EnemyFrame);
	auto knightFrame = Sprite::create(s_P_KnightFrame);
	auto weaponFrame = Sprite::create(s_P_WeaponFrame);
	enemyFrame->setAnchorPoint(Vec2(0, 0.5));
	knightFrame->setAnchorPoint(Vec2(0, 0.5));
	weaponFrame->setAnchorPoint(Vec2(0, 0.5));
	float gap = (visibleSize.width - enemyFrame->getContentSize().width * 3) / 4;
	x = gap + originSize.x;
	y = visibleSize.height * 3 / 5 + originSize.y;
	enemyFrame->setPosition(x, y);
	knightFrame->setPosition(x + enemyFrame->getContentSize().width + gap, y);
	weaponFrame->setPosition(x + enemyFrame->getContentSize().width * 2 + gap * 2, y);
	addChild(enemyFrame);
	addChild(knightFrame);
	addChild(weaponFrame);

	{
		Button* enemyButton = Button::create(s_P_EnemyButton);
		enemyButton->setAnchorPoint(Vec2(0.5, 0.5));

		enemyButton->ignoreContentAdaptWithSize(false);
		enemyButton->setScale9Enabled(true);
		enemyButton->setPressedActionEnabled(false);
		enemyButton->addTouchEventListener(CC_CALLBACK_2(SafeScene::TouchEventEnemyButton, this));
		x += enemyFrame->getContentSize().width / 2;
		y -= (enemyFrame->getContentSize().height / 2 + enemyButton->getContentSize().height + ButtonHeightGap);
		enemyButton->setPosition(Vec2(x, y));
		enemyButton->setGlobalZOrder(uiOrder);
		addChild(enemyButton);
	}
	{
		Button* knightButton = Button::create(s_P_KnightButton);
		knightButton->setAnchorPoint(Vec2(0.5, 0.5));

		knightButton->ignoreContentAdaptWithSize(false);
		knightButton->setScale9Enabled(true);
		knightButton->setPressedActionEnabled(false);
		knightButton->addTouchEventListener(CC_CALLBACK_2(SafeScene::TouchEventKnightButton, this));

		knightButton->setPosition(Vec2(x + enemyFrame->getContentSize().width + gap, y));
		knightButton->setGlobalZOrder(uiOrder);
		addChild(knightButton);
	}
	{
		Button* weaponButton = Button::create(s_P_WeaponButton);
		weaponButton->setAnchorPoint(Vec2(0.5, 0.5));

		weaponButton->ignoreContentAdaptWithSize(false);
		weaponButton->setScale9Enabled(true);
		weaponButton->setPressedActionEnabled(false);
		weaponButton->addTouchEventListener(CC_CALLBACK_2(SafeScene::TouchEventWeaponButton, this));

		weaponButton->setPosition(Vec2(x + enemyFrame->getContentSize().width * 2 + gap * 2, y));
		weaponButton->setGlobalZOrder(uiOrder);
		addChild(weaponButton);
	}
	return true;
}

void SafeScene::TouchEventEnemyButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->pushScene(EnemyScene::create());
		}
		break;

		default:
			break;
	}
	return;
}

void SafeScene::TouchEventKnightButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->pushScene(KnightScene::create());
		}
		break;

		default:
			break;
	}
	return;
}

void SafeScene::TouchEventWeaponButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->pushScene(WeaponScene::create());
		}
		break;

		default:
			break;
	}
	return;
}

bool KnightScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();
	{
		//ÏÔÊ¾±³¾°Í¼Æ¬
		auto back = Sprite::create(s_P_BackGround);
		float scaledPre = visibleSize.width / (back->getContentSize().width);
		back->setScale(scaledPre);
		back->setPosition(Vec2(visibleSize / 2) + originSize);
		this->addChild(back);
	}
	{
		auto knight0 = MenuItemImage::create(s_P_Knight0, s_P_Knight0, CC_CALLBACK_1(KnightScene::StartGame0, this));
		auto knight1 = MenuItemImage::create(s_P_Knight1, s_P_Knight1, CC_CALLBACK_1(KnightScene::StartGame1, this));
		auto knight2 = MenuItemImage::create(s_P_Knight2, s_P_Knight2, CC_CALLBACK_1(KnightScene::StartGame2, this));
		auto knight3 = MenuItemImage::create(s_P_Knight3, s_P_Knight3, CC_CALLBACK_1(KnightScene::StartGame3, this));
		auto knight4 = MenuItemImage::create(s_P_Knight4, s_P_Knight4, CC_CALLBACK_1(KnightScene::StartGame4, this));
		auto knight5 = MenuItemImage::create(s_P_Knight5, s_P_Knight5, CC_CALLBACK_1(KnightScene::StartGame5, this));
		auto knight6 = MenuItemImage::create(s_P_Knight6, s_P_Knight6, CC_CALLBACK_1(KnightScene::StartGame6, this));
		auto knight7 = MenuItemImage::create(s_P_Knight7, s_P_Knight7, CC_CALLBACK_1(KnightScene::StartGame7, this));

		float sc = visibleSize.width * KnightPre / knight0->getContentSize().width;
		knight0->setScale(sc);
		sc = visibleSize.width * KnightPre / knight1->getContentSize().width;
		knight1->setScale(sc);
		sc = visibleSize.width * KnightPre / knight2->getContentSize().width;
		knight2->setScale(sc);
		sc = visibleSize.width * KnightPre / knight3->getContentSize().width;
		knight3->setScale(sc);
		sc = visibleSize.width * KnightPre / knight4->getContentSize().width;
		knight4->setScale(sc);
		sc = visibleSize.width * KnightPre / knight5->getContentSize().width;
		knight5->setScale(sc);
		sc = visibleSize.width * KnightPre / knight6->getContentSize().width;
		knight6->setScale(sc);
		sc = visibleSize.width * KnightPre / knight7->getContentSize().width;
		knight7->setScale(sc);

		float padding1 = Pad1;
		float padding2 = Pad2;

		auto menu1 = Menu::create(knight0, knight1, knight2, nullptr);
		auto menu2 = Menu::create(knight3, knight4, knight5, nullptr);
		auto menu3 = Menu::create(knight6, knight7, nullptr);
		menu1->alignItemsHorizontallyWithPadding(padding1);
		menu2->alignItemsHorizontallyWithPadding(padding1);
		menu3->alignItemsHorizontallyWithPadding(padding2);

		float x = visibleSize.width / 2 + originSize.x;
		float gap = (visibleSize.height - knight0->getContentSize().height * 3) / 4;
		float y = gap + knight0->getContentSize().height / 2 + originSize.y + 30;

		menu1->setPosition(Vec2(x, y));
		menu2->setPosition(Vec2(x, y + gap + knight0->getContentSize().height));
		menu3->setPosition(Vec2(x, y + gap * 2 + knight0->getContentSize().height * 2));
		addChild(menu1);
		addChild(menu2);
		addChild(menu3);
	}
	{
		auto outButton = Button::create(s_P_OutButton);
		outButton->setAnchorPoint(Vec2(0, 1));

		outButton->ignoreContentAdaptWithSize(false);
		outButton->setScale9Enabled(true);
		outButton->setPressedActionEnabled(false);
		outButton->addTouchEventListener(CC_CALLBACK_2(KnightScene::TouchEventOutButton, this));

		float x = originSize.x + ButtonWidthGapInStop;
		float y = visibleSize.height + originSize.y - ButtonWidthGapInStop;
		outButton->setPosition(Vec2(x, y));
		this->addChild(outButton);
	}
	return true;
}

void KnightScene::TouchEventOutButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->popScene();
		}
		break;

		default:
			break;
	}
	return;
}

void KnightScene::StartGame0(Ref* sender)
{
	auto knight = Knight::create(0, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame1(Ref* sender)
{
	auto knight = Knight::create(1, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame2(Ref* sender)
{
	auto knight = Knight::create(2, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame3(Ref* sender)
{
	auto knight = Knight::create(3, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame4(Ref* sender)
{
	auto knight = Knight::create(4, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame5(Ref* sender)
{
	auto knight = Knight::create(5, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame6(Ref* sender)
{
	auto knight = Knight::create(6, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}
void KnightScene::StartGame7(Ref* sender)
{
	auto knight = Knight::create(7, 1);
	auto scene = Gaming::createScene(knight, 1);
	auto director = Director::getInstance();
	director->replaceScene(scene);
}

bool EnemyScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();
	{
		//ÏÔÊ¾±³¾°Í¼Æ¬
		auto back = Sprite::create(s_P_GuideFrame);
		float scaledPre = visibleSize.width / (back->getContentSize().width);
		back->setScale(scaledPre);
		back->setPosition(Vec2(visibleSize / 2) + originSize);
		this->addChild(back);
	}

	auto sprite = Sprite::create(s_P_StartEnemy);
	sprite->retain();
	sprite->setAnchorPoint(Vec2(0.5, 1));
	float x = visibleSize.width * 3 / 4 + originSize.x;
	float y = visibleSize.height + originSize.y - ButtonWidthGapInStop * 20;
	sprite->setPosition(Vec2(x, y));
	this->addChild(sprite);

	{
		auto enemy0 = Button::create(s_P_Enemy0);
		enemy0->setScale9Enabled(true);
		enemy0->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint0);
			});
		addChild(enemy0);

		auto enemy1 = Button::create(s_P_Enemy1);
		enemy1->setScale9Enabled(true);
		enemy1->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint1);
			});
		addChild(enemy1);

		auto enemy2 = Button::create(s_P_Enemy2);
		enemy2->setScale9Enabled(true);
		enemy2->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint2);
			});
		addChild(enemy2);

		auto enemy30 = Button::create(s_P_Enemy30);
		enemy30->setScale9Enabled(true);
		enemy30->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint30);
			});
		addChild(enemy30);

		auto enemy31 = Button::create(s_P_Enemy31);
		enemy31->setScale9Enabled(true);
		enemy31->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint31);
			});
		addChild(enemy31);

		auto enemy32 = Button::create(s_P_Enemy32);
		enemy32->setScale9Enabled(true);
		enemy32->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint32);
			});
		addChild(enemy32);

		auto enemy4 = Button::create(s_P_Enemy4);
		enemy4->setScale9Enabled(true);
		enemy4->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint4);
			});
		addChild(enemy4);

		auto enemy5 = Button::create(s_P_Enemy5);
		enemy5->setScale9Enabled(true);
		enemy5->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_EnemyHint5);
			});
		addChild(enemy5);

		float padding1 = (visibleSize.width / 2 - enemy0->getContentSize().width * 3) / 4;
		float padding2 = (visibleSize.width / 2 - enemy4->getContentSize().width * 2) / 3;

		float stuffw = enemy0->getContentSize().width;
		float stuffh = enemy0->getContentSize().height;

		float x = padding1 + stuffw / 2 + originSize.x;
		float gap = (visibleSize.height - enemy0->getContentSize().height * 3) / 4;
		float y = gap + stuffh / 2 + originSize.y;

		enemy0->setPosition(Vec2(x, y));
		enemy1->setPosition(Vec2(x + padding1 + stuffw, y));
		enemy2->setPosition(Vec2(x + (padding1 + stuffw) * 2, y));

		enemy30->setPosition(Vec2(x, y + gap + stuffh));
		enemy31->setPosition(Vec2(x + padding1 + stuffw, y + gap + stuffh));
		enemy32->setPosition(Vec2(x + (padding1 + stuffw) * 2, y + gap + stuffh));

		x = padding2 + stuffw / 2 + originSize.x;
		enemy4->setPosition(Vec2(x, y + gap * 2 + stuffh * 2));
		enemy5->setPosition(Vec2(x + padding1 + stuffw, y + gap * 2 + stuffh * 2));
	}
	{
		auto outButton = Button::create(s_P_OutButton);
		outButton->setAnchorPoint(Vec2(0, 1));

		outButton->ignoreContentAdaptWithSize(false);
		outButton->setScale9Enabled(true);
		outButton->setPressedActionEnabled(false);
		outButton->addTouchEventListener(CC_CALLBACK_2(EnemyScene::TouchEventOutButton, this));

		float x = originSize.x + ButtonWidthGapInStop * 3;
		float y = visibleSize.height + originSize.y - ButtonWidthGapInStop * 2;
		outButton->setPosition(Vec2(x, y));
		this->addChild(outButton);
	}
	return true;
}

void EnemyScene::TouchEventOutButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->popScene();
		}
		break;

		default:
			break;
	}
	return;
}

bool WeaponScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();

	{
		//ÏÔÊ¾±³¾°Í¼Æ¬
		auto back = Sprite::create(s_P_GuideFrame);
		float scaledPre = visibleSize.width / (back->getContentSize().width);
		back->setScale(scaledPre);
		back->setPosition(Vec2(visibleSize / 2) + originSize);
		this->addChild(back);
	}
	auto sprite = Sprite::create(s_P_StartWeapon);
	sprite->retain();
	sprite->setAnchorPoint(Vec2(0.5, 1));
	float x = visibleSize.width * 3 / 4 + originSize.x;
	float y = visibleSize.height + originSize.y - ButtonWidthGapInStop * 20;
	sprite->setPosition(Vec2(x, y));
	addChild(sprite);
	{
		auto weapon0 = Button::create(s_P_Weapon0);
		weapon0->setScale9Enabled(true);
		weapon0->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint0);
			});
		addChild(weapon0);

		auto weapon1 = Button::create(s_P_Weapon1);
		weapon1->setScale9Enabled(true);
		weapon1->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint1);
			});
		addChild(weapon1);

		auto weapon2 = Button::create(s_P_Weapon2);
		weapon2->setScale9Enabled(true);
		weapon2->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint2);
			});
		addChild(weapon2);

		auto weapon3 = Button::create(s_P_Weapon3);
		weapon3->setScale9Enabled(true);
		weapon3->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint3);
			});
		addChild(weapon3);

		auto weapon4 = Button::create(s_P_Weapon4);
		weapon4->setScale9Enabled(true);
		weapon4->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint4);
			});
		addChild(weapon4);

		auto weapon5 = Button::create(s_P_Weapon5);
		weapon5->setScale9Enabled(true);
		weapon5->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint5);
			});
		addChild(weapon5);

		auto weapon6 = Button::create(s_P_Weapon6);
		weapon6->setScale9Enabled(true);
		weapon6->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint6);
			});
		addChild(weapon6);

		auto weapon7 = Button::create(s_P_Weapon7);
		weapon7->setScale9Enabled(true);
		weapon7->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint7);
			});
		addChild(weapon7);

		auto weapon8 = Button::create(s_P_Weapon8);
		weapon8->setScale9Enabled(true);
		weapon8->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint8);
			});
		addChild(weapon8);

		auto weapon9 = Button::create(s_P_Weapon9);
		weapon9->setScale9Enabled(true);
		weapon9->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint9);
			});
		addChild(weapon9);

		auto weapon10 = Button::create(s_P_Weapon10);
		weapon10->setScale9Enabled(true);
		weapon10->addClickEventListener([sprite](Ref* button) {
			se._audioID = se.play2d(s_M_ButtonSelected);
			sprite->setTexture(s_P_WeaponHint10);
			});
		addChild(weapon10);

		float padding1 = (visibleSize.width / 2 - weapon0->getContentSize().width * 4) / 5;
		float padding2 = (visibleSize.width / 2 - weapon4->getContentSize().width * 3) / 4;

		weapon0->setScale(1.7f);
		weapon1->setScale(1.7f);
		weapon2->setScale(1.7f);
		weapon3->setScale(1.7f);
		weapon4->setScale(1.7f);
		weapon5->setScale(1.7f);
		weapon6->setScale(1.7f);
		weapon7->setScale(1.7f);
		weapon8->setScale(1.7f);
		weapon9->setScale(1.7f);
		weapon10->setScale(1.7f);

		float stuffw = weapon0->getContentSize().width;
		float stuffh = weapon0->getContentSize().height;
		float x = padding1 + weapon0->getContentSize().width / 2 + originSize.x;
		float gap = (visibleSize.height - weapon0->getContentSize().height * 3) / 4;
		float y = gap + weapon0->getContentSize().height / 2 + originSize.y;

		weapon0->setPosition(Vec2(x, y));
		weapon1->setPosition(Vec2(x + padding1 + stuffw, y));
		weapon2->setPosition(Vec2(x + (padding1 + stuffw) * 2, y));
		weapon3->setPosition(Vec2(x + (padding1 + stuffw) * 3, y));

		x = padding2 + weapon0->getContentSize().width / 2 + originSize.x;
		weapon4->setPosition(Vec2(x, y + gap + stuffh));
		weapon5->setPosition(Vec2(x + padding2 + stuffw, y + gap + stuffh));
		weapon6->setPosition(Vec2(x + (padding2 + stuffw) * 2, y + gap + stuffh));

		x = padding1 + weapon0->getContentSize().width / 2 + originSize.x;
		weapon7->setPosition(Vec2(x, y + gap * 2 + stuffh * 2));
		weapon8->setPosition(Vec2(x + padding1 + stuffw, y + gap * 2 + stuffh * 2));
		weapon9->setPosition(Vec2(x + (padding1 + stuffw) * 2, y + gap * 2 + stuffh * 2));
		weapon10->setPosition(Vec2(x + (padding1 + stuffw) * 3, y + gap * 2 + stuffh * 2));
	}
	{
		auto outButton = Button::create(s_P_OutButton);
		outButton->setAnchorPoint(Vec2(0, 1));

		outButton->ignoreContentAdaptWithSize(false);
		outButton->setScale9Enabled(true);
		outButton->setPressedActionEnabled(false);
		outButton->addTouchEventListener(CC_CALLBACK_2(WeaponScene::TouchEventOutButton, this));

		float x = originSize.x + ButtonWidthGapInStop * 3;
		float y = visibleSize.height + originSize.y - ButtonWidthGapInStop * 2;
		outButton->setPosition(Vec2(x, y));
		this->addChild(outButton);
	}
	return true;
}

void WeaponScene::TouchEventOutButton(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			se._audioID = se.play2d(s_M_ButtonSelected);
			Director::getInstance()->popScene();
		}
		break;

		default:
			break;
	}
	return;
}