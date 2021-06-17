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

#include "cocos2d.h"
#include "BGM.h"
#include "ui/CocosGUI.h"
#include "Const.h"
#include "source.h" 

using namespace cocos2d::ui;

void problemLoading(const char* filename);

class BGMButton : public Sprite
{
public:
    virtual bool init();

    void setPostionStartLayer();
    void setPostionStopLayer(Sprite*  sprite);

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

        if (bgm.getIfon() == false)//如果BGM没有播放，则设置为选下
        {
            _bgmButton = Sprite::create(s_P_BGMButtonSelected);
        }
        else
        {
            _bgmButton = Sprite::create(s_P_BGMButton);
        }
        _listener = nullptr;
        if (_bgmButton == nullptr ||
            _bgmButton->getContentSize().width <= 0 ||
            _bgmButton->getContentSize().height <= 0)
        {
            problemLoading("'s_P_BGMButton' and 's_P_BGMButtonSelected'");
        }
    }
private:
    Sprite* _bgmButton;
    EventListener* _listener;
};


class SEButton : public cocos2d::Sprite
{
public:
    virtual bool init();

    void setPostionStartLayer();
    void setPostionStopLayer(Sprite*  sprite);

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
        if (se.getIfon() == false)//如果SE没有播放，则设置为选下
        {
            _seButton = Sprite::create(s_P_SEButtonSelected);
        }
        else
        {
            _seButton = Sprite::create(s_P_SEButton);
        }
        _listener = nullptr;

        if (_seButton == nullptr ||
            _seButton->getContentSize().width <= 0 ||
            _seButton->getContentSize().height <= 0)
        {
            problemLoading("'s_P_SEButton' and 's_P_SEButtonSelected'");
        }
    }
private:
    Sprite* _seButton;
    EventListener* _listener;
};




class InfoButton : public Sprite
{
public:
    virtual bool init();

    void setPostionStartLayer();
    void setPostionStopLayer(Sprite* sprite);

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
        if (_infoButton == nullptr ||
            _infoButton->getContentSize().width <= 0 ||
            _infoButton->getContentSize().height <= 0)
        {
            problemLoading("'s_P_InfoButton' and 's_P_InfoButtonSelected'");
        }
    }
private:
    Sprite* _infoButton;
    EventListener* _listener;
};



class InfoScene : public cocos2d::Scene
{
public:

    virtual bool init();

    void touchEvent(Ref* pSender, Widget::TouchEventType type);

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