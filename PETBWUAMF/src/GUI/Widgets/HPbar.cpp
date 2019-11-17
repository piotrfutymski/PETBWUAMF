#include "HPbar.h"

namespace Didax
{
HPbar::HPbar(): Widget()
{
	this->updateColor();
}
}

void Didax::HPbar::_update(float deltaT)
{
}

bool Didax::HPbar::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void Didax::HPbar::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_redHP, states);
	if (!_overhealed)
		return;
	target.draw(_line, states);
	target.draw(_greenHP, states);
}

void Didax::HPbar::updatePosition()
{
	this->recalculateBar();
}

void Didax::HPbar::updateSize()
{
	this->recalculateBar();
}

void Didax::HPbar::updateColor()
{
	_redHP.setFillColor(sf::Color::Red * _color);
	_line.setFillColor(sf::Color::Black * _color);
	_greenHP.setFillColor(sf::Color::Green * _color);
}

void Didax::HPbar::recalculateBar()
{
	float hPrc = (float)_HP / (float)_maxHP;
	auto p = this->getAbsolutePosition();
	_redHP.setPosition(p);

	if (!_overhealed)
	{
		_redHP.setSize({ hPrc*_size.x, _size.y });
	}
	else
	{
		float r = 1 / hPrc;
		float g = (hPrc - 1) / hPrc;
		float d = _size.x - _lineWidth;

		_redHP.setSize({ r*_size.x, _size.y });
		_line.setSize({ (float)_lineWidth, _size.y });
		_greenHP.setSize({ g*_size.x, _size.y });

		_line.setPosition(p.x + r * _size.x, 0);
		_greenHP.setPosition(p.x + r * _size.x + _lineWidth, 0);
	}


}

void Didax::HPbar::setMaxHP(int maxHP)
{
	_maxHP = maxHP;
	if (_HP > _maxHP)
		_overhealed = true;
	else
		_overhealed = false;
	this->recalculateBar();
}

int Didax::HPbar::getMaxHP() const
{
	return _maxHP;
}

void Didax::HPbar::setHP(int HP)
{
	_HP = HP;
	if (_HP > _maxHP)
		_overhealed = true;
	else
		_overhealed = false;
	this->recalculateBar();
}

int Didax::HPbar::getHP() const
{
	return _HP;
}

void Didax::HPbar::setLineWidth(int w)
{
	_lineWidth = w;
	this->recalculateBar();
}

int Didax::HPbar::getLineWidth() const
{
	return _lineWidth;
}

bool Didax::HPbar::isOverhealed() const
{
	return _overhealed;
}
