#include "OrderRepresentation.h"

Didax::OrderRepresentation::OrderRepresentation(GUIElementPrototype * prototype) :GUIElement(prototype)
{
}

Didax::OrderRepresentation::~OrderRepresentation()
{
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


void Didax::OrderRepresentation::setChoosed(bool c)
{
	_choosed->setVisible(c);
}

void Didax::OrderRepresentation::_init(AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<ImageWidget>());
	_choosed = static_cast<ImageWidget *>(_widgets[1].get());

	//root
	_root->setSize({ _prototype->_values["widthR"], (_prototype->_values["heightR"]) });
	_root->addChild(_choosed);

	//choosed

	auto textback = assets->getAsset<TextureAsset>(_prototype->_strings["choosed"]);
	_choosed->setTexture(&(textback->_texture));

	_choosed->setVisible(false);
	_choosed->setActive(false);

	//

	for (auto & x : _widgets)
	{
		x->setPrority(2);
	}

}

void Didax::OrderRepresentation::_initLogic(AssetMeneger * assets)
{
	this->createEmptyButton("order", _root);
}
