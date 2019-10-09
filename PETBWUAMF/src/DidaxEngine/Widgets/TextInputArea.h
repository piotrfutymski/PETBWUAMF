#pragma once
#include "Widget.h"
#include "../Utility/StringConversion.h"


namespace Didax
{

class TextInputArea : public Widget
{
public:
	TextInputArea();
	~TextInputArea();

	sf::Color getBackgroundColor()const;

	void setBackgroundColor(const sf::Color &c);
	void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	void setInputBackgroundColor(const sf::Color & c);
	void setInputBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	void setFontColor(sf::Color);
	void setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	std::string getText()const;
	void setText(const std::string & s);

	void setFont(sf::Font * f);

	int getCharacterSize()const;
	void setCharacterSize(int s);

	sf::Vector2f getMargin()const;
	void setMargin(const sf::Vector2f & m);

	bool isEditable()const;
	void setEditable(bool e);


private:

	std::string _allText{ "" };
	sf::Text _textLine;
	sf::RectangleShape _background;
	sf::Font * _font;
	sf::Color _fontColor;
	sf::Color _nonEditableColor;
	sf::Color _editableColor;

	sf::RectangleShape _cursor{ sf::Vector2f{1,30} };

	int _characterSize{ 30 };
	sf::Vector2f _margin{ 5,5 };

	bool _isEditable;

	bool _isCursorOnScreen{ true };
	float _cursorTime{ 0.5 };
	float _cursorPeriod{ 0 };

	size_t _charIndex;

	// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

	void recalculateCursor();

	void calculateCharIndex();

	std::string captureChar(const sf::Event & event);

	void refreshColor();

};

}