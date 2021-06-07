/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-27)

 Annotation:…Ë÷√ƒ⁄»›
 ****************************************************************************/
#pragma once

#ifndef __SETUP_LAYER_H__
#define __SETUP_LAYER_H__

#include "cocos2d.h"
#include "source.h" 

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
    void StopCallBackBGM(Ref* sendef);
    void StopCallBackSE(Ref* sendef);
    CREATE_FUNC(BGMLayer);
};

#endif __SETUP_LAYER_H__