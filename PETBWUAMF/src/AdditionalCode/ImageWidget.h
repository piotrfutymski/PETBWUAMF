#pragma once
#include "Widget.h"

namespace Didax
{

class ImageWidget: public Widget
{
public:
	ImageWidget();

public: 

	//properties:

	void setTexture(const sf::Texture * t);

	void setScalableTexture(bool flag);

	bool getScalable()const;

private:

	bool _noScalable{ false };

	sf::Sprite _sprite;
	sf::Vector2f _textureSize{0,0};
	bool _isTextureLoaded{ false };

	// Inherited via Widget
	virtual void _update(float deltaT) override;
	virtual bool _input(const sf::Event & event, bool inArea) override;
	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void updatePosition() override;
	virtual void updateSize() override;


	// Inherited via Widget
	virtual void updateColor() override;

};

}