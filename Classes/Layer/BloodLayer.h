/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:ÑªÌõÄÚÈÝ

 API:
 ****************************************************************************/
#pragma once

#ifndef __BLOOD_LAYER_H__
#define __BLOOD_LAYER_H__

#include "cocos2d.h"
#include "Knight.h"
#include "source.h" 


class UIItem
{
public:
    void AddStuff(Sprite* sprite, float now, float max);
    void SetPosition(float x, float y);
    void Change(float now, float max);

    Sprite* GetSprite();
    Label* GetLabel();
    Sprite* _sprite;
    Label* _label;
    float _now ;
    float _max ;
};

static class HP :public UIItem
{
public:
private:
}hp;

static  class DF :public UIItem
{
public:
private:
}df;

static  class MP :public UIItem
{
public:
private:
}mp;

class BloodLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    static  BloodLayer* create()
    {
        auto ret = new (std::nothrow)  BloodLayer();
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    void SetKnight(Knight& kinght);

    static void Change(Knight& kinght);
};

#endif __BLOOD_LAYER_H__