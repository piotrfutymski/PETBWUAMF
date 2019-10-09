#include "ScrollArea.h"


namespace Didax
{

ScrollArea::ScrollArea()
{	
}

ScrollArea::ScrollArea(const Scroller & scr)
{
	this->setScroller(scr);
}

void ScrollArea::addChild(Widget * widget)
{
	this->_addChild(widget);
}

void ScrollArea::removeChild(Widget * widget)
{
	this->_removeChild(widget);
}

void ScrollArea::setScroller(const Scroller & scr)
{
	_scroller = scr;
	_scroller.setOnButtonPosChanged([this]()
	{
		this->calcualteChildrenPos();
	});
}

sf::Color ScrollArea::getBackgroundColor() const
{
	return _backgroundColor;
}

void ScrollArea::setBackgroundColor(sf::Color c)
{
	_backgroundColor = c;
	_background.setFillColor(c*_color);
}

void ScrollArea::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this -> setBackgroundColor(sf::Color{ r,g,b,a });
}

float ScrollArea::getScrollerWidth() const
{
	return _scrollerWidth;
}

void ScrollArea::setScrollerWidth(float x)
{
	_scrollerWidth = x;
	this->calculateScroller();
}

float ScrollArea::getAreaHeight() const
{
	return _areaHeight;
}

void ScrollArea::setAreaHeight(float y)
{
	_areaHeight = y;
	if (_areaHeight <= _size.y)
	{
		_areaHeight = _size.y;
		_showScroller = false;
	}
	else
	{
		this->calculateScroller();
		_showScroller = true;
	}
}

void ScrollArea::resizeHeightToChildren()
{
	auto h = this->getSizeWithChildren().y + _padding.y;
	this->setAreaHeight(h);
}


float ScrollArea::getWheelVelocity() const
{
	return _wheelVelocity;
}

void ScrollArea::setWheelVelocity(float v)
{
	_wheelVelocity = v;
}

void ScrollArea::_update(float deltaT)
{
	if(_showScroller)
		_scroller.update(deltaT);
}

bool ScrollArea::_input(const sf::Event & event, bool inArea)
{
	if (_showScroller)
	{
		if (event.type == sf::Event::MouseWheelMoved && this->isMoseIn() && inArea)
		{
			_scroller.moveButton(-event.mouseWheel.delta * _wheelVelocity);
		}
	}	
	return false;
}

bool ScrollArea::_inputBeforeAll(const sf::Event & event, bool inArea)
{
	if (_showScroller)
		return _scroller.input(event);
}

void ScrollArea::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_background);
}

void ScrollArea::_drawAfterAll(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(_showScroller)
		target.draw(_scroller);
}

void ScrollArea::updatePosition()
{
	_background.setPosition(this->getAbsolutePosition());
	this->setLimitArea({ 0,0 }, _size);
	this->calculateScroller();
}

void ScrollArea::updateSize()
{
	_background.setSize(_size);
	this->setLimitArea({ 0,0 }, _size);
	this->calculateScroller();
}

void ScrollArea::calcualteChildrenPos()
{
	auto temp = -_scroller.getButtonPosition()*(_areaHeight - _size.y);
	auto delta = temp - _deltaH;
	for (auto x : _children)
	{
		x->move({ 0, delta });
	}
	_deltaH = temp;
}

void ScrollArea::calculateScroller()
{
	auto temp = this->getAbsolutePosition();
	_scroller.setPosition({ temp.x +_size.x- _scrollerWidth, temp.y });
	_scroller.setSize({ _scrollerWidth, _size.y });
}

void ScrollArea::updateColor()
{
	_scroller.setColor(_color);
	this->setBackgroundColor(_backgroundColor);
}


}