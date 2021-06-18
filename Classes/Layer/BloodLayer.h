/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:ÑªÌõÄÚÈÝ

 API:
 ****************************************************************************/
#pragma once

#ifndef __BLOOD_LAYER_H__
#define __BLOOD_LAYER_H__

#include "cocos2d.h"
#include "source.h" 
#include "Const.h"
#include "ui/CocosGUI.h"
#include "Knight.h"


class BloodLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(BloodLayer);

private:
    Sprite* _DF;
    Sprite* _MP;
    Sprite* _HP;

};

#endif __BLOOD_LAYER_H__