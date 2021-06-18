/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/
#pragma once


#include "cocos2d.h"
#include "source.h" 
#include "General.h"
#include "ui/CocosGUI.h"
#include "BloodLayer.h"
#include "StopLayer.h"

class MainUILayer : public cocos2d::Layer
{
public:

    virtual bool init(EventListenerKeyboard& eventListener,Node& node);

    static MainUILayer* create(EventListenerKeyboard& eventListener, Node& node)
    {
        auto ret = new (std::nothrow) MainUILayer();
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
};