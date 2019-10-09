#pragma once
#include "Widget.h"

namespace Didax
{

class Canvas : public Widget
{
public:
	//Constructors

	Canvas();

public:
	//functions

	void addChild(Widget * widget);
	void removeChild(Widget * widget);

	//properties

	sf::Color getBackgroundColor()const;

	void setBackgroundColor(sf::Color);
	void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);


private:

	sf::Color _backgroundColor;

	sf::RectangleShape _background;

private:
	// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

};

}