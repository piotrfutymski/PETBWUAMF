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
	size_t getOrderId();
	void setPosition(int p);
	int getPosition()const;
	void resetOrder();
	void setChoosable(bool c);
	bool isChoosable()const;
	void hide();
	void show();

	static std::function<void(OrderRepresentation *)> onHoverIn;
	static std::function<void(OrderRepresentation *)> onHoverInIfChoosabe;
	static std::function<void(OrderRepresentation *)> onHoverOut;
	static std::function<void(OrderRepresentation *)> onHoverOutIfChoosabe;
	static std::function<void(OrderRepresentation *)> onReleaseIfChoosabe;


private:

	Button * _order;

	sf::Vector2f _orderSize{132, 170};
	sf::Vector2f _offset{ 20, 910 };
	float _padding{ 4 };
	size_t _orderID{ (size_t)-1 };

	int _position;
	bool _isChoosable{ true };


private:

	// Inherited via GUIElement
	virtual void _init() override;

	virtual void _initLogic() override;

};

}