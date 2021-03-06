#include "GUIElement.h"

Didax::GUIElement::GUIElement(GUIElementPrototype * prototype, Game * game, Engine* e)
{
	_prototype = prototype;
	_game = game;
	_engine = e;

}

Didax::GUIElement::~GUIElement()
{
}

const Didax::Canvas * Didax::GUIElement::getRoot() const
{
	return _root;
}

Didax::Canvas * Didax::GUIElement::getRoot()
{
	return _root;
}

void Didax::GUIElement::open(Canvas * parent)
{
	_widgets.push_back(std::make_unique<Canvas>());
	_root = static_cast<Canvas *>(_widgets.begin()->get());
	this->_init();
	parent->addChild(_root);
	_parent = parent;
}

void Didax::GUIElement::close()
{
	_parent->removeChild(_root);
	_widgets.clear();
}



