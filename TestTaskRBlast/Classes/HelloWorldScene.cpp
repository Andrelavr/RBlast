/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIText.h"
#include "Button.h"
#include "ButtonLongPress.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto button1 = Button::create("button_normal.png", "button_selected.png");
    if (button1)
    {
        button1->setPosition(Vec2(visibleSize.width * 0.2f + origin.x, visibleSize.height * 0.8f + origin.y));
        this->addChild(button1, 10);
        button1->setScale(0.3f);
        button1->setExpandZone(button1->getContentSize() * 1.2f);
        button1->setSafetZone(Size(button1->getContentSize().width * 1.5f, button1->getContentSize().height * 2.0f));
        button1->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto label = Label::createWithTTF("Button 1", "fonts/Marker Felt.ttf", 70);
        label->setPosition(button1->getContentSize() * 0.5f);
        button1->addChild(label);

        debugSprite(button1, button1->getSafeZone(), Color3B::GREEN, 1);
        debugSprite(button1, button1->getExpandZone(), Color3B::BLUE, 2);
    }

    auto button2 = Button::create("button_normal.png", "button_selected.png");
    if (button2)
    {
        button2->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.8f + origin.y));
        this->addChild(button2, 10);
        button2->setScale(0.3f);
        button2->setExpandZone(Size(button2->getContentSize().width, button2->getContentSize().height * 1.6f));
        button2->setSafetZone(Size(button2->getContentSize().width * 1.5f, button2->getContentSize().height * 2.0f));
        button2->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto label = Label::createWithTTF("Button 2 Idle", "fonts/Marker Felt.ttf", 70);
        label->setPosition(button2->getContentSize() * 0.5f);
        button2->addStateChild(label, 1, ButtonState::Idle);

        debugSprite(button2, button2->getSafeZone(), Color3B::GREEN, 1);
        debugSprite(button2, button2->getExpandZone(), Color3B::BLUE, 2);
    }

    auto button3 = Button::create("button_normal.png", "button_selected.png");
    if (button3)
    {
        button3->setPosition(Vec2(visibleSize.width * 0.8f + origin.x, visibleSize.height * 0.8f + origin.y));
        button3->setRotation(45.0f);
        this->addChild(button3, 10);
        button3->setScale(0.3f);
        button3->setExpandZone(button3->getContentSize() * 1.2f);
        button3->setSafetZone(Size(button3->getContentSize().width * 1.5f, button3->getContentSize().height * 2.0f));
        button3->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto label = Label::createWithTTF("Button 3 Idle + Pushed", "fonts/Marker Felt.ttf", 70);
        label->setPosition(button3->getContentSize() * 0.5f);
        button3->addStateChild(label, 1, ButtonState::Idle);
        button3->addStateChild(label, 1, ButtonState::Pushed);

        debugSprite(button3, button3->getSafeZone(), Color3B::GREEN, 1);
        debugSprite(button3, button3->getExpandZone(), Color3B::BLUE, 2);
    }

    auto button4 = ButtonLongPress::create("button_normal.png", "button_selected.png");
    if (button4)
    {
        button4->setPosition(Vec2(visibleSize.width * 0.2f + origin.x, visibleSize.height * 0.6f + origin.y));
        this->addChild(button4, 10);
        button4->setScale(0.3f);
        button4->setExpandZone(button4->getContentSize() * 1.2f);
        button4->setSafetZone(Size(button4->getContentSize().width * 1.5f, button4->getContentSize().height * 2.0f));
        button4->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto label = Label::createWithTTF("Button 4 Idle + Pushed", "fonts/Marker Felt.ttf", 70);
        label->setPosition(button4->getContentSize() * 0.5f);
        button4->addStateChild(label, 1, ButtonState::Idle);
        button4->addStateChild(label, 1, ButtonState::Pushed);

        auto labelLongPushed = Label::createWithTTF("Long Pushed", "fonts/Marker Felt.ttf", 85);
        labelLongPushed->setPosition(button4->getContentSize() * 0.5f);
        button4->addStateChild(labelLongPushed, 1, ButtonState::PushedLong);

        debugSprite(button4, button4->getSafeZone(), Color3B::GREEN, 1);
        debugSprite(button4, button4->getExpandZone(), Color3B::BLUE, 2);
    }

    auto labelExpand = Label::createWithTTF("Expand zone", "fonts/Marker Felt.ttf", 25);
    labelExpand->setPosition(Vec2(visibleSize.width * 0.4f + origin.x, visibleSize.height * 0.20f + origin.y));
    this->addChild(labelExpand);

    auto spriteExpand = Sprite::create();
    spriteExpand->setTextureRect(Rect(0.0f, 0.0f, 25.0f, 25.0f));
    spriteExpand->setPosition(Vec2(visibleSize.width * 0.6f + origin.x, visibleSize.height * 0.20f + origin.y));
    spriteExpand->setColor(Color3B::BLUE);
    this->addChild(spriteExpand);

    auto labelSafe = Label::createWithTTF("Safe zone", "fonts/Marker Felt.ttf", 25);
    labelSafe->setPosition(Vec2(visibleSize.width * 0.4f + origin.x, visibleSize.height * 0.15f + origin.y));
    this->addChild(labelSafe);
    
    auto spriteSafe = Sprite::create();
    spriteSafe->setTextureRect(Rect(0.0f, 0.0f, 25.0f, 25.0f));
    spriteSafe->setPosition(Vec2(visibleSize.width * 0.6f + origin.x, visibleSize.height * 0.15f + origin.y));
    spriteSafe->setColor(Color3B::GREEN);
    this->addChild(spriteSafe);

    return true;
}

Sprite* HelloWorld::debugSprite(cocos2d::Node* transformNode, cocos2d::Size size, cocos2d::Color3B color, int zOrder)
{
    auto sprite = Sprite::create();
    sprite->setTextureRect(Rect(0.0f, 0.0f, size.width, size.height));
    sprite->setColor(color);
    sprite->setOpacity(100);
    sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(sprite, zOrder);
    Vec3 scale;
    Quaternion rotation;
    transformNode->getNodeToParentTransform().decompose(&scale, &rotation, nullptr);
    sprite->setScale(scale.x, scale.y);
    sprite->setRotationQuat(rotation);
    sprite->setPosition(transformNode->getPosition());
    return sprite;
}
