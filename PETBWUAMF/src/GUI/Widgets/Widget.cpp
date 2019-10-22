#include "Widget.h"

namespace Didax{

//constructors

Widget::Widget()
{
	_widgetEvent[CallbackType::onHold] = nullptr;
	_widgetEvent[CallbackType::onHover] = nullptr;
	_widgetEvent[CallbackType::onHoverIn] = nullptr;
	_widgetEvent[CallbackType::onHoverOut] = nullptr;
	_widgetEvent[CallbackType::onPress] = nullptr;
	_widgetEvent[CallbackType::onRelease] = nullptr;
	_widgetEvent[CallbackType::onPressRight] = nullptr;

}

//public functions

void Widget::update(float deltaT)
{
	if (!_isActive)
		return;
	
	this->actualizeInTime(deltaT);
	this->updateEvents();
	this->updateCallbacks(deltaT);
	if (_onUpdate != nullptr)
		_onUpdate(this, deltaT);
	this->_update(deltaT);
	for (auto x : _children)
	{
		x->update(deltaT);
	}
}

bool Widget::input(const sf::Event & event, bool inArea)
{
	if (!_isActive)
		return false;

	auto a = this->getAbsolutePosition();
	if (_isSetArea && !this->isPointInArea((sf::Vector2f)(Input::getMousePosition()), _borderArea[0] +a, _borderArea[1] - _borderArea[0] + a))
		inArea = false;

	bool endHere = this->_inputBeforeAll(event, inArea);
	if (endHere)
		return endHere;
		
	int i = _children.size() - 1;
	while (i != -1)
	{
		if (_children[i]->getPriority() < _priority)
			break;
		endHere |= _children[i]->input(event, inArea);
		if (endHere)
			return endHere;
		i--;
	}

	if (inArea)
	{
		endHere = this->poolEvents(event);
	}	
	endHere |= this->_input(event, inArea);
	if (endHere)
		return endHere;

	while (i !=  - 1)
	{
		endHere |= _children[i]->input(event, inArea);
		if (endHere)
			return endHere;
		i--;
	}
	return endHere;
}

bool Widget::isInGivenArea(sf::Vector2f a, sf::Vector2f b)
{
	if (_relativePos.x > a.x && _relativePos.x + getSize().x< b.x && _relativePos.y > a.y && _relativePos.y + getSize().y < b.y)
		return true;
	return false;
}

//properties

void Widget::setPosition(sf::Vector2f pos)
{
	auto delta = pos - _relativePos;
	_relativePos = pos;
	this->updatePosition();
	for (auto x : _children)
	{
		x->updatePosition();
	}
	if (_isSetArea)
	{
		this->setLimitArea(_borderArea[0] + delta, _borderArea[1] + delta);
	}
}

void Widget::setPosition(float x, float y)
{
	this->setPosition({ x,y });
}

void Widget::move(sf::Vector2f deltaS)
{
	this->setPosition(deltaS.x + _relativePos.x, deltaS.y + _relativePos.y);
}

sf::Vector2f Widget::getPosition() const
{
	return _relativePos;
}

void Widget::setPositionInTime(sf::Vector2f pos, float T)
{
	_movingInTime = true;
	_nextPos = pos;
	_velocity = { (pos.x - _relativePos.x) / T, (pos.y - _relativePos.y) / T };
	_timeToMove = T;
}

void Widget::setPositionInTime(float x, float y, float T)
{
	setPositionInTime({ x,y }, T);
}

void Widget::setColor(const sf::Color & c)
{
	_color = c;
	this->updateColor();
	for (auto x : _children)
	{
		x->setColor(c);
	}
}

void Widget::setColorInTime(const sf::Color & c, float T)
{
	_changingColor = true;
	_nextColor = { c.r, c.g,c.b,c.a };
	_lastColor = _color;
	_timefromBeg = 0;
	_timeToChangeColor = T;
}

sf::Color Widget::getColor() const
{
	return _color;
}

void Widget::setSize(const sf::Vector2f & s)
{
	_size = s;
	this->updateSize();
}

void Widget::resizeToChildren()
{
	this->setSize(this->getSizeWithChildren());
}

sf::Vector2f Widget::getSizeWithChildren()const
{
	sf::Vector2f res{ 0,0 };
	if (_children.size() == 0)
		res;
	for (auto x : _children)
	{
		auto p = x->getPosition();
		auto s = x->getSize();
		if (p.x + s.x > res.x)
			res.x = p.x + s.x;
		if (p.y + s.y > res.y)
			res.y = p.y + s.y;
	}
	return res;
}

sf::Vector2f Widget::getSize() const
{
	return _size;
}

Widget * Widget::getParent()
{
	return _parent;
}

const Widget * Widget::getParent() const
{
	return _parent;
}

void Widget::setPadding(const sf::Vector2f & pad)
{
	_padding = pad;
	this->updatePosition();
}

sf::Vector2f Widget::getPadding() const
{
	return _padding;
}

bool Widget::isHovered() const
{
	return _isHovered;
}

bool Widget::isPressed() const
{
	return _isPressed;
}

bool Widget::isVisible() const
{
	return _isVisible;
}
void Widget::setVisible(bool v)
{
	_isVisible = v;
}

bool Widget::isActive() const
{
	return _isActive;
}

void Widget::setActive(bool a)
{
	_isActive = a;
}

int Widget::getPriority() const
{
	return _priority;
}

void Widget::setPrority(int p)
{
	_priority = p;
	if (_parent != nullptr)
		_parent->recalculatePriority();
}

const std::vector<Widget*> & Widget::getChildren() const
{
	return _children;
}

std::vector<Widget*> & Widget::getChildren()
{
	return _children;
}


void Widget::setLimitArea(const sf::Vector2f & A, const sf::Vector2f & B)
{
	_borderArea[0].x = A.x;
	_borderArea[0].y = A.y;  
	_borderArea[1].x = B.x;
	_borderArea[1].y = B.y;

	_isSetArea = true;
}

void Widget::setLimitArea(const sf::Rect<float>& f)
{
	setLimitArea({ f.left, f.top }, { f.left + f.width, f.top + f.height });
}

void Widget::limitSize()
{
	auto p = this->getAbsolutePosition();
	this->setLimitArea({ p.x,p.y, _size.x, _size.y });
}

void Widget::resetLimitArea()
{
	_borderArea[0] = { 0,0 };
	_borderArea[1] = { 0,0 };
	_isSetArea = false;
	for (auto x : _children)
	{
		x->resetLimitArea();
	}

}

void Widget::setWidgetEvent(CallbackType t, const std::function<void(Widget*, float)>& func)
{
	_widgetEvent[t] = func;
}

void Widget::resetWidgetEvent(CallbackType t)
{
	_widgetEvent[t] = nullptr;
}

void Widget::onUpdate(const std::function<void(Widget*, float)>& func)
{
	_onUpdate = func;
}

void Widget::resetOnUpdate()
{
	_onUpdate = nullptr;
}

//help functions

sf::Vector2f Widget::getAbsolutePosition()const
{
	if (_parent == nullptr)
		return _relativePos;
	else
		return _parent->getAbsolutePosition() + _parent->getPadding() + this->_relativePos;
}

sf::Vector2f Widget::mouseRelativePos() const
{
	auto minPos = getAbsolutePosition();
	auto mousePos = Input::getMousePosition();
	return { ((mousePos.x - minPos.x) / _size.x), ((mousePos.y - minPos.y) / _size.y) };
}

bool Widget::isMoseIn()const
{
	auto minPos = getAbsolutePosition();
	auto maxPos = minPos + getSize();
	auto mousePos = Input::getMousePosition();
	if (mousePos.x > minPos.x && mousePos.x < maxPos.x && mousePos.y > minPos.y && mousePos.y < maxPos.y)
		return true;
	return false;
}

bool Widget::_addChild(Widget * child)
{
	if (child->getParent() == this)
		return false;

	_children.push_back(child);
	this->recalculatePriority();
	child->setParent(this);
	return true;
}

void Widget::_removeChild(Widget * child)
{
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
}

void Widget::setParent(Widget * parent)
{
	_parent = parent;
	this->updatePosition();
	this->updateSize();
}

//private functions

void Widget::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!_isVisible)
		return;
	if (_isSetArea)
	{
		auto h_w = Input::getRezolution().y;
		auto pos = getAbsolutePosition();
		::glEnable(GL_SCISSOR_TEST);
		::glScissor(_borderArea[0].x + pos.x, h_w -_borderArea[1].y - pos.y, _borderArea[1].x - _borderArea[0].x, _borderArea[1].y - _borderArea[0].y);
		this->drawOnly(target, states);
		::glDisable(GL_SCISSOR_TEST);
	}
	else
		this->drawOnly(target, states);	
}

