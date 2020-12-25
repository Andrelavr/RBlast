#pragma once

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ButtonState.h"

class Button : public cocos2d::ui::Widget
{
public:
    Button();
    ~Button();

    virtual bool init() override;
    virtual bool init(const std::string& normalImage, const std::string& selectedImage);

    static Button* create();
    static Button* create(const std::string& normalImage, const std::string& selectedImage);

    virtual void addStateChild(cocos2d::Node* node, int zOrder, ButtonState state);

    ButtonState getState() const { return _state; }

    void setCallback(std::function<void()> callback);

    cocos2d::Size getSafeZone() const { return _safeZone; }
    void setSafetZone(const cocos2d::Size& safeZone);

    cocos2d::Size getExpandZone() const { return _expandZone; }
    void setExpandZone(const cocos2d::Size& expandZone);

    virtual void onSizeChanged() override;

    virtual bool hitTest(const cocos2d::Vec2& pt, const cocos2d::Camera* camera, cocos2d::Vec3* p) const override;

    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unusedEvent) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unusedEvent) override;

    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();

    const static std::string BUTTON_EVENT_NAME;

protected:
    virtual void updateState(ButtonState newState);
    virtual void appendStateChild(cocos2d::Node* node, ButtonState state);
    virtual void setChildStateVisible(ButtonState state, bool visible);
    virtual void sendPushEvent();
    virtual void callback();
    void updateZones(cocos2d::Size& updatingZone);

    std::function<void()> _callback;

    cocos2d::ui::Scale9Sprite* _textureNormal;
    cocos2d::ui::Scale9Sprite* _textureSelected;

    cocos2d::Size _safeZone;
    cocos2d::Size _expandZone;

    cocos2d::Vector<cocos2d::Node*> _childIdle;
    cocos2d::Vector<cocos2d::Node*> _childPushed;
    cocos2d::Vector<cocos2d::Node*> _childDragout;

    ButtonState _state;
};
