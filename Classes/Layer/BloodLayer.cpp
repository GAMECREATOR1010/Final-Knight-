/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:ÑªÌõÄÚÈÝ

 ****************************************************************************/
#include "BloodLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;



void UIItem::AddStuff(Sprite* sprite, float now, float max)
{
    _sprite = sprite;
    _now = now;
    _max = max;
    char string[30] = { 0 };
    sprintf(string, "%d/%d", (int)_now, (int)_max);
    _label = Label::createWithTTF(string, s_T_Pixeboy, 25);

    float precen = now / max;
    _sprite->setScaleX(precen);
    _sprite->setGlobalZOrder(uiOrder);
    _sprite->setAnchorPoint(Vec2(0, 1));

    _label->setGlobalZOrder(uiOrder);
}

Sprite* UIItem::GetSprite()
{
    return _sprite;
}
Label* UIItem::GetLabel()
{
    return _label;
}

void UIItem::SetPosition(float x, float y)
{
    _sprite->setPosition(x, y);
    float x_lab = x + _sprite->getContentSize().width / 2;
    float y_lab = y - _sprite->getContentSize().height / 2;
    _label->setPosition(x_lab, y_lab);
}


void UIItem::Change(float now, float max)
{
    _now = now;
    _max = max;
    float precen = now / max;
    _sprite->setScaleX(precen);
    char string[30] = { 0 };
    sprintf(string, "%d/%d", (int)_now, (int)_max);
    _label->setString(string);
}



bool BloodLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    {
        //ÏÔÊ¾±³¾°Í¼Æ¬
        auto bloodFrame = Sprite::create(s_P_BloodFrame);
        float x = bloodFrame->getContentSize().width / 2 + originSize.x;
        float y = visibleSize.height - bloodFrame->getContentSize().height / 2 + originSize.y;
        bloodFrame->setPosition(x, y);
        bloodFrame->setGlobalZOrder(uiOrder);
        this->addChild(bloodFrame);

    }

    return true;
}


void BloodLayer::SetKnight(Knight& kinght)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();



    {
        float x = BloodUIx + originSize.x;
        float y = visibleSize.height - BloodUIy + originSize.y;

        if (hp.GetSprite()==nullptr)
        {
            hp.AddStuff(Sprite::create(s_P_HPUI), kinght.GetHP(), kinght.GetHPMax());
            df.AddStuff(Sprite::create(s_P_DFUI), kinght.GetDefence(), kinght.GetDefenceMax());
            mp.AddStuff(Sprite::create(s_P_MPUI), kinght.GetEnergyNow(), kinght.GetEnergyMax());
        }

        Change(kinght);

    
        hp.SetPosition(x, y);
        addChild(hp.GetSprite());
        addChild(hp.GetLabel());

        y -= BloodUIGap;
        df.SetPosition(x, y);
        addChild(df.GetSprite());
        addChild(df.GetLabel());

        y -= BloodUIGap;
        mp.SetPosition(x, y);
        addChild(mp.GetSprite());
        addChild(mp.GetLabel());
    }
}

void BloodLayer::Change(Knight& kinght)
{
    hp.Change(kinght.GetHP(), kinght.GetHPMax());
    df.Change(kinght.GetDefence(), kinght.GetDefenceMax());
    mp.Change(kinght.GetEnergyNow(), kinght.GetEnergyMax());
}