bool Widget::isPointInArea(const sf::Vector2f & point, const sf::Vector2f A, const sf::Vector2f B)
{
	if (point.x > A.x && point.x <B.x && point.y >A.y && point.y < B.y)
		return true;
	return false;
}

void Widget::actualizeInTime(float deltaT)
{
	if (_movingInTime)
	{
		move({ (deltaT *_velocity.x), (deltaT * _velocity.y) });
		_timeToMove -= deltaT;
		if (_timeToMove <= 0)
		{
			_movingInTime = false;
			setPosition(_nextPos);
		}
	}
	if (_changingColor)
	{
		_timefromBeg += deltaT;
		auto C = (_nextColor - _lastColor);
		C.r*=(_timefromBeg / _timeToChangeColor);
		C.g*=(_timefromBeg / _timeToChangeColor);
		C.b*=(_timefromBeg / _timeToChangeColor);
		C.a*=(_timefromBeg / _timeToChangeColor);
		this->setColor(C+_lastColor);
		if (_timefromBeg > _timeToChangeColor)
		{
			_changingColor = false;
			this->setColor(_nextColor);
		}
	}
}

void Widget::updateCallbacks(float deltaT)
{
	for (auto it = _callbacks.begin(); it != _callbacks.end(); it++)
	{
		_widgetEvent[*it](this, deltaT);
	}
	_callbacks.clear();
}

