#include "TextInputArea.h"

namespace Didax
{


TextInputArea::TextInputArea()
{

}


TextInputArea::~TextInputArea()
{
}

sf::Color TextInputArea::getBackgroundColor() const
{
	return _nonEditableColor;
}

void TextInputArea::setBackgroundColor(const sf::Color & c)
{
	_nonEditableColor = c;
	this->refreshColor();
}

void TextInputArea::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->setBackgroundColor(sf::Color{ r,g,b,a });
}

void TextInputArea::setInputBackgroundColor(const sf::Color & c)
{
	_editableColor = c;
	this->refreshColor();
}

void TextInputArea::setInputBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->setInputBackgroundColor(sf::Color{ r,g,b,a });
}

void TextInputArea::setFontColor(sf::Color c)
{
	_fontColor = c;
	_textLine.setFillColor(c*_color);
	_cursor.setFillColor(c*_color);
}

void TextInputArea::setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->setFontColor(sf::Color{ r,g,b,a });
}

std::string TextInputArea::getText() const
{
	return _allText;
}

void TextInputArea::setText(const std::string & s)
{
	_allText = s;
	_textLine.setString(s);
}

void TextInputArea::setFont(sf::Font * f)
{
	_font = f;
	_textLine.setFont(*f);
}

int TextInputArea::getCharacterSize() const
{
	return _characterSize;
}

void TextInputArea::setCharacterSize(int s)
{
	_characterSize = s;
	_textLine.setCharacterSize(s);
	_cursor.setSize(sf::Vector2f{ 1.0f, (float)s });
}

sf::Vector2f TextInputArea::getMargin() const
{
	return _margin;
}

void TextInputArea::setMargin(const sf::Vector2f & m)
{
	_margin = m;
	this->updatePosition();
}

bool TextInputArea::isEditable() const
{
	return _isEditable;
}

void TextInputArea::setEditable(bool e)
{
	_isEditable = e;
	this->refreshColor();
}

void TextInputArea::_update(float deltaT)
{
	if (_isEditable)
	{
		_cursorPeriod += deltaT;
		if (_cursorPeriod > _cursorTime)
		{
			_cursorPeriod = 0;
			_isCursorOnScreen = !_isCursorOnScreen;
		}

	}
}

bool TextInputArea::_input(const sf::Event & event, bool inArea)
{
	bool res = false;
	if (_isEditable)
	{
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (_charIndex > 0)
					_charIndex--;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				if (_charIndex < _allText.size())
					_charIndex++;
			}
			else if (event.key.code == sf::Keyboard::Delete)
			{
				if (_charIndex < _allText.size())
				{
					_allText.erase(_allText.begin() + _charIndex);
				}
			}
			else if (event.key.code == sf::Keyboard::BackSpace)
			{
				if (_charIndex > 0)
				{
					_allText.erase(_allText.begin() + _charIndex -1);
					_charIndex--;
				}
			}
			else
			{
				auto a = this->captureChar(event);
				_allText.insert(_charIndex, a);
				
				_charIndex+=a.size();				
			}
			this->setText(_allText);
			this->recalculateCursor();
		}

		if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left && this->isMoseIn() && inArea)
		{
			this->calculateCharIndex();
			this->recalculateCursor();
			res = true;
		}
	}
	return res;
}

void TextInputArea::_draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_background);
	target.draw(_textLine);
	if (_isEditable && _isCursorOnScreen)
		target.draw(_cursor);
}

void TextInputArea::updatePosition()
{
	auto a = this->getAbsolutePosition();
	_background.setPosition(a);
	_textLine.setPosition(a + _margin);
	this->recalculateCursor();
}

void TextInputArea::updateSize()
{
	_background.setSize(_size);
}

void TextInputArea::recalculateCursor()
{
	_cursor.setPosition(_textLine.findCharacterPos(_charIndex));
}

void TextInputArea::calculateCharIndex()
{
	auto a = _textLine.getGlobalBounds();
	std::vector<float> charPositions{ this->getAbsolutePosition().x };
	for (size_t i = 0; i < _allText.size(); i++)
	{
		charPositions.emplace_back(_textLine.findCharacterPos(i).x);
	}
	charPositions.emplace_back(a.left + a.width);
	charPositions.emplace_back(this->getAbsolutePosition().x + _size.x);

	auto mousePos = Input::getMousePosition();

	for (size_t i = 0; i < charPositions.size() - 1; i++)
	{
		if (charPositions[i] < mousePos.x && mousePos.x < charPositions[i + 1])
		{
			_charIndex = i-1;
			break;
		}
		if (_charIndex < 0)
			_charIndex = 0;
	}
}

std::string TextInputArea::captureChar(const sf::Event & event)
{
	return (StringConversion::keyToString(event.key.code));
}

void TextInputArea::refreshColor()
{
	if (_isEditable)
		_background.setFillColor(_editableColor*_color);
	else
		_background.setFillColor(_nonEditableColor*_color);
}

void TextInputArea::updateColor()
{
	this->setBackgroundColor(_editableColor);
	this->setInputBackgroundColor(_nonEditableColor);
	this->setFontColor(_fontColor);
}

}