#include "UnitRepresentation.h"

void Didax::UnitRepresentation::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<ImageWidget>());
	_attack = static_cast<TextArea *>(_widgets[1].get());
	_health = static_cast<TextArea *>(_widgets[2].get());
	_defence = static_cast<TextArea *>(_widgets[3].get());
	_border = static_cast<ImageWidget *>(_widgets[4].get());

	//root

	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });
	_root->addChild(_attack);
	_root->addChild(_health);
	_root->addChild(_defence);
	_root->addChild(_border);


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

	// border

	_border->setPosition({ prototype->_values["xPosB"], (prototype->_values["yPosB"]) });
	auto text = assets->getAsset<TextureAsset>(prototype->_strings["border"]);
	_border->setTexture(&(text->_texture));
	_border->setVisible(false);
	_border->setActive(false);

}

void Didax::UnitRepresentation::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_root->setWidgetEvent(Widget::CallbackType::onHoverIn, [this](Widget * w, float dt) {
		if(this->getIfCanBeChoosed())
			static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,200 }); 
	});
	_root->setWidgetEvent(Widget::CallbackType::onHoverOut, [this](Widget * w, float dt) {
		if (this->getIfCanBeChoosed())
			static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,255 });
	});
	_root->setWidgetEvent(Widget::CallbackType::onPress, [this](Widget * w, float dt) {
		if (this->getIfCanBeChoosed())
		{
			this->onChoosed();
			static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,150 });
		}			
	});
	_root->setWidgetEvent(Widget::CallbackType::onRelease, [this](Widget * w, float dt) {
		if (this->getIfCanBeChoosed() && w->isHovered())
			static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,200 });
		else
			static_cast<Canvas *>(w)->setBackgroundColor({ 255,255,255,255 });
	});
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

sf::Color Didax::UnitRepresentation::getColorFromBC(const BorderColor & c)
{
	if (c == BorderColor::red)
		return sf::Color::Red;
	else
		return sf::Color::Yellow;
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
	_attack->setColor(getColorFromPC(p));
	_attack->setText(std::to_string(v));
}

void Didax::UnitRepresentation::setDefence(const ParameterColor & p, int v)
{
	_defence->setColor(getColorFromPC(p));
	_defence->setText(std::to_string(v));
}

void Didax::UnitRepresentation::setHealth(const ParameterColor & p, int v)
{
	_health->setColor(getColorFromPC(p));
	_health->setText(std::to_string(v));
}

void Didax::UnitRepresentation::setReadyToChoose(const BorderColor & c)
{
	_canBeChoosen = true;
	_border->setColor(getColorFromBC(c));
	_border->setVisible(true);
}

void Didax::UnitRepresentation::unsetReadyToChoose()
{
	_canBeChoosen = false;
	_border->setVisible(false);
}

void Didax::UnitRepresentation::setPosition(int pos)
{
	_root->setPosition(POSITIONTAB[pos]);
}

void Didax::UnitRepresentation::setOnChoosed(const std::function<void()>& func)
{
	_onChoosed = func;
}

void Didax::UnitRepresentation::resetOnChoosed()
{
	_onChoosed = nullptr;
}

bool Didax::UnitRepresentation::getIfCanBeChoosed() const
{
	return _canBeChoosen;
}

void Didax::UnitRepresentation::onChoosed()
{
	if (_onChoosed != nullptr)
		_onChoosed();
}


sf::Vector2f Didax::UnitRepresentation::POSITIONTAB[] = {
	{200,40},{200,210},{200,370},{200,530},
	{350,40},{350,210},{350,370},{350,530},
	{600,40},{600,210},{600,370},{600,530},
	{750,40},{750,210},{750,370},{750,530}
};