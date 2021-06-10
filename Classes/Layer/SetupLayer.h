/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:…Ë÷√ƒ⁄»›
 ****************************************************************************/
#pragma once

#ifndef __SETUP_LAYER_H__
#define __SETUP_LAYER_H__

#include "cocos2d.h"
#include "BGM.h"
#include "ui/CocosGUI.h"
#include "source.h" 

using namespace cocos2d::ui;

class SetupLayerStart : public cocos2d::Layer
{
public:
    virtual bool init();
    void StopCallBack(Ref* sendef);
    CREATE_FUNC(SetupLayerStart);
};

class SetupLayer : public SetupLayerStart
{
public:
    virtual bool init();

    CREATE_FUNC(SetupLayerStart);
};


class BGMLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void SetPostionStartLayer(Button* BGMButton, float x, float y);
    void touchEvent(Ref* pSender, Widget::TouchEventType type);
    CREATE_FUNC(BGMLayer);
};


class SELayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void SetPostionStartLayer(Button* SEButton, float x, float y);
    void touchEvent(Ref* pSender, Widget::TouchEventType type);
    CREATE_FUNC(SELayer);
};

#endif __SETUP_LAYER_H__