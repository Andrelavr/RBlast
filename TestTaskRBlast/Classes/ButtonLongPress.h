#pragma once

#include "cocos2d.h"
#include "Button.h"

class ButtonLongPress : public Button
{
public:
    ButtonLongPress();
    ~ButtonLongPress();

    virtual bool init() override;
    virtual bool init(const std::string& normalImage, const std::string& selectedImage);

    static ButtonLongPress* create();
    static ButtonLongPress* create(const std::string& normalImage, const std::string& selectedImage);

    void setPressDurattion(float duration);
    float getPressDuration() const { return _pressDuration; }

    virtual void update(float delta) override;

    const static std::string BUTTON_LONG_PRESS_EVENT_NAME;

protected:
    virtual void appendStateChild(cocos2d::Node* node, ButtonState state) override;
    virtual void sendPushEvent() override;
    virtual void callback() override;
    virtual void setChildStateVisible(ButtonState state, bool visible) override;

    cocos2d::Vector<cocos2d::Node*> _childPushedLong;

private:

    float _pressDuration;
    float _deltaPress;
};
