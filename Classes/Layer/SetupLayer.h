/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:…Ë÷√ƒ⁄»›
 ****************************************************************************/
#pragma once

#ifndef __SETUP_LAYER_H__
#define __SETUP_LAYER_H__

#include "cocos2d.h"
class SetupLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void StopCallBack(Ref* sendef);
    void StopCallBackBGM(Ref* sendef);
    void StopCallBackSE(Ref* sendef);
    CREATE_FUNC(SetupLayer);
};

#endif __SETUP_LAYER_H__