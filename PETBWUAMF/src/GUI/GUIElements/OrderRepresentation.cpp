#include "OrderRepresentation.h"

Didax::OrderRepresentation::OrderRepresentation(GUIElementPrototype * prototype, Game * game)
	: GUIElement(prototype, game)
{
}

Didax::OrderRepresentation::~OrderRepresentation()
{
}

void Didax::OrderRepresentation::setOrder(size_t o)
{
	_orderID = o;
	auto order = _game->getObject<Order>(o);
	auto text = AssetMeneger::getAsset<TextureAsset>(order->getPrototype()->_texture);
	_order->setTexture(&text->_texture);
	
}

size_t Didax::OrderRepresentation::getOrderID()
{
	return _orderID;
}

void Didax::OrderRepresentation::setPosition(int pos)
{
	_position = pos;
	_root->setPosition({ _offset.x + (_orderSize.x + _padding) * pos, _offset.y });
}

int Didax::OrderRepresentation::getPosition() const
{
	return _position;
}

void Didax::OrderRepresentation::resetOrder()
{
	_orderID = -1;
	_order = nullptr;
}

void Didax::OrderRepresentation::setChoosable(bool c)
{
	_isChoosable = c;
	if (_isChoosable)
	{
		_root->setColor(sf::Color::White);
	}
	else
	{
		_root->setColor({ 100, 100, 100, 255 });
	}
}

bool Didax::OrderRepresentation::isChoosable() const
{
	return _isChoosable;
}

void Didax::OrderRepresentation::hide()
{
	_root->setActive(false);
	_root->setVisible(false);
}

void Didax::OrderRepresentation::show()
{
	_root->setActive(true);
	_root->setVisible(true);
}

void Didax::OrderRepresentation::setHoverInTime()
{
	auto old = _root->getPosition();
	_root->setPositionInTime(old.x, old.y - 20, 0.3);
}

void Didax::OrderRepresentation::setChoosen()
{
	auto old = _root->getPosition();
	_root->setPosition(old.x, old.y - 20);
	_root->setColor(sf::Color::White);
}

void Didax::OrderRepresentation::resetPosition()
{
	this->setPosition(this->getPosition());
}

void Didax::OrderRepresentation::_init()
{
	_widgets.push_back(std::make_unique<Button>());
	_order = static_cast<Button *>(_widgets[1].get());

	//root

	auto text = AssetMeneger::getAsset<TextureAsset>(_prototype->_strings["background"]);
	_root->setSize({ _orderSize.x, _orderSize.y });
	_root->setTexture(&text->_texture);
	_root->addChild(_order);

	//order

	_order->setPosition({0, 0 });
	_order->setSize({ _orderSize.x, _orderSize.y });

}

void Didax::OrderRepresentation::_initLogic(Engine * e)
{
	_order->setWidgetEvent(Widget::CallbackType::onHoverIn, [=](Widget *, float) {
		onHoverIn(this, e);
	});

	_order->setWidgetEvent(Widget::CallbackType::onHoverOut, [=](Widget *, float) {
		onHoverOut(this, e);
	});

	_order->setWidgetEvent(Widget::CallbackType::onRelease, [=](Widget *, float) {
		onRelease(this, e);
	});

}


std::function<void(Didax:: OrderRepresentation *, Didax::Engine *) > Didax::OrderRepresentation::onHoverIn = nullptr;
std::function<void(Didax:: OrderRepresentation *, Didax::Engine *) > Didax::OrderRepresentation::onHoverOut = nullptr;
std::function<void(Didax:: OrderRepresentation *, Didax::Engine *) > Didax::OrderRepresentation::onRelease = nullptr;