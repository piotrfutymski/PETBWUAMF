#pragma once

#include "Widget.h"

namespace Didax
{

class SwitchableImage : public Widget
{
public:
	SwitchableImage();
	~SwitchableImage();

	void init(const std::vector <sf::Texture *> & txt);

	void setOption(size_t id);

	size_t getOption()const;

	void nextOption();


private:

	std::vector<sf::Texture *> _textures;

	sf::Sprite _sprite;

	int _choosenOption;


	// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea = true) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

};


}