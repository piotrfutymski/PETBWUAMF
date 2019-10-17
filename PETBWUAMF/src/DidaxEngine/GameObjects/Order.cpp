#include "Order.h"

Didax::Order::Order(OrderPrototype * prototype, AssetMeneger * assets)
{
	_prototype = prototype;
	this->createGUI<OrderRepresentation>("OrderRepresentation", assets);
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

void Didax::Order::showInHand(AssetMeneger * assets, int pos, Canvas * parent,const std::function<void(Order *)> & hi, const std::function<void(Order *)> & ho)
{
	this->openGUI(parent,assets, { [hi,this]() {hi(this); } , [ho, this]() {ho(this); } });
	auto URep = this->getGUI<OrderRepresentation>();
	URep->setOrder(_prototype->_texture, assets);
	URep->setPosition(pos);
}

void Didax::Order::setAsChoosable(const std::function<void(Order *)> & f)
{
	this->getGUI<OrderRepresentation>()->setChoosable([f, this]() {f(this); });
}

const Didax::OrderPrototype * Didax::Order::getPrototype() const
{
	return _prototype;
}
