#pragma once
#ifndef __GAMING_SCENE_H__
#define __GAMING_SCENE_H__

#include "General.h"
#include <cstdlib> 
#include <ctime>

class Gaming : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(Knight* myknight,int chapter);
    BattleMap* map;
    Knight* myKnight;
    bool flag, inPassage, transing = false;
    bool endGame = false;
    virtual bool init(Knight* myknight, int chapter);
    void myUpdate(float tmd);
    bool onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    bool onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    bool onContactBegin(const PhysicsContact& contact);
    void update(float delta);
    int chapter = 1;
    Vec2 change;
    Room* atRoom;
    Room* nextRoom;
    
private:
    bool _isInteract = false;
};


#endif 