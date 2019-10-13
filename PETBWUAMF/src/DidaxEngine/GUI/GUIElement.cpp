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

sf::Vector2f Didax::GUIElement::POSITIONTAB[] = {
	{200,40},{200,220},{200,400},{200,580},
	{350,40},{350,220},{350,400},{350,580},
	{600,40},{600,220},{600,400},{600,580},
	{750,40},{750,220},{750,400},{750,580}
};

sf::Color Didax::GUIElement::INTERACTIONCOLORS[] = {
	{255, 255, 255, 255},
	{200, 200, 200, 255},
	{150, 150, 150, 255},
};

sf::Color Didax::GUIElement::BORDERCOLORS[] = {
	{255, 255, 255, 255},
	{255, 255, 0, 255},
	{255, 0, 0, 255},
};