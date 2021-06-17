/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:暂停内容

 API:在场景中添加暂停按钮请加入：
        auto stopButton = StopButton::create();
        this->addChild(stopButton);
 ****************************************************************************/

#pragma once

#ifndef __STOP_LAYER_H__
#define __STOP_LAYER_H__

#include "cocos2d.h"
#include "source.h" 
#include "Const.h"
#include "ui/CocosGUI.h"
#include "Layer/TwoUseButtonsLayer.h"
#include "Scene/StartScene.h"
#include "BGM.h"

using namespace cocos2d::ui;

class StopButton : public cocos2d::Sprite
{
public:
    virtual bool init();

    static StopButton* create()
    {
        auto ret = new (std::nothrow) StopButton();
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

protected:
    StopButton()
        : _stopButton(Sprite::create(s_P_StopButton))
        , _listener(nullptr)
    {

        if (_stopButton == nullptr ||
            _stopButton->getContentSize().width <= 0 ||
            _stopButton->getContentSize().height <= 0)
        {
            problemLoading("'s_P_BGMButton' and 's_P_BGMButtonSelected'");
        }
    }
private:
    Sprite* _stopButton;
    EventListener* _listener;

};

class StopLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    void touchEventResumeButton(Ref* pSender, Widget::TouchEventType type);
    void touchEventHomeButton(Ref* pSender, Widget::TouchEventType type);

    static StopLayer* create()
    {
        auto ret = new (std::nothrow)StopLayer();
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

protected:
     StopLayer()
        : _stopLayer(Layer::create())
    {
    }
private:
    Layer* _stopLayer;

};

#endif __STOP_LAYER_H__

