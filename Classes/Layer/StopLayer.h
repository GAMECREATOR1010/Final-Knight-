/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:暂停内容

 API:在场景中添加暂停按钮请加入：
        #include "Layer/StopLayer.h"


        auto stopButton = StopButton::create();
        this->addChild(stopButton);
 ****************************************************************************/

#pragma once

#ifndef __STOP_LAYER_H__
#define __STOP_LAYER_H__

#include "cocos2d.h"
#include "Layer/TwoUseButtonsLayer.h"
#include "Scene/StartScene.h"
#include "source.h"
#include "Const.h" 

using namespace cocos2d::ui;


class StopButton : public cocos2d::Sprite
{
public:
    virtual bool init(EventListenerKeyboard& eventListener, Node& node);

    static StopButton* create(EventListenerKeyboard& eventListener, Node& node)
    {
        auto ret = new (std::nothrow) StopButton();
        if (ret && ret->init(eventListener,node))
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
    }
private:
    Sprite* _stopButton;
    EventListener* _listener;

};

class StopLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    void TouchEventResumeButton(Ref* pSender, Widget::TouchEventType type);
    void TouchEventHomeButton(Ref* pSender, Widget::TouchEventType type);
    void TouchEventSupremeButton(Ref* pSender, Widget::TouchEventType type);

    static StopLayer* create(EventListenerKeyboard& eventListener, Node& node)
    {
        auto ret = new (std::nothrow)StopLayer(eventListener,node);
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
    StopLayer(EventListenerKeyboard& eventListener, Node& node)
        : _stopLayer(Layer::create())
        , _node(node)
            , _eventListener(eventListener)
    {
    }
private:
    Layer* _stopLayer;
    Node& _node;
    EventListenerKeyboard& _eventListener;

};

#endif
