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
