#include "GUIElement.h"

Didax::GUIElement::GUIElement()
{

}

Didax::GUIElement::~GUIElement()
{
}

bool Didax::GUIElement::setParent(Canvas * parent)
{
	if (!parent->addChild(_root))
		return false;
	_parent = parent;
	return true;
}

Didax::Canvas * Didax::GUIElement::getParent()
{
	return _parent;
}

const Didax::Canvas * Didax::GUIElement::getRoot() const
{
	return _root;
}

Didax::Canvas * Didax::GUIElement::getRoot()
{
	return _root;
}

void Didax::GUIElement::init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_prototype = prototype;
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets[0].get());
	this->_init(prototype, assets);
	this->_initLogic(prototype, assets);

}
