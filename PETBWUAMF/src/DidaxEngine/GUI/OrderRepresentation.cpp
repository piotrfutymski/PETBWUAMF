#include "OrderRepresentation.h"

Didax::OrderRepresentation::OrderRepresentation(GUIElementPrototype * prototype) :GUIElement(prototype)
{
}

Didax::OrderRepresentation::~OrderRepresentation()
{
}

void Didax::OrderRepresentation::setChoosable(const std::function<void()> & f)
{
	_chosable = true;
	this->setOnPressToButton("order", f);
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


void Didax::OrderRepresentation::_init(AssetMeneger * assets)
{
	//root
	_root->setSize({ _prototype->_values["widthR"], (_prototype->_values["heightR"]) });
	_root->setPrority(1);
}

void Didax::OrderRepresentation::_initLogic(AssetMeneger * assets, const std::vector<std::function<void()>>& func)
{
	this->createEmptyButton("order", _root);
	this->setOnHoverInToButton("order", func[0]);
	this->setOnHoverOutToButton("order", func[1]);
}
