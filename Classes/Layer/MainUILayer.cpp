/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-18)

 Annotation:主要UI整合

 ****************************************************************************/


#include "MainUILayer.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainUILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}


void MainUILayer::AddStuff(EventListenerKeyboard& eventListener, Node& node, Knight& kinght)
{
    bgm._audioID = bgm.play2d(s_M_StartBGM);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();


    {
        auto stopButton = StopButton::create(eventListener, node);
        stopButton->setGlobalZOrder(uiOrder);
        this->addChild(stopButton);
    }
    {
        _bloodLayer->SetKnight(kinght);
        _bloodLayer->setGlobalZOrder(uiOrder);
        this->addChild(_bloodLayer);
    }
    {
        auto coinFrame = Sprite::create(s_P_CoinFrame);
        float x = visibleSize.width - coinFrame->getContentSize().width * 2 + originSize.x;
        float y = visibleSize.height - coinFrame->getContentSize().height + originSize.y;
        coinFrame->setPosition(x, y);
        coinFrame->setGlobalZOrder(uiOrder);
        this->addChild(coinFrame);

        if (coinLabel.GetLabel() == nullptr)
        {
            coinLabel.AddStuff(coinFrame);
        }
        coinLabel.Change();
        this->addChild(coinLabel.GetLabel());
    }
}


void CoinLabel::AddStuff(Sprite* coinFrame)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    _x = visibleSize.width - coinFrame->getContentSize().width * 15 / 8 + originSize.x;
    _y = visibleSize.height - coinFrame->getContentSize().height + originSize.y;
    char string[30] = { 0 };
    sprintf(string, "%d", goldMoney.GetBalance());
    _label = Label::createWithTTF(string, s_T_Pixeboy, 25);
    _label->setPosition(_x, _y);
    _label->setGlobalZOrder(uiOrder);
}
void CoinLabel::Change()
{
    char string[30] = { 0 };
    sprintf(string, "%d", goldMoney.GetBalance());
    _label->setString(string);
}

void MainUILayer :: ChangeCoinLabel()
{
    coinLabel.Change();
}