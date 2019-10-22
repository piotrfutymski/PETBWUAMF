#pragma once
#include "Widget.h"
#include "WidgetHelp/Scroller.h"

namespace Didax {



class ScrollArea : public Widget
{

public:

	//constructors
	ScrollArea();

	ScrollArea(const Scroller & scr);

	//public functions

	void addChild(Widget * widget);
	void removeChild(Widget * widget);
	

	//properties

	void setScroller(const Scroller & scr);

	sf::Color getBackgroundColor()const;

	void setBackgroundColor(sf::Color);
	void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	float getScrollerWidth()const;
	void setScrollerWidth(float x);

	float getAreaHeight()const;
	void setAreaHeight(float y);
	void resizeHeightToChildren();

	float getWheelVelocity()const;
	void setWheelVelocity(float v);

private:

	sf::RectangleShape _background;
	sf::Color _backgroundColor;

	Scroller _scroller;

	bool _showScroller{ true };

	float _areaHeight;

	float _deltaH;



	float _scrollerWidth{ 32 };

	float _wheelVelocity{ 0.1f };


	// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea) override;

	virtual bool _inputBeforeAll(const sf::Event & event, bool inArea) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void _drawAfterAll(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

	// help functions

	void calcualteChildrenPos();

	void calculateScroller();



};

}