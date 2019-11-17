#pragma once
#include "Widget.h"

namespace Didax
{

class Button : public Widget
{
public:

	Button();

public:

	void setTexture(const sf::Texture * t);

	//properties

	void setHoverMask(const sf::Color & c);
	void setClickedMask(const sf::Color & c);
	sf::Color getHoverMask()const;
	sf::Color getClickedMask()const;

private:

	sf::Sprite _sprite;

	sf::Color _hoverColorMask{ 200, 200, 200, 255 };
	sf::Color _clickedColorMask{ 150, 150, 150, 255 };

private:
// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea = true) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

};

}