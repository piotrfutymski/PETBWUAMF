#include "Canvas.h"

namespace Didax
{
Canvas::Canvas():Widget()
{
}

bool Canvas::addChild(Widget * widget)
{
	return this->_addChild(widget);
}

void Canvas::removeChild(Widget * widget)
{
	this->_removeChild(widget);
}

sf::Color Canvas::getBackgroundColor() const
{
	return _backgroundColor;
}

void Canvas::setBackgroundColor(sf::Color c)
{
	_backgroundColor = c;
	if (_bType == BackgroundType::Rect)
		_backgroundRect->setFillColor(c*_color);
	else if (_bType == BackgroundType::Image)
		_backgroundSprite->setColor(c* _color);
}

void Canvas::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->setBackgroundColor(sf::Color{ r,g,b,a });
}

void Canvas::setTexture(const sf::Texture * t)
{
	if (_bType == BackgroundType::Rect)
		_backgroundRect = nullptr;
	_backgroundSprite = std::make_unique<sf::Sprite>();
	_backgroundSprite->setTexture(*t);
	_bType = BackgroundType::Image;
	this->updateSize();

}

void Canvas::setRect()
{
	if (_bType == BackgroundType::Image)
		_backgroundSprite = nullptr;
	_backgroundRect = std::make_unique<sf::RectangleShape>();
	_bType = BackgroundType::Rect;
	this->updateSize();

}

void Canvas::unsetBackground()
{
	if (_bType == BackgroundType::Image)
		_backgroundSprite = nullptr;
	else if(_bType == BackgroundType::Rect)
		_backgroundRect = nullptr;
	_bType = BackgroundType::None;
}

void Canvas::_update(float deltaT)
{
}

bool Canvas::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void Canvas::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (_bType == BackgroundType::Image)
		target.draw(*_backgroundSprite);
	else if (_bType == BackgroundType::Rect)
		target.draw(*_backgroundRect);
}

void Canvas::updatePosition()
{
	if (_bType == BackgroundType::Image)
		_backgroundSprite->setPosition(this->getAbsolutePosition());
	else if (_bType == BackgroundType::Rect)
		_backgroundRect->setPosition(this->getAbsolutePosition());
}

void Canvas::updateSize()
{
	if (_bType == BackgroundType::Image)
	{
		auto textureSize = _backgroundSprite->getTexture()->getSize();
		_backgroundSprite->setScale({ _size.x / textureSize.x, _size.y / textureSize.y });
	}
	else if (_bType == BackgroundType::Rect)
		_backgroundRect->setSize(_size);
}

void Canvas::updateColor()
{
	this->setBackgroundColor(_backgroundColor);
}

}