#pragma once
#include "Widget.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>

namespace Didax
{


class TextArea : public Widget
{
public:

	enum class Alaign {
		Left, Center, Right
	};

	//constructors

	TextArea();

	TextArea(const std::string & s);

	//properties

	sf::Color getBackgroundColor()const;

	void setBackgroundColor(sf::Color);
	void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	void setFontColor(sf::Color);
	void setFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	std::string getText()const;
	void setText(const std::string & s);

	void setFont(sf::Font * f);
	
	int getCharacterSize()const;
	void setCharacterSize(int s);

	int getLineSpacing()const;
	void setLineSpacing(int s);

	sf::Vector2f getMargin()const;
	void setMargin(const sf::Vector2f & m);

	Alaign getAlaign()const;
	void setAlaign(Alaign a);

	void resizeToText();
	sf::Vector2f getTextSize()const;

private:
	std::string _allText{ "" };
	std::vector<sf::Text> _textLines;
	sf::RectangleShape _background;
	sf::Font * _font;
	sf::Color _fontColor{0,0,0,255};
	sf::Color _backgroundColor{0,0,0,0};

	int _characterSize{ 30 };
	int _lineSpacing{ 5 };
	sf::Vector2f _margin{ 5,5 };
	Alaign _alaign{ Alaign::Left };


	// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;
	//help functions

	void recalculateLinesPositions();
	void recalculateLines();

	void recalculateColor();

	float getTextLineLength(const sf::Text & t);



};

}