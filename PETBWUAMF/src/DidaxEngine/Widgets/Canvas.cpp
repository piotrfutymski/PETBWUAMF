#include "Canvas.h"

namespace Didax
{
Canvas::Canvas():Widget(), _backgroundColor { sf::Color{0, 0, 0} }
{
	_background.setFillColor(_backgroundColor);
	_background.setSize(_size);
}

void Canvas::addChild(Widget * widget)
{
	this->_addChild(widget);
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
	_background.setFillColor(c*_color);
}

void Canvas::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	_backgroundColor = sf::Color{ r,g,b,a };
	_background.setFillColor(_backgroundColor*_color);
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
	target.draw(_background);
}

void Canvas::updatePosition()
{
	_background.setPosition(this->getAbsolutePosition());
}

void Canvas::updateSize()
{
	_background.setSize(_size);
}

void Canvas::updateColor()
{
	this->setBackgroundColor(_backgroundColor);
}

}