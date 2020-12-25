#include "ButtonLongPress.h"

USING_NS_CC;

const std::string ButtonLongPress::BUTTON_LONG_PRESS_EVENT_NAME = "button_long_press_pushed";

ButtonLongPress::ButtonLongPress() :
    _pressDuration(1.0f),
    _deltaPress(0.0f)
{
    this->scheduleUpdate();
}

ButtonLongPress::~ButtonLongPress()
{}

bool ButtonLongPress::init()
{
    if (!Button::init())
    {
        return false;
    }

    return true;
}

bool ButtonLongPress::init(const std::string& normalImage, const std::string& selectedImage)
{
    return Button::init(normalImage, selectedImage);
}

ButtonLongPress* ButtonLongPress::create()
{
    ButtonLongPress* button = new (std::nothrow) ButtonLongPress();
    if (button && button->init())
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

ButtonLongPress* ButtonLongPress::create(const std::string& normalImage, const std::string& selectedImage)
{
    ButtonLongPress* button = new (std::nothrow) ButtonLongPress();
    if (button && button->init(normalImage, selectedImage))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

void ButtonLongPress::setPressDurattion(float duration)
{
    if (duration > 0.0f)
    {
        _pressDuration = duration;
    }
}

void ButtonLongPress::update(float delta)
{
    if (_state == ButtonState::Pushed)
    {
        _deltaPress += delta;
        if (_deltaPress >= _pressDuration)
        {
            updateState(ButtonState::PushedLong);
        }
    }
    else
    {
        _deltaPress = 0.0f;
    }
}

void ButtonLongPress::appendStateChild(cocos2d::Node* node, ButtonState state)
{
    if (state == ButtonState::Idle)
    {
        _childIdle.pushBack(node);
    }
    else if (state == ButtonState::Pushed)
    {
        _childPushed.pushBack(node);
    }
    else if (state == ButtonState::Dragout)
    {
        _childDragout.pushBack(node);
    }
    else if (state == ButtonState::PushedLong)
    {
        _childPushedLong.pushBack(node);
    }
    node->setVisible(_state == state);
    setChildStateVisible(_state, true);
}

void ButtonLongPress::sendPushEvent()
{
    if (_state == ButtonState::PushedLong)
    {
        auto dispatcher = Director::getInstance()->getEventDispatcher();

        EventCustom event(BUTTON_LONG_PRESS_EVENT_NAME);
        event.setUserData(this);
        dispatcher->dispatchEvent(&event);
    }
}

void ButtonLongPress::callback()
{
    if (_callback)
    {
        if (_state == ButtonState::PushedLong)
        {
            _callback();
        }
    }
}

void ButtonLongPress::setChildStateVisible(ButtonState state, bool visible)
{
    Button::setChildStateVisible(state, visible);

    if (state == ButtonState::PushedLong)
    {
        for (auto& node : _childPushedLong)
        {
            node->setVisible(visible);
        }
    }
}

