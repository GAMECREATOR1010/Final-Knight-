/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/
#pragma once


#include "General.h"
#include "Money.h"
#include "Layer/BloodLayer.h"
#include "Layer/ContactLayer.h"
#include "Layer/StopLayer.h"

class MainUILayer : public cocos2d::Layer
{
public:

    virtual bool init();

    static MainUILayer* create()
    {
        auto ret = new (std::nothrow) MainUILayer();
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
    static void ChangeCoinLabel();
    void AddStuff(EventListenerKeyboard& eventListener, Node& node, Knight& kinght);
    BloodLayer* _bloodLayer;

protected:
    MainUILayer()
        : _bloodLayer(BloodLayer::create())
    {
    }

};

static class CoinLabel
{
public:
    void AddStuff(Sprite* coinFrame);
    void Change();
    Label* GetLabel()
    {
        return _label;
    }
private:
    Label* _label;
    float _x;
    float _y;
}coinLabel;



