#include "OrderRepresentation.h"

Didax::OrderRepresentation::OrderRepresentation()
{
}

Didax::OrderRepresentation::~OrderRepresentation()
{
}

void Didax::OrderRepresentation::setChoosable()
{
	_chosable = true;
}

void Didax::OrderRepresentation::setOrder(const std::string & name, AssetMeneger * assets)
{
	auto text = assets->getAsset<TextureAsset>(name);
	_root->setTexture(&(text->_texture));
}

void Didax::OrderRepresentation::setPosition(int pos)
{
	_root->setPosition(ORDERPOSITIONTAB[pos]);
}

void Didax::OrderRepresentation::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	//root
	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });

}

void Didax::OrderRepresentation::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	this->createEmptyButton(_root);
}
