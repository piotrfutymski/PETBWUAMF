#pragma once
#include "GUIElement.h"


namespace Didax
{

class Engine;
class OrderRepresentation:public GUIElement
{
public:

	OrderRepresentation(GUIElementPrototype * prototype, Game * game, Engine * e);
	~OrderRepresentation();

	void setOrder(size_t o);
	size_t getOrderID();

	void setPosition(int p);
	int getPosition()const;

	void resetOrder();
	void setChoosable(bool c);
	bool isChoosable()const;
	void hide();
	void show();

	void setHoverInTime();
	void setChoosen();
	void resetPosition();


private:

	Button* _order{ nullptr };

	sf::Vector2f _orderSize{132, 170};
	sf::Vector2f _offset{ 20, 910 };
	float _padding{ 4 };
	size_t _orderID{ (size_t)-1 };

	int _position;
	bool _isChoosable{ true };


private:

	// Inherited via GUIElement
	virtual void _init() override;

};

}