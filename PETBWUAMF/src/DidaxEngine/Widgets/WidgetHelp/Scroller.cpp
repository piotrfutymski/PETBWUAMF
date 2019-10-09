#include "Scroller.h"

namespace Didax
{

Scroller::Scroller()
{
	_topArrow._isHovered = false;
	_topArrow._isPressed = false;
	_bottomArrow._isPressed = false;
	_bottomArrow._isPressed = false;
	_button._isPressed = false;
	_button._isPressed = false;
}

Scroller::Scroller(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Vector2f & size, const sf::Texture * back):Scroller()
{
	init(top, bot, butt, size, back);
}

void Scroller::init(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Vector2f & size, const sf::Texture * back)
{
	setTextures(top, bot, butt, back);
	setSize(size);
}

bool Scroller::input(const sf::Event & e)
{
	bool res = false;
	if (!_isActive)
		return res;
	if (e.type == sf::Event::MouseButtonPressed && (_background.getGlobalBounds().contains(sf::Vector2f(Input::getMousePosition()))))
		res = true;
	this->elemInput(&_topArrow, e );
	this->elemInput(&_bottomArrow, e);
	this->elemInput(&_button, e);
	return res;

}

void Scroller::update(float deltaT)
{
	if (_topArrow._isPressed)
		this->onHold(&_topArrow,deltaT);
	if (_bottomArrow._isPressed)
		this->onHold(&_bottomArrow, deltaT);
	if (_button._isPressed)
		this->onHold(&_button, deltaT);

}

void Scroller::setTextures(const sf::Texture * top, const sf::Texture * bot, const sf::Texture * butt, const sf::Texture * back)
{
	_topArrow._sprite.setTexture(*top);
	_bottomArrow._sprite.setTexture(*bot);
	_button._sprite.setTexture(*butt);
	_arrowHeight = (float)top->getSize().y;
	_buttonHeight = (float)butt->getSize().y;
	_background.setTexture(*back);
}

void Scroller::setHoverColor(const sf::Color & c)
{
	_hoveredColor = c;
}

void Scroller::setClickedColor(const sf::Color & c)
{
	_clickedColor = c;
}

void Scroller::setNormalColor(const sf::Color & c)
{
	_normalColor = c;
}


sf::Vector2f Scroller::getSize() const
{
	return _size;
}

void Scroller::setSize(const sf::Vector2f & s)
{
	_size = s;
	this->recalculateAll();
}

float Scroller::getArrowHeight() const
{
	return _arrowHeight;
}

void Scroller::setArrowHeight(float h)
{
	_arrowHeight = h;
	this->recalculateAll();
}

float Scroller::getButtonHeight() const
{
	return _buttonHeight;
}

void Scroller::setButtonHeight(float b)
{
	_buttonHeight = b;
	this->recalculateAll();
}

float Scroller::getButtonPosition() const
{
	return _buttonPosition;
}

void Scroller::moveButton(float delta)
{
	this->setButtonPos(_buttonPosition + delta);
}

bool Scroller::isActive() const
{
	return _isActive;
}

void Scroller::setActive(bool a)
{
	_isActive = a;
}

void Scroller::setArrowVelocity(float v)
{
	_arrowVelocity = v;
}


void Scroller::setPosition(const sf::Vector2f & pos)
{
	_position = pos;
	this->recalculateAll();
}

sf::Vector2f Scroller::getPosition()
{
	return _position;
}

void Scroller::setOnButtonPosChanged(const std::function<void()>& f)
{
	_onButtonPosChanged = f;
}

void Scroller::setColor(const sf::Color & c)
{
	_globalColor = c;
	_background.setColor(_normalColor*_globalColor);
	this->recalculateColor(&_topArrow);
	this->recalculateColor(&_bottomArrow);
	this->recalculateColor(&_button);
}

sf::Color Scroller::getColor() const
{
	return _globalColor;
}


void Scroller::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_background);
	target.draw(_topArrow._sprite);
	target.draw(_bottomArrow._sprite);
	target.draw(_button._sprite);
}

