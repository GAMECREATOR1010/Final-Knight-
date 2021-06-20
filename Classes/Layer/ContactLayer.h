/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:½»»¥

 API:
 ****************************************************************************/
#pragma once


#ifndef __CONTACT_LAYER_H__
#define __CONTACT_LAYER_H__

#include "cocos2d.h"
#include "source.h" 
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Knight.h"


class LackOfCoinLayer : public cocos2d::Layer
{
public:
    void problemLoading(const char* filename);

    virtual bool init(Knight* kinght);

    static LackOfCoinLayer* create( Knight* kinght)
    {
        auto ret = new (std::nothrow) LackOfCoinLayer();
        if (ret && ret->init( kinght))
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


class SuccessBugLayer : public cocos2d::Layer
{
public:
    void problemLoading(const char* filename);

    virtual bool init(Knight* kinght);

    static SuccessBugLayer* create(Knight* kinght)
    {
        auto ret = new (std::nothrow) SuccessBugLayer();
        if (ret && ret->init(kinght))
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


class SuccessStatueLayer : public cocos2d::Layer
{
public:
    void problemLoading(const char* filename);

    virtual bool init(Knight* kinght);

    static SuccessStatueLayer* create(Knight* kinght)
    {
        auto ret = new (std::nothrow) SuccessStatueLayer();
        if (ret && ret->init(kinght))
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


class FailStatueLayer : public cocos2d::Layer
{
public:
    void problemLoading(const char* filename);

    virtual bool init(Knight* kinght);

    static FailStatueLayer* create(Knight* kinght)
    {
        auto ret = new (std::nothrow) FailStatueLayer();
        if (ret && ret->init(kinght))
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
#endif __CONTACT_LAYER_H__