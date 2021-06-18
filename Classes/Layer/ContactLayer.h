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
#include "Knight.h"
#include "source.h" 


class LackOfCoinLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(LackOfCoinLayer);

};


class SuccessBugLayer : public cocos2d::Layer
{
public:

    virtual bool init();

    CREATE_FUNC(SuccessBugLayer);

};

#endif __CONTACT_LAYER_H__