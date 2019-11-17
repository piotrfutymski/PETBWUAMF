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

void Didax::OrderRepresentation::setPosition(int pos)
{
	_root->setPosition({ _offset.x + (_orderSize.x + _padding) * pos, _offset.y });
}

void Didax::OrderRepresentation::resetOrder()
{
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

void Didax::OrderRepresentation::_initLogic()
{
}

void Didax::OrderRepresentation::set_onHoverIn(const std::function<void()>& f)
{
	_order->setWidgetEvent(Widget::CallbackType::onHoverIn, [=](Widget *, float) {
		f();
	});
}

void Didax::OrderRepresentation::set_onHoverOut(const std::function<void()>& f)
{
	_order->setWidgetEvent(Widget::CallbackType::onHoverOut, [=](Widget *, float) {
		f();
	});
}
