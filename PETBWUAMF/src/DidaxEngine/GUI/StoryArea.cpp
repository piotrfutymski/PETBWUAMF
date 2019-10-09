#include "StoryArea.h"

namespace Didax
{


StoryArea::StoryArea()
{
}


StoryArea::~StoryArea()
{
}

void StoryArea::init(Canvas * h, ImageWidget * b, ScrollArea * s, TextArea * t, ImageWidget * i)
{
	_holder = h;
	_background = b;
	_scrollArea = s;
	_text = t;
	_image = i;
	h->addChild(b);
	h->addChild(s);
	s->addChild(t);
	s->addChild(i);
	b->setActive(false);
	t->setActive(false);
	i->setActive(false);
	this->resetBackgrounds();
	this->recalculateAll();
}

void StoryArea::setSize(const sf::Vector2f & s)
{
	_size = s;
	this->recalculateAll();
}

sf::Vector2f StoryArea::getSize() const
{
	return _size;
}

void StoryArea::setPosition(const sf::Vector2f & p)
{
	this->_holder->setPosition(p);
}

sf::Vector2f StoryArea::getPosition() const
{
	return _holder->getPosition();
}

void StoryArea::setScrollMargin(const sf::Vector2f & m)
{
	_scrollMargin = m;
	this->recalculateAll();
}

sf::Vector2f StoryArea::getScrollMargin() const
{
	return _scrollMargin;
}

void StoryArea::setScrollPadding(const sf::Vector2f & p)
{
	_scrollPadding = p;
	this->recalculateAll();
}

sf::Vector2f StoryArea::getScrollPadding() const
{
	return _scrollPadding;
}

void StoryArea::resetBackgrounds()
{
	_scrollArea->setBackgroundColor({ 0,0,0,0 });
	_text->setBackgroundColor({ 0,0,0,0 });
}

void StoryArea::recalculatePositions()
{
	_background->setPosition(0, 0);
	_scrollArea->setPosition(_scrollMargin);
	_scrollArea->setPadding(_scrollPadding);
	if (_imageFirst)
	{
		_image->setPosition(0, 0);
		_text->setPosition(0, _image->getSize().y);
	}
	else
	{
		_text->setPosition(0, 0);
		_image->setPosition(0, _text->getSize().y);
	}
	_scrollArea->resizeHeightToChildren();
	
}

void StoryArea::recalculateSizes()
{
	_background->setSize(_size);
	_scrollArea->setSize({ _size.x - _scrollMargin.x * 2, _size.y - _scrollMargin.y * 2 });
	_text->resizeToText();
}

void StoryArea::recalculateAll()
{
	this->recalculateSizes();
	this->recalculatePositions();
	_holder->resizeToChildren();
}


}