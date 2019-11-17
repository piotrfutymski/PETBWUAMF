#pragma once


#pragma once
#include "Widget.h"

namespace Didax
{

class HPbar : public Widget
{


public:

	HPbar();

	void setMaxHP(int maxHP);
	int getMaxHP()const;

	void setHP(int HP);
	int getHP()const;

	void setLineWidth(int w);
	int getLineWidth()const;

	bool isOverhealed()const;


private:

	sf::RectangleShape _redHP;
	sf::RectangleShape _line;
	sf::RectangleShape _greenHP;

	int _lineWidth{ 2 };

	int _maxHP{ 100 };
	int _HP{ 100 };

	bool _overhealed{ false };





private:
		// Inherited via Widget
	virtual void _update(float deltaT) override;

	virtual bool _input(const sf::Event & event, bool inArea = true) override;

	virtual void _draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void updatePosition() override;

	virtual void updateSize() override;

	virtual void updateColor() override;

	void recalculateBar();

};

}