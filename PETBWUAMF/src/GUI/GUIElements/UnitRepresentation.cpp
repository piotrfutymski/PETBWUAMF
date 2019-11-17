#include "UnitRepresentation.h"

void Didax::UnitRepresentation::_init()
{
	_widgets.push_back(std::make_unique<Button>());
	_widgets.push_back(std::make_unique<HPbar>());
	_unit = static_cast<Button *>(_widgets[1].get());
	_bar = static_cast<HPbar *>(_widgets[2].get());

	//root

	_unitSize = _prototype->_values["size"];
	_padding = _prototype->_values["Padd"];

	auto text = AssetMeneger::getAsset<TextureAsset>(_prototype->_strings["background"]);

	_root->setSize({ (float)_unitSize, (float)_unitSize });
	_root->setTexture(&text->_texture);
	_root->addChild(_unit);
	_root->addChild(_bar);

	// unit

	_unit->setPosition({ _prototype->_values["unitx"], _prototype->_values["unity"] });
	_unit->setSize({ _prototype->_values["unitW"], _prototype->_values["unitH"] });

	// bar

	_bar->setPosition({ _prototype->_values["hpBarx"], _prototype->_values["hpBary"] });
	_bar->setSize({ _prototype->_values["hpBarW"], _prototype->_values["hpBarH"] });

}

void Didax::UnitRepresentation::_initLogic()
{
}


Didax::UnitRepresentation::UnitRepresentation(GUIElementPrototype * prototype, Game * game) :GUIElement(prototype, game)
{
}

Didax::UnitRepresentation::~UnitRepresentation()
{
}

void Didax::UnitRepresentation::setUnit(size_t u)
{
	_unitID = u;
	auto unit = _game->getObject<Unit>(u);
	auto text = AssetMeneger::getAsset<TextureAsset>(unit->getPrototype()->_texture);
	_unit->setTexture(&text->_texture);
	
	this->reloadHealth();
	this->reloadPosition();


}

void Didax::UnitRepresentation::resetUnit()
{

}

void Didax::UnitRepresentation::reloadHealth()
{
	auto unit = _game->getObject<Unit>(_unitID);
	_bar->setMaxHP(unit->getPrototype()->_health);
	_bar->setHP(unit->getHealth());
}

void Didax::UnitRepresentation::reloadPosition()
{
	auto unit = _game->getObject<Unit>(_unitID);
	auto pos = unit->getPosition();

	_root->setPosition({ (float)(pos.x * (_unitSize + _padding)),(float)( pos.y * (_unitSize + _padding) )});

}

