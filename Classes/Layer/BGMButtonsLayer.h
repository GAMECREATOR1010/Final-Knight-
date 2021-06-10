#pragma once

#ifndef __BGMBUTTONS_LAYER_H__
#define __BGMBUTTONS_LAYER_H__

#include "cocos2d.h"
#include "BGM.h"
#include "ui/CocosGUI.h"
#include "source.h" 

using namespace cocos2d::ui;

class BGMLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    void SetPostionStartLayer(Button* BGMButton);

    void touchEvent(Ref* pSender, Widget::TouchEventType type);

    CREATE_FUNC(BGMLayer);
};


class SELayer : public cocos2d::Layer
{
public:
    virtual bool init();

    void SetPostionStartLayer(Button* SEButton);

    void touchEvent(Ref* pSender, Widget::TouchEventType type);

    CREATE_FUNC(SELayer);
};

#endif __BGMBUTTONS_LAYER_H__