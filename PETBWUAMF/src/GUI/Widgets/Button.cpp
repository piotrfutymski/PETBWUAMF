#include "Button.h"

Didax::Button::Button()
{
	_interableFlag = true;
	_isInterable = true;
}

void Didax::Button::setTexture(const sf::Texture * t)
{
	_sprite.setTexture(*t);
	this->updateSize();
}

void Didax::Button::setHoverMask(const sf::Color & c)
{
	_hoverColorMask = c;
	this->updateColor();
}

void Didax::Button::setClickedMask(const sf::Color & c)
{
	_clickedColorMask = c;
	this->updateColor();
}

sf::Color Didax::Button::getHoverMask() const
{
	return _hoverColorMask;
}

sf::Color Didax::Button::getClickedMask() const
{
	return _clickedColorMask;
}

void Didax::Button::_update(float deltaT)
{
	for (auto &c : _callbacks)
	{
		if (c == Widget::CallbackType::onHoverIn || c == Widget::CallbackType::onHoverOut ||
			c == Widget::CallbackType::onPress || c == Widget::CallbackType::onRelease)
		{
			this->updateColor();
			break;
		}
	}
}

bool Didax::Button::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void Didax::Button::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Didax::Button::updatePosition()
{
	_sprite.setPosition(this->getAbsolutePosition());
}

void Didax::Button::updateSize()
{
	if (_sprite.getTexture() == nullptr)
		return;
	auto textureSize = _sprite.getTexture()->getSize();
	_sprite.setScale({ _size.x / textureSize.x, _size.y / textureSize.y });
}

void Didax::Button::updateColor()
{
	sf::Color mask;
	if (_isPressed)
		mask = _clickedColorMask;
	else if (_isHovered)
		mask = _hoverColorMask;
	else
		mask = sf::Color::White;
	_sprite.setColor(_color * mask);
}