void Scroller::elemInput(Element * el, const sf::Event & e)
{
	if (el->_sprite.getGlobalBounds().contains(sf::Vector2f(Input::getMousePosition())))
	{
		if (el->_isHovered == false && el->_isPressed == false)
			this->onHoverIn(el);
	}
	else
	{
		if (el->_isHovered == true && el->_isPressed == false)
			this->onHoverOut(el);		
	}

	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left && el->_isHovered == true)
	{
		if (el->_isPressed == false)
			this->onPress(el);
	}
	else if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (el->_isPressed == true)
			this->onRealesed(el);

	}
	else if (el != &_button && el->_isHovered == false)
	{
		if (el->_isPressed == true)
			this->onRealesed(el);
	}
}

void Scroller::onHoverIn(Element * el)
{
	el->_isHovered = true;
	this->recalculateColor(el);
}

void Scroller::onPress(Element * el)
{
	el->_isPressed = true;
	this->recalculateColor(el);
	if (el == &_button)
	{
		_buttonClickPos = Input::getMousePosition().y;
		_buttonClockPosprc = _buttonPosition;
	}
}

void Scroller::onHold(Element * el, float deltaT)
{
	if (el == &_button)
	{
		this->calculateButtonPos();
	}
	else if (el == &_topArrow)
	{
		float x = _buttonPosition - _arrowVelocity * deltaT * _buttonHeight / _freeSpaceheight;
		if (x > 0)
			this->setButtonPos(x);
	}
	else
	{
		float x = _buttonPosition + _arrowVelocity * deltaT * _buttonHeight / _freeSpaceheight;
		if (x < 1.0)
			this->setButtonPos(x);
	}
}

void Scroller::onRealesed(Element * el)
{
	el->_isPressed = false;
	this->recalculateColor(el);
}

void Scroller::onHoverOut(Element * el)
{
	el->_isHovered = false;
	this->recalculateColor(el);
}

void Scroller::recalculateColor(Element * el)
{
	if (el->_isPressed)
	{
		el->_sprite.setColor(_clickedColor*_globalColor);
	}
	else if (el->_isHovered)
	{
		el->_sprite.setColor(_hoveredColor*_globalColor);
	}	
	else
		el->_sprite.setColor(_normalColor*_globalColor);
}

void Scroller::recalculateAll()
{
	auto temp = _background.getTexture()->getSize();

	_background.setScale(_size.x / temp.x, (_size.y - (2*_arrowHeight)) / temp.y);;
	_background.setPosition(_position.x, _position.y + _arrowHeight);

	_freeSpaceheight = (int)(_size.y - 2 * _arrowHeight - _buttonHeight);

	_topArrow._sprite.setPosition(_position);
	temp = _topArrow._sprite.getTexture()->getSize();
	_topArrow._sprite.setScale(_size.x/ temp.x, 1);
	 recalculateButton();
	temp = _button._sprite.getTexture()->getSize();
	_button._sprite.setScale(_size.x/temp.x, 1);
	temp = _bottomArrow._sprite.getTexture()->getSize();
	_bottomArrow._sprite.setPosition(_position.x, _position.y+_size.y -_arrowHeight);
	_bottomArrow._sprite.setScale(_size.x/temp.x, 1);

}

void Scroller::recalculateButton()
{
	sf::Vector2f Point = { _position.x, _position.y + _arrowHeight };
	Point.y += _buttonPosition * _freeSpaceheight;
	_button._sprite.setPosition(Point);
}


void Scroller::calculateButtonPos()
{
	float delta =(float)( Input::getMousePosition().y - _buttonClickPos);
	delta /= _freeSpaceheight;
	auto x = delta + _buttonClockPosprc;
		this->setButtonPos(x);
}

void Scroller::setButtonPos(float pos)
{
	if (pos == _buttonPosition)
			return;
	if (pos < 0)
		pos = 0;
	else if (pos > 1)
		pos = 1;
		
	_buttonPosition = pos;
	this->recalculateButton();
	if(_onButtonPosChanged!=nullptr)
		this->_onButtonPosChanged();
}



}


