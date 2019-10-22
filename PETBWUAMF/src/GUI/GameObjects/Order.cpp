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

void Didax::Order::addToHand(AssetMeneger * assets, int pos, Canvas * parent)
{
	this->openGUI(parent,assets);
	auto URep = this->getGUI<OrderRepresentation>();
	URep->setOrder(_prototype->_texture, assets);
	URep->setPosition(pos);
}

const Didax::OrderPrototype * Didax::Order::getPrototype() const
{
	return _prototype;
}

void Didax::Order::setDescriptable()
{
	if (!this->isInHand())
		return;
	_representation->onlyHoverButton("order");
	_representation->setOnHoverInToButton("order", [this] {_functions["showDescription"](this); });
	_representation->setOnHoverOutToButton("order", [this] {_functions["hideDescription"](this); });
}

void Didax::Order::setUnClicable()
{
	if (!this->isInHand())
		return;
	_representation->unactiveButton("order");
}


void Didax::Order::setCHoosable()
{
	if (!this->isInHand())
		return;
	_representation->backToEmptyButton("order");
	_representation->setOnHoverInToButton("order", [this] {_functions["showDescription"](this); });
	_representation->setOnHoverOutToButton("order", [this] {_functions["hideDescription"](this); });

	auto ptr = static_cast<OrderRepresentation *>(_representation.get());
	_representation->setOnPressToButton("order", [this, ptr] {_functions["chooseUnitTarget"](this); ptr->setChoosed(true); });
}

void Didax::Order::setFunctions(const std::map<std::string, std::function<void(Order*u)>>& f)
{
	_functions = f;
}


