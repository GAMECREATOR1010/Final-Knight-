/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-24)

 Annotation:��ͣ����
 ****************************************************************************/

#pragma once

#ifndef __STOP_LAYER_H__
#define __STOP_LAYER_H__

#include "cocos2d.h"

class StopLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void StopCallBack(Ref* sendef);
    CREATE_FUNC(StopLayer);
};

#endif __STOP_LAYER_H__

