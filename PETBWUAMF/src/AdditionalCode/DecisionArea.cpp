#include "DecisionArea.h"

namespace Didax
{

DecisionArea::DecisionArea()
{
}

DecisionArea::~DecisionArea()
{
}

void DecisionArea::init(Canvas * holder, ImageWidget * background, ScrollArea * scrollArea,const std::vector<TextArea*> & options)
{
	_holder = holder;
	_background = background;
	_scrollArea = scrollArea;
	_options = options;

	_holder->addChild(_background);
	_holder->addChild(_scrollArea);
	for (auto x: _options)
	{
		_scrollArea->addChild(x);
	}
	_background->setActive(false);

	this->initWidgetFunctions();
	this->resetBackgrounds();
	this->recalculateAll();
}

void DecisionArea::setSize(const sf::Vector2f & s)
{
	_size = s;
	this->recalculateAll();
}

sf::Vector2f DecisionArea::getSize() const
{
	return _size;
}

void DecisionArea::setPosition(const sf::Vector2f & p)
{
	this->_holder->setPosition(p);
}

sf::Vector2f DecisionArea::getPosition() const
{
	return _holder->getPosition();
}

void DecisionArea::setScrollMargin(const sf::Vector2f & m)
{
	_scrollMargin = m;
	this->recalculateAll();
}

sf::Vector2f DecisionArea::getScrollMargin() const
{
	return _scrollMargin;
}

void DecisionArea::setScrollPadding(const sf::Vector2f & p)
{
	_scrollPadding = p;
	this->recalculateAll();
}

sf::Vector2f DecisionArea::getScrollPadding() const
{
	return _scrollPadding;
}

size_t DecisionArea::getHoveredOption() const
{
	return _hoveredOption;
}

void DecisionArea::setOnChoosenOption(const std::function<void(size_t opt)>& f)
{
	_onOptionChoosed = f;
}

void DecisionArea::initWidgetFunctions()
{
	for (size_t i = 0; i < _options.size(); i++)
	{
		_options[i]->setWidgetEvent(Widget::CallbackType::onHoverIn, [this, i](Widget * w, float dt) {
			_hoveredOption = i;
			_options[i]->setBackgroundColor({ 0,0,0,50 });
		});
		_options[i]->setWidgetEvent(Widget::CallbackType::onHoverOut, [this, i](Widget * w, float dt) {
			_hoveredOption = -1;
			_options[i]->setBackgroundColor({ 0,0,0,0 });
		});
		_options[i]->setWidgetEvent(Widget::CallbackType::onPress, [this, i](Widget * w, float dt) {
			_options[i]->setBackgroundColor({ 0,0,0,100 });
		});
		_options[i]->setWidgetEvent(Widget::CallbackType::onRelease, [this, i](Widget * w, float dt) {
			if (_onOptionChoosed != nullptr)
				_onOptionChoosed(i);
			if(_options[i]->isHovered())
				_options[i]->setBackgroundColor({ 0,0,0,50 });
			else
				_options[i]->setBackgroundColor({ 0,0,0,0 });
		});
	}
}

void DecisionArea::resetBackgrounds()
{
	_scrollArea->setBackgroundColor({ 0,0,0,0 });
	for (auto x : _options)
	{
		x->setBackgroundColor({ 0,0,0,0 });
	}
}

void DecisionArea::recalculatePositions()
{
	_background->setPosition(0, 0);
	_scrollArea->setPosition(_scrollMargin);
	_scrollArea->setPadding(_scrollPadding);

	float h = (_size.y - 2 * _scrollMargin.y - 6) / 3;

	for (size_t i = 0; i < _options.size(); i++)
	{
		_options[i]->setPosition(0, h*i);
	}

	_scrollArea->resizeHeightToChildren();
}

void DecisionArea::recalculateSizes()
{
	_background->setSize(_size);
	_scrollArea->setSize({ _size.x - _scrollMargin.x * 2, _size.y - _scrollMargin.y * 2 });

	float h = (_size.y - 2 * _scrollMargin.y) / 3;

	for (size_t i = 0; i < _options.size(); i++)
	{
		_options[i]->setSize({(_scrollArea->getSize().x) - 32, h});
	}
}

void DecisionArea::recalculateAll()
{
	this->recalculateSizes();
	this->recalculatePositions();
	_holder->resizeToChildren();
}

}


