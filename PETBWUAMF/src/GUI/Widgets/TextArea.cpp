#include "TextArea.h"
#include <locale>
#include <codecvt>
#include <string>

namespace Didax
{

TextArea::TextArea()
{
	_background.setFillColor(sf::Color::White);
}

TextArea::TextArea(const std::string & s)
{
	TextArea();
	_allText = s;
	this->recalculateLines();
}

sf::Color TextArea::getBackgroundColor() const
{
	return _backgroundColor;
}

void TextArea::setBackgroundColor(sf::Color c)
{
	_backgroundColor = c;
	_background.setFillColor(c*_color);
}

void TextArea::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	_background.setFillColor(sf::Color(r, g, b, a));
}

void TextArea::setFontColor(sf::Color c)
{
	_fontColor = c;
	this->recalculateColor();;
}

void TextArea::setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	setFontColor(sf::Color(r, g, b, a));
}

std::string TextArea::getText() const
{
	return _allText;
}

void TextArea::setText(const std::string & s)
{
	_allText = s;
	this->recalculateLines();
}

void TextArea::setFont(sf::Font * f)
{
	_font = f;
	this->recalculateLines();
}

int TextArea::getCharacterSize() const
{
	return _characterSize;
}

void TextArea::setCharacterSize(int s)
{
	_characterSize = s;
	for (auto x : _textLines)
	{
		x.setCharacterSize(_characterSize);
	}
	this->recalculateLinesPositions();
}

int TextArea::getLineSpacing() const
{
	return _lineSpacing;
}

void TextArea::setLineSpacing(int s)
{
	_lineSpacing = s;
	this->recalculateLinesPositions();
}

sf::Vector2f TextArea::getMargin() const
{
	return _margin;
}

void TextArea::setMargin(const sf::Vector2f & m)
{
	_margin = m;
	this->recalculateLinesPositions();
}

TextArea::Alaign TextArea::getAlaign() const
{
	return _alaign;
}

void TextArea::setAlaign(Alaign a)
{
	_alaign = a;
	this->recalculateLinesPositions();
}

void TextArea::resizeToText()
{
	this->setSize(this->getTextSize());
}

sf::Vector2f TextArea::getTextSize() const
{
	sf::Vector2f res{ 0,0 };
	for (size_t i = 0; i < _textLines.size(); i++)
	{
		if (_textLines[i].getGlobalBounds().width > res.x)
			res.x = _textLines[i].getGlobalBounds().width;
	}
	res.y = _margin.y + _textLines.size() * (_characterSize + _lineSpacing);
	return res;
}

void TextArea::_update(float deltaT)
{
}

bool TextArea::_input(const sf::Event & event, bool inArea)
{
	return false;
}

void TextArea::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_background);
	for (auto x : _textLines)
	{
		target.draw(x);
	}
}

void TextArea::updatePosition()
{
	_background.setPosition(this->getAbsolutePosition());
	this->recalculateLinesPositions();
}

void TextArea::updateSize()
{
	_background.setSize(_size);
}

void TextArea::recalculateLinesPositions()
{
	float x,y = 0;
	
	for (size_t i = 0; i < _textLines.size(); i++)
	{
		if (_alaign == Alaign::Left)
		{
			x = _margin.x;
		}
		else if (_alaign == Alaign::Center)
		{
			float l = this->getTextLineLength(_textLines[i]);
			x = (_size.x - l) / 2;
		}
		else
		{
			float l = this->getTextLineLength(_textLines[i]);
			x = (_size.x - l - _margin.x);
		}
		y = _margin.y + i * (_characterSize + _lineSpacing);
		auto abs = this->getAbsolutePosition();
		_textLines[i].setPosition(abs.x + x, abs.y + y);
	}
}

void TextArea::recalculateLines()
{
	std::string buf = "";
	std::stringstream ss{ _allText };


	_textLines.clear();	

	while (std::getline(ss, buf, '\n'))
	{	
		_textLines.emplace_back(sf::Text {});
		std::wstring wsTmp(buf.begin(),buf.end());
		_textLines.back().setString(wsTmp);
		_textLines.back().setPosition(0, 0);
		_textLines.back().setFont(*_font);
	}
	this->recalculateLinesPositions();
	this->recalculateColor();
}

void TextArea::recalculateColor()
{
	for (auto& x : _textLines)
	{
		x.setFillColor(_fontColor*_color);
	}
}

float TextArea::getTextLineLength(const sf::Text & t)
{
	return t.getLocalBounds().width;
}

void TextArea::updateColor()
{
	this->setBackgroundColor(_backgroundColor);
	this->setFontColor(_fontColor);
}



}

