#pragma once
#ifndef __GAMING_SCENE_H__
#define __GAMING_SCENE_H__

#include "General.h"

class Gaming : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(Gaming);
};

#endif 