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

void Didax::UnitRepresentation::_initLogic(Engine * e)
{
	_unit->setWidgetEvent(Widget::CallbackType::onHoverIn, [=](Widget *, float) {
		onHoverIn(this, e);
	});

	_unit->setWidgetEvent(Widget::CallbackType::onHoverOut, [=](Widget *, float) {
		onHoverOut(this, e);
	});

	_unit->setWidgetEvent(Widget::CallbackType::onRelease, [=](Widget *, float) {
		onRelease(this, e);
	});
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

std::function<void(Didax::UnitRepresentation *, Didax::Engine *) > Didax::UnitRepresentation::onHoverIn = nullptr;
std::function<void(Didax::UnitRepresentation *, Didax::Engine *) > Didax::UnitRepresentation::onHoverOut = nullptr;
std::function<void(Didax::UnitRepresentation *, Didax::Engine *) > Didax::UnitRepresentation::onRelease = nullptr;