#pragma once
#include "GUIElement.h"


namespace Didax
{
class OrderRepresentation:public GUIElement
{
public:

	OrderRepresentation(GUIElementPrototype * prototype, Game * game);
	~OrderRepresentation();

	void setOrder(size_t o);
	void setPosition(int p);
	void resetOrder();

	void set_onHoverIn(const std::function<void()> & f);
	void set_onHoverOut(const std::function<void()> & f);


private:

	Button * _order;

	sf::Vector2f _orderSize{132, 170};
	sf::Vector2f _offset{ 20, 910 };
	float _padding{ 4 };
	size_t _orderID;

	int _position;
	bool isChoosable{ true };


private:

	// Inherited via GUIElement
	virtual void _init() override;

	virtual void _initLogic() override;

};

}