/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:可在开始界面和暂停界面显示的按钮：
            BGMButton 、 SEButton  、InfoButton
            及 InfoScene 的内容
 ****************************************************************************/

#pragma once

#ifndef __TWOUSE_BUTTONS_LAYER_H__
#define __TWOUSE_BUTTONS_LAYER_H__

#include "BGM.h"
#include "source.h" 
#include "Const.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

static void problemLoading(const char* filename);

class BGMButton : public Sprite
{
public:
    virtual bool init();

    void SetPostionStartLayer();
    void SetPostionStopLayer(Sprite*  sprite);

    static BGMButton* create()
    {
        auto ret = new (std::nothrow) BGMButton();
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

    EventListener* getListener()
    {
        return _listener;
    }
protected:
    BGMButton()
    {

        if (bgm.GetIfon() == false)//如果BGM没有播放，则设置为选下
        {
            _bgmButton = Sprite::create(s_P_BGMButtonSelected);
        }
        else
        {
            _bgmButton = Sprite::create(s_P_BGMButton);
        }
        _listener = nullptr;
    }
private:
    Sprite* _bgmButton;
    EventListener* _listener;
};


class SEButton : public cocos2d::Sprite
{
public:
    virtual bool init();

    void SetPostionStartLayer();
    void SetPostionStopLayer(Sprite*  sprite);

    static SEButton* create()
    {
        auto ret = new (std::nothrow) SEButton;
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
    EventListener* getListener()
    {
        return _listener;
    }
protected:
    SEButton()
    {
        if (se.GetIfon() == false)//如果SE没有播放，则设置为选下
        {
            _seButton = Sprite::create(s_P_SEButtonSelected);
        }
        else
        {
            _seButton = Sprite::create(s_P_SEButton);
        }
        _listener = nullptr;
    }
private:
    Sprite* _seButton;
    EventListener* _listener;
};




class InfoButton : public Sprite
{
public:
    virtual bool init();

    void SetPostionStartLayer();
    void SetPostionStopLayer(Sprite* sprite);

    static InfoButton* create()
    {
        auto ret = new (std::nothrow) InfoButton();
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
    InfoButton()
        : _infoButton(Sprite::create(s_P_InfoButton))
        , _listener(nullptr)
    {
    }
private:
    Sprite* _infoButton;
    EventListener* _listener;
};



class InfoScene : public cocos2d::Scene
{
public:

    virtual bool init();

    void TouchEvent(Ref* pSender, Widget::TouchEventType type);

    static InfoScene* create()
    {
        auto ret = new (std::nothrow)InfoScene();
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
    InfoScene()
        : _infoScene(Layer::create())
    {
    }
private:
    Layer* _infoScene;

};

#endif __TWOUSE_BUTTONS_LAYER_H__