#include "GUIElement.h"

Didax::GUIElement::GUIElement(GUIElementPrototype * prototype)
{
	_prototype = prototype;
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
	this->_initLogic();
	parent->addChild(_root);
	_parent = parent;
}

void Didax::GUIElement::close()
{
	_parent->removeChild(_root);
	_widgets.clear();
}

void Didax::GUIElement::setPriority(int p)
{
	_priority = p;
	_root->setProrityRecoursive(p);
}

int Didax::GUIElement::getPriority() const
{
	return _priority;
}


sf::Vector2f Didax::GUIElement::UNITPOSITIONTAB[] = {
	{200,40},{200,220},{200,400},{200,580},
	{350,40},{350,220},{350,400},{350,580},
	{600,40},{600,220},{600,400},{600,580},
	{750,40},{750,220},{750,400},{750,580}
};

sf::Vector2f Didax::GUIElement::ORDERPOSITIONTAB[] = {
	{0,840},{140,840},{280,840},{420,840},
	{560,840},{700,840},{940,840},{1080,840},
	{1220,840},{1360,840},
};


