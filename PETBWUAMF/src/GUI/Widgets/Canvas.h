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
	//properties

	void setTexture(const sf::Texture * t);

	void setRect();
	void unsetBackground();


private:

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