#include "UnitRepresentation.h"

void Didax::UnitRepresentation::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<TextArea>());
	_attack = static_cast<TextArea *>(_widgets[1].get());
	_health = static_cast<TextArea *>(_widgets[2].get());
	_defence = static_cast<TextArea *>(_widgets[3].get());

	//root

	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });
	_root->addChild(_attack);
	_root->addChild(_health);
	_root->addChild(_defence);


	auto f = assets->getAsset<FontAsset>(prototype->_strings["font"]);

	//attack

	_attack->setPosition({ prototype->_values["xPosA"], (prototype->_values["yPosA"]) });
	_attack->setFont(&(f->_font));

	// health

	_health->setPosition({ prototype->_values["xPosH"], (prototype->_values["yPosH"]) });
	_health->setFont(&(f->_font));

	// defence

	_defence->setPosition({ prototype->_values["xPosD"], (prototype->_values["yPosD"]) });
	_defence->setFont(&(f->_font));

	for (auto & x: _widgets)
	{
		x->setPrority(1);
	}

}

void Didax::UnitRepresentation::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets, const std::vector<std::function<void()>> & func)
{
	this->createEmptyButton("unit",_root);
}

sf::Color Didax::UnitRepresentation::getColorFromPC(const ParameterColor & p)
{
	if (p == ParameterColor::green)
		return sf::Color::Green;
	else if (p == ParameterColor::red)
		return sf::Color::Red;
	else 
		return sf::Color::White;
}


Didax::UnitRepresentation::UnitRepresentation()
{
}

Didax::UnitRepresentation::~UnitRepresentation()
{
}

void Didax::UnitRepresentation::setUnit(const std::string & name, AssetMeneger * assets)
{
	auto text = assets->getAsset<TextureAsset>(name);
	_root->setTexture(&(text->_texture));
}

void Didax::UnitRepresentation::setAttack(const ParameterColor & p, int v)
{
	_attack->setFontColor(getColorFromPC(p));
	_attack->setText(std::to_string(v));
}

void Didax::UnitRepresentation::setDefence(const ParameterColor & p, int v)
{
	_defence->setFontColor(getColorFromPC(p));
	_defence->setText(std::to_string(v));
}

void Didax::UnitRepresentation::setHealth(const ParameterColor & p, int v)
{
	_health->setFontColor(getColorFromPC(p));
	_health->setText(std::to_string(v));
}


void Didax::UnitRepresentation::setPosition(int pos)
{
	_root->setPosition(UNITPOSITIONTAB[pos]);
}



