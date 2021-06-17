/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-6-17)

 Annotation:���ڿ�ʼ�������ͣ������ʾ�İ�ť��
            BGMButton �� SEButton  ��InfoButton
            �� InfoScene ������
 ****************************************************************************/

#include "TwoUseButtonsLayer.h"


USING_NS_CC;
using namespace cocos2d::ui;


void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BGMButton::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    float scaledPre = visibleSize.width * ButtonPre / (_bgmButton->getContentSize().width);
    _bgmButton->setContentSize(Size(_bgmButton->getContentSize().width * scaledPre, _bgmButton->getContentSize().height * scaledPre));

    auto listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(true);
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            se._audioID = se.play2d(s_M_ButtonSelected);
            if (bgm.getIfon() == false)//���BGMû�в��ţ������BGM
            {
                bgm.resumeAll();
                bgm.change();
            }
            else//���BGM���ڲ��ţ�����ͣBGM
            {
                bgm.pauseAll();
                bgm.change();
            }
            return true;
        }
        return false;
    };

    listener->onTouchMoved = [](Touch* touch, Event* event) {
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        if (bgm.getIfon() == false)//���BGMû�в��ţ������ð�ťΪ����
        {
            _bgmButton->setTexture(s_P_BGMButtonSelected);
            float scaledPre = visibleSize.width * ButtonPre / (_bgmButton->getContentSize().width);
            _bgmButton->setScale(scaledPre);
        }
        else//���BGM���ڲ��ţ������ð�ťΪ����
        {
            _bgmButton->setTexture(s_P_BGMButton);
            float scaledPre = visibleSize.width * ButtonPre / (_bgmButton->getContentSize().width);
            _bgmButton->setScale(scaledPre);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _bgmButton);

    _listener = listener;

    return true;
}


void BGMButton::setPostionStartLayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float x = originSize.x + _bgmButton->getContentSize().width / 2+ ButtonWidthGap;
    float y = originSize.y + _bgmButton->getContentSize().height  / 2+ ButtonHeightGap;
    _bgmButton->setPosition(Vec2(x, y));
    addChild(_bgmButton);
}

void BGMButton::setPostionStopLayer(Sprite* sprite)
{
    _bgmButton->setAnchorPoint(Vec2(0.5, 0));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float x = originSize.x + visibleSize.width / 2 - _bgmButton->getContentSize().width - ButtonWidthGapInStop;
    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;
    _bgmButton->setPosition(Vec2(x, y));
    addChild(_bgmButton);
}






bool SEButton::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    float scaledPre = visibleSize.width * ButtonPre / (_seButton->getContentSize().width);
    _seButton->setContentSize(Size(_seButton->getContentSize().width* scaledPre, _seButton->getContentSize().height* scaledPre));


    auto listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(true);
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            if (se.getIfon() == false)//���SEû�в��ţ���ı�״̬
            {
                se.change();
            }
            else//���SE���ڲ��ţ���ر�SE���ı�״̬
            {
                se.change();
            }
            return true;
        }
        return false;
    };

    listener->onTouchMoved = [](Touch* touch, Event* event) {
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        auto visibleSize = Director::getInstance()->getVisibleSize();

        if (se.getIfon() == false)//���SEû�в��ţ������ð�ťΪ����
        {
            _seButton->setTexture(s_P_SEButtonSelected);
            float scaledPre = visibleSize.width * ButtonPre / (_seButton->getContentSize().width);
            _seButton->setScale(scaledPre);
        }
        else//���SE���ڲ��ţ������ð�ťΪ����������SE
        {
            _seButton->setTexture(s_P_SEButton);
            float scaledPre = visibleSize.width * ButtonPre / (_seButton->getContentSize().width);
            _seButton->setScale(scaledPre);
            se._audioID = se.play2d(s_M_ButtonSelected);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _seButton);

    _listener = listener;

    return true;
}


void SEButton::setPostionStartLayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float x = originSize.x + _seButton->getContentSize().width  / 2 + ButtonWidthGap;
    float y = originSize.y + _seButton->getContentSize().height  * 3 / 2 + ButtonHeightGap * 2;
    _seButton->setPosition(Vec2(x, y));
    addChild(_seButton);
}

void SEButton::setPostionStopLayer(Sprite* sprite)
{
    _seButton->setAnchorPoint(Vec2(0.5, 0));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float x = originSize.x + visibleSize.width / 2 - _seButton->getContentSize().width * 2 - ButtonWidthGapInStop * 2;
    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;
    _seButton->setPosition(Vec2(x, y));
    addChild(_seButton);
}





bool InfoButton::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    float scaledPre = visibleSize.width * ButtonPre / (_infoButton->getContentSize().width);
    _infoButton->setContentSize(Size(_infoButton->getContentSize().width * scaledPre, _infoButton->getContentSize().height * scaledPre));


    auto listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(true);
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&,this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            se._audioID = se.play2d(s_M_ButtonSelected);
            Director::getInstance()->pushScene(InfoScene::create());

            return true;
        }
        return false;
    };

    listener->onTouchMoved = [](Touch* touch, Event* event) {
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _infoButton);

    _listener = listener;

    return true;
}


void InfoButton::setPostionStartLayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float scaledPre = visibleSize.width * ButtonPre / (_infoButton->getContentSize().width);
    _infoButton->setScale(scaledPre);
    float x = originSize.x + _infoButton->getContentSize().width * scaledPre / 2 + ButtonWidthGap;
    float y = originSize.y + _infoButton->getContentSize().height * scaledPre * 5 / 2 + ButtonHeightGap * 3;
    _infoButton->setPosition(Vec2(x, y));
    addChild(_infoButton);
}

void InfoButton::setPostionStopLayer(Sprite* sprite)
{
    _infoButton->setAnchorPoint(Vec2(0.5, 0));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    float scaledPre = visibleSize.width * ButtonPre / (_infoButton->getContentSize().width);
    _infoButton->setScale(scaledPre);
    float x = originSize.x + visibleSize.width / 2 + _infoButton->getContentSize().width * scaledPre * 2 + ButtonWidthGapInStop * 2;
    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;
    _infoButton->setPosition(Vec2(x, y));
    addChild(_infoButton, stopLayerStuffTag);
}






bool InfoScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();

    //��ʾ���
    auto sprite = Sprite::create(s_P_InfoFrame);
    sprite->setPosition(Vec2(visibleSize / 2) + originSize);
    _infoScene->addChild(sprite);// , infoLayerTag);

    float y = originSize.y + visibleSize.height / 2 - sprite->getContentSize().height / 2 + ButtonHeightGapInStop;

    {
        //��ʾ�رհ�ť
        Button* closeButton = Button::create(s_P_CloseButton);
        closeButton->setAnchorPoint(Vec2(0.5, 0));

        closeButton->ignoreContentAdaptWithSize(false);
        closeButton->setScale9Enabled(true);
        closeButton->setPressedActionEnabled(false);
        closeButton->addTouchEventListener(CC_CALLBACK_2(InfoScene::touchEvent, this));

        float x = originSize.x + visibleSize.width / 2;
        closeButton->setPosition(Vec2(x, y));
        _infoScene->addChild(closeButton);// , infoLayerStuffTag);
    }

    this->addChild(_infoScene);
    return true;
}

void InfoScene::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        se._audioID = se.play2d(s_M_ButtonSelected);
        Director::getInstance()->popScene();
    }
    break;

    default:
        break;

    }
    return;
}