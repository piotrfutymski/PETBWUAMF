#include "UnitRepresentation.h"
#include "../Engine.h"

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

	_unit->setWidgetEvent(Widget::CallbackType::onHoverIn, [this](Widget*, float) {
		_engine->unitOnHoverIn(this);
	});
	_unit->setWidgetEvent(Widget::CallbackType::onHoverOut, [this](Widget*, float) {
		_engine->unitOnHoverOut(this);
	});

	_unit->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget*, float) {
		_engine->unitOnRelease(this);
	});
}


Didax::UnitRepresentation::UnitRepresentation(GUIElementPrototype * prototype, Game * game, Engine * e) :GUIElement(prototype, game, e)
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
	_pos = unit->getPosition();
	
	this->reloadHealth();
	this->reloadPosition();

}

void Didax::UnitRepresentation::resetUnit()
{

}

size_t Didax::UnitRepresentation::getUnitID()
{
	return _unitID;
}

sf::Vector2i Didax::UnitRepresentation::getPosition() const
{
	return _pos;
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
	_pos = pos;

	_root->setPosition({ (float)(pos.x * (_unitSize + _padding)),(float)( pos.y * (_unitSize + _padding) )});

}

bool Didax::UnitRepresentation::isChoosable() const
{
	return _choosable;
}

void Didax::UnitRepresentation::setChoosable(bool c)
{
	_choosable = c;
}

void Didax::UnitRepresentation::recalculate()
{
	this->reloadHealth();
	this->reloadPosition();
}

void Didax::UnitRepresentation::hide()
{
	_root->setVisible(false);
	_root->setActive(false);
}