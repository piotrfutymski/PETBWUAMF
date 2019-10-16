#include "Order.h"

Didax::Order::Order(Engine * eng, OrderPrototype * prototype):GameObject(eng)
{
	_prototype = prototype;
}

Didax::Order::~Order()
{
}

bool Didax::Order::isInHand() const
{
	if (_location == Location::InHand)
		return true;
	return false;
}

Didax::Canvas * Didax::Order::show(AssetMeneger * assets, int pos)
{
	auto res = this->openGUI<OrderRepresentation>("OrderRepresentation", assets);
	auto URep = this->getGUI<OrderRepresentation>("OrderRepresentation");
	URep->setOrder(_prototype->_texture, assets);
	URep->setPosition(pos);
	return res; 
}

void Didax::Order::setAsChoosable()
{
	this->getGUI<OrderRepresentation>("OrderRepresentation")->setChoosable();
}
