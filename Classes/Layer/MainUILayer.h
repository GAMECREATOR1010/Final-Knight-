/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/
#pragma once


#include "cocos2d.h"
#include "source.h" 
#include "General.h"
#include "ui/CocosGUI.h"
#include "BloodLayer.h"
#include "StopLayer.h"

class MainUILayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(MainUILayer);
};