bool Widget::poolEvents(const sf::Event & e)
{
	bool res = false;
	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left && isMoseIn())
	{
		res = true;
		_isPressed = true;
		if (_widgetEvent[CallbackType::onPress] != nullptr)
			_callbacks.push_back(CallbackType::onPress);
	}		

	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Right && isMoseIn())
	{
		res = true;
		if (_widgetEvent[CallbackType::onPressRight] != nullptr)
			_callbacks.push_back(CallbackType::onPressRight);
	}
				
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left && _isPressed)
	{
		_isPressed = false;
		if (_widgetEvent[CallbackType::onRelease] != nullptr)
			_callbacks.push_back(CallbackType::onRelease);
	}
		
	return res;
}

void Widget::updateEvents()
{
	if (isMoseIn())
	{
		CallbackType t;
		if (_isHovered == false)
		{
			_isHovered = true;
			t = CallbackType::onHoverIn;
		}
		else
		{
			t = CallbackType::onHover;
		}
		if (_widgetEvent[t] != nullptr)
			_callbacks.push_back(t);

	}
	else if (!isMoseIn() && _isHovered == true)
	{
		_isHovered = false;
		if (_widgetEvent[CallbackType::onHoverOut] != nullptr)
			_callbacks.push_back(CallbackType::onHoverOut);
	}
	if (_isPressed)
	{
		if (_widgetEvent[CallbackType::onHold] != nullptr)
			_callbacks.push_back(CallbackType::onHold);
		if (!isMoseIn())
		{
			_isPressed = false;
			if (_widgetEvent[CallbackType::onRelease] != nullptr)
				_callbacks.push_back(CallbackType::onRelease);
		}
	}
}

void Widget::recalculatePriority()
{
	std::sort(_children.begin(), _children.end(), [](const Widget*  l, const Widget*  r) {return l->getPriority() < r->getPriority(); });
}

void Widget::drawOnly(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto it = _children.begin();
	while (it != _children.end())
	{
		if ((*it)->getPriority() >= _priority)
			break;
		(*it)->draw(target, states);
		it++;
	}

	_draw(target, states);
	while (it != _children.end())
	{
		(*it)->draw(target, states);
		it++;
	}
	_drawAfterAll(target, states);
}


}

