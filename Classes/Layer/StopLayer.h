/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-24)

 Annotation:ÔÝÍ£ÄÚÈÝ
 ****************************************************************************/

#pragma once

#ifndef _STOP_LAYER_H_
#define _STOP_LAYER_H_

#include "cocos2d.h"

class StopLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void StopCallBack(Ref* sendef);
    CREATE_FUNC(StopLayer);
};

#endif _STOP_LAYER_H_

