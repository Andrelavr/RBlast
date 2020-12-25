#include "Button.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

const std::string Button::BUTTON_EVENT_NAME = "button_pushed";

Button::Button() :
    _callback(nullptr),
    _textureNormal(nullptr),
    _textureSelected(nullptr),
    _safeZone(Size::ZERO),
    _expandZone(Size::ZERO),
    _state(ButtonState::Idle)
{
    setTouchEnabled(true);
    setFocusEnabled(false);
}

Button::~Button()
{}

bool Button::init()
{
    if ( !ui::Widget::init() )
    {
        return false;
    }

    return true;
}

bool Button::init(const std::string& normalImage, const std::string& selectedImage)
{
    if (!normalImage.empty())
    {
        _textureNormal = ui::Scale9Sprite::create();
        _textureNormal->setRenderingType(ui::Scale9Sprite::RenderingType::SIMPLE);
        _textureNormal->initWithFile(normalImage);
        _textureNormal->setAnchorPoint(Vec2(0.0f, 0.0f));
        _textureNormal->setVisible(true);

        addProtectedChild(_textureNormal);
        setContentSize(_textureNormal->getContentSize());
    }
    if (!selectedImage.empty())
    {
        _textureSelected = ui::Scale9Sprite::create();
        _textureSelected->setRenderingType(ui::Scale9Sprite::RenderingType::SIMPLE);
        _textureSelected->initWithFile(selectedImage);
        _textureSelected->setAnchorPoint(Vec2(0.0f, 0.0f));
        _textureSelected->setVisible(false);

        addProtectedChild(_textureSelected);
    }

    return true;
}

Button* Button::create()
{
    Button* button = new (std::nothrow) Button();
    if (button && button->init())
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

Button* Button::create(const std::string& normalImage, const std::string& selectedImage)
{
    Button* button = new (std::nothrow) Button();
    if (button && button->init(normalImage, selectedImage))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

void Button::addStateChild(cocos2d::Node* node, int zOrder, ButtonState state)
{
    if (node)
    {
        if (node->getParent() == nullptr)
        {
            this->addChild(node, zOrder);
        }
        appendStateChild(node, state);
    }
}

void Button::setCallback(std::function<void()> callback)
{
    _callback = callback;
}

void Button::setSafetZone(const cocos2d::Size& safeZone)
{
    if (!_safeZone.equals(safeZone))
    {
        _safeZone = safeZone;

        updateZones(_safeZone);
    }
}

void Button::setExpandZone(const cocos2d::Size& expandZone)
{
    if (!_expandZone.equals(expandZone))
    {
        _expandZone = expandZone;

        updateZones(_expandZone);
    }
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();

    updateZones(_safeZone);
    updateZones(_expandZone);
}

bool Button::hitTest(const Vec2& pt, const Camera* camera, Vec3* p) const
{
    Rect rect;
    rect.origin = (_expandZone - getContentSize()) * -0.5f;
    rect.size = _expandZone;
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}

void Button::onTouchMoved(Touch* touch, Event* unusedEvent)
{
    if (_state == ButtonState::Idle)
    {
        return;
    }

    Widget::onTouchMoved(touch, unusedEvent);

    if (!_highlight)
    {
        updateState(ButtonState::Dragout);
        Rect rect;
        rect.origin = (_safeZone - getContentSize()) * -0.5f;
        rect.size = _safeZone;
        if (!isScreenPointInRect(_touchMovePosition, _hittedByCamera, getWorldToNodeTransform(), rect, nullptr))
        {
            onTouchEnded(touch, unusedEvent);
            updateState(ButtonState::Idle);
        }
    }
}

void Button::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    if (_state == ButtonState::Idle)
    {
        return;
    }

    Widget::onTouchEnded(touch, unusedEvent);

    sendPushEvent();

    callback();

    updateState(ButtonState::Idle);
}

void Button::onPressStateChangedToNormal()
{
    if (_textureNormal)
    {
        _textureNormal->setVisible(true);
    }
    if (_textureSelected)
    {
        _textureSelected->setVisible(false);
    }
}

void Button::onPressStateChangedToPressed()
{
    updateState(ButtonState::Pushed);
    if (_textureNormal)
    {
        _textureNormal->setVisible(false);
    }
    if (_textureSelected)
    {
        _textureSelected->setVisible(true);
    }
}

void Button::updateState(ButtonState newState)
{
    if (_state != newState)
    {
        setChildStateVisible(_state, false);
        
        _state = newState;

        setChildStateVisible(_state, true);
    }
}

void Button::appendStateChild(cocos2d::Node* node, ButtonState state)
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
    node->setVisible(_state == state);
    setChildStateVisible(_state, true);
}

void Button::setChildStateVisible(ButtonState state, bool visible)
{
    if (state == ButtonState::Idle)
    {
        for (auto& node : _childIdle)
        {
            node->setVisible(visible);
        }
    }
    else if (state == ButtonState::Pushed)
    {
        for (auto& node : _childPushed)
        {
            node->setVisible(visible);
        }
    }
    else if (state == ButtonState::Dragout)
    {
        for (auto& node : _childDragout)
        {
            node->setVisible(visible);
        }
    }
}

void Button::sendPushEvent()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    EventCustom event(BUTTON_EVENT_NAME);
    event.setUserData(this);
    dispatcher->dispatchEvent(&event);
}

void Button::callback()
{
    if (_callback)
    {
        _callback();
    }
}

void Button::updateZones(cocos2d::Size& updatingZone)
{
    updatingZone.width = std::max(_contentSize.width, updatingZone.width);
    updatingZone.height = std::max(_contentSize.height, updatingZone.height);
}
