#pragma once
#include "Widget.h"

namespace Didax
{

class Canvas : public Widget
{
public:

	enum class BackgroundType{
		None, Rect, Image
	};

	//Constructors

	Canvas();

public:
	//functions

	bool addChild(Widget * widget);
	void removeChild(Widget * widget);

	//properties

	sf::Color getBackgroundColor()const;

	void setBackgroundColor(sf::Color);
	void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);

	void setTexture(const sf::Texture * t);

	void setRect();
	void unsetBackground();


private:

	sf::Color _backgroundColor{ 255,255,255 };

	std::unique_ptr<sf::RectangleShape> _backgroundRect { nullptr };

	std::unique_ptr<sf::Sprite> _backgroundSprite{ nullptr };

	BackgroundType _bType{ BackgroundType::None };